#include <stdio.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>

typedef struct{
    int fileSize;
    char completePath[256];
}couple;

typedef struct{
    char** buffer;
    bool *ready_1;
    int counterFile;
    couple *mainInformation;
    int numeroThread;
    int total_Size;

    pthread_mutex_t mutex;
    pthread_cond_t condition_fileSize;
    pthread_cond_t condition_totalSize;

}shared;

typedef struct{
    int tn;
    pthread_t pthread;
    shared *sh;

}t_data;

void *exploreDir(void *arg){
    t_data *data = (t_data*)arg;
    DIR *directory = opendir(data->sh->buffer[data->tn]);
    struct dirent *entry;

    //printf("Thread %d in attesa\n", data->tn);

    pthread_mutex_lock(&data->sh->mutex);
    
        //printf("Thread %d entrato nella sezione critica\n", data->tn);

        if (directory == NULL){
            printf("[DIR-%d] errore nell'apertura della cartella %s\n", data->tn, data->sh->buffer[data->tn]);
            data->sh->ready_1[data->tn] = true;
            //exit(-1);
        }else
            //printf("cartella %s aperta con successo\n", data->sh->buffer[data->tn]);

        while((entry = readdir(directory)) != NULL){
            if((strcmp(entry->d_name, ".") != 0) && strcmp(entry->d_name, "..")){
                printf("[DIR-%d] File %s trovato\n", data->tn, entry->d_name);
              
                strcpy(data->sh->mainInformation[data->sh->counterFile].completePath, data->sh->buffer[data->tn]);
                strcat(data->sh->mainInformation[data->sh->counterFile].completePath, "/");
                strcat(data->sh->mainInformation[data->sh->counterFile].completePath, entry->d_name);

                //printf("%s\n", data->sh->mainInformation[data->sh->counterFile].completePath);
                //printf("%d\n", data->tn);

                data->sh->counterFile++; 
            }else{
            data->sh->ready_1[data->tn]=true;
            }   
        }

        int n=0;
        for (int i = 0; i < data->sh->numeroThread; i++)
        {   
            if (data->sh->ready_1[i] == true)
            {
                n++;
            }
        }
        
        if(n == data->sh->numeroThread)
            pthread_cond_signal(&data->sh->condition_fileSize);
        
    pthread_mutex_unlock(&data->sh->mutex);

    closedir(directory); // Chiudi la directory
}

void *fileSize(void* arg){
    t_data *data = (t_data*)arg;
    struct stat filestat;
       
   // pthread_mutex_lock(&data->sh->mutex);
        pthread_cond_wait(&data->sh->condition_fileSize, &data->sh->mutex);
        
                for (int i = 0; i < data->sh->counterFile; i++){
                    //printf("File %s in indice %d\n", data->sh->mainInformation[i].completePath, i);
                    stat(data->sh->mainInformation[i].completePath, &filestat);
                    
                    if(S_ISREG(filestat.st_mode)){
                        data->sh->mainInformation[i].fileSize = filestat.st_size;
                        printf("[STAT] Il file Regolare %s e' di %d byte\n", data->sh->mainInformation[i].completePath, data->sh->mainInformation[i].fileSize);
                    }else
                        printf("[STAT] Il file %s non e' regolare\n", data->sh->mainInformation[i].completePath);                                
                }

        pthread_cond_signal(&data->sh->condition_totalSize);
   // pthread_mutex_unlock(&data->sh->mutex);
}


void *totalSize(void*arg){
    t_data *data = (t_data*)arg;
    
    //pthread_mutex_lock(&data->sh->mutex);
        pthread_cond_wait(&data->sh->condition_totalSize, &data->sh->mutex);
            
            data->sh->total_Size=0;

            for (int i = 0; i < data->sh->counterFile; i++){
                data->sh->total_Size += data->sh->mainInformation[i].fileSize;
                printf("[MAIN] Dimensione totale Momentanea %d con l'aggiunta del file %s\n", data->sh->mainInformation[i].fileSize, data->sh->mainInformation[i].completePath);
            }
            printf("[MAIN] Dimensione totale effettiva = %d con un totale di %d file regolari", data->sh->total_Size, data->sh->counterFile);

    //pthread_mutex_unlock(&data->sh->mutex);
}


int main(int argc, char** argv){
    shared *s = malloc(sizeof(shared));
    s->buffer = malloc((argc-1) * sizeof(char*));
    s->counterFile = 0;
    s->mainInformation = malloc(sizeof(couple) * (argc-1));
    s->ready_1 = malloc(sizeof(bool) * (argc-1));
    s->numeroThread = argc - 1;

    pthread_mutex_init(&s->mutex, NULL);
    pthread_cond_init(&s->condition_fileSize, NULL);
    pthread_cond_init(&s->condition_totalSize, NULL); 


    if (argc < 2) {
        printf("Usare: %s PATH PATH ... -> Esempio ./files/number1 \n", argv[0]);
        return 1;
    }


    t_data t_dir[argc-1];
        for (int i = 0; i < argc-1; i++)
        {
            s->buffer[i] = argv[i+1];
            t_dir[i].sh = s;
            t_dir[i].tn = i;
            pthread_create(&t_dir[i].pthread, NULL, exploreDir, (void*)&t_dir[i]);
        }
    
    //Non hanno bisogno di un t_number
    t_data t_stat;
        t_stat.sh = s;
        pthread_create(&t_stat.pthread, NULL, fileSize, (void*)&t_stat);

    t_data t_main; 
        t_main.sh = s;
        pthread_create(&t_main.pthread, NULL, totalSize, (void*)&t_main);
    
    for (int i = 0; i < argc-1; i++)
    {
        pthread_join(t_dir[i].pthread, NULL);
    }
    
    pthread_join(t_main.pthread, NULL);
    pthread_join(t_stat.pthread, NULL);

    free(s->ready_1);
    free(s->buffer);
    free(s);
}