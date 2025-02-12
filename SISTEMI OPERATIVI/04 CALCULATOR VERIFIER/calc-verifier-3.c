#include <stdio.h>      
#include <semaphore.h>     
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

#define MAX_REQUEST 5

typedef struct{
    long long int operator_1;
    long long int operator_2;
    int operation;
    int tn;
}record;

typedef struct{
    record buffer[MAX_REQUEST];
    long long int *n;
    int completed;
    int verified;

    char* paths[256];
    int *row;
    int n_threads;
    int element_in;
    long long *verify_results;

    int total_file;
    int save_counter;
    int ready;

    pthread_mutex_t mutex;
    sem_t *turn;
    sem_t full, empty;
}shared;
typedef struct{
    int tn;
    shared* sh;
    pthread_t pthread;
}t_data;

void *readFile(void *arg){
    t_data *data = (t_data*)arg;
    char s[30];

    FILE *temp = fopen(data->sh->paths[data->tn], "r");

    if(!temp){
        printf("[FILE-%d] impossibile aprire il file %s\n", data->tn, data->sh->paths[data->tn]);
        data->sh->n_threads--;
        return NULL;
    }

    while (fgets(s, sizeof(s), temp))
    {
        data->sh->row[data->tn]++;
    }

    fclose(temp);

    FILE *file = fopen(data->sh->paths[data->tn], "r");

    int counter = 0;

    if(counter == 0){
        fgets(s, sizeof(s), file);
        data->sh->n[data->tn] = (long long) atoll(s);

        printf("[FILE-%d] valore iniziale della computazione %lld\n", data->tn, data->sh->n[data->tn]);
    }

    while(1){        

        sem_wait(&data->sh->turn[data->tn]);
                pthread_mutex_lock(&data->sh->mutex);

            if(fgets(s, sizeof(s), file)){
                
                if(counter < 100){
                    counter++;


                    printf("[FILE-%d] prossima operazione: %s\n", data->tn, s);

                    if(s[0] == '+')
                        data->sh->buffer[data->sh->element_in].operation = 0;
                    else if(s[0] == '-')
                        data->sh->buffer[data->sh->element_in].operation = 1;
                    else if(s[0] == 'x')
                        data->sh->buffer[data->sh->element_in].operation = 2;

                    data->sh->buffer[data->sh->element_in].operator_2 = atoll(strcpy(s, s+1));
                    data->sh->buffer[data->sh->element_in].tn = data->tn;

                    data->sh->element_in++;
                    if(data->sh->element_in == 5){
                        sem_post(&data->sh->full);

                        sem_wait(&data->sh->empty);
                    }

                }else{
                    data->sh->verify_results[data->tn] = atoll(s);
                    printf("[FILE-%d] computazione terminata in modo corretto\n", data->tn);
                    counter++;
                    data->sh->save_counter = counter;
                    data->sh->ready++;
                    data->sh->completed++;

                    if(data->sh->ready == data->sh->n_threads){
                        sem_post(&data->sh->full);
                        break;
                    }
                    
                }
            }
                pthread_mutex_unlock(&data->sh->mutex);
                
                sem_post(&data->sh->turn[(data->tn + 1) % data->sh->n_threads]);   
    }
}

void *calculator(void* arg){
    t_data *data = (t_data*)arg;
    while (1)
    {    
        sem_wait(&data->sh->full);
                
        
            //printf("SIAMO ARRIVATI A 5\n");
        long long temp = 0;

            if(data->sh->save_counter == 101){
                for (int i = 0; i < data->sh->n_threads; i++)
                {
                    printf("[CALC] risultato computazione: %lld ;  numero da verificare: %lld\n", data->sh->n[i], data->sh->verify_results[i]);
                    
                    if(data->sh->verify_results[i] == data->sh->n[i]){
                        data->sh->verified++;
                        printf("[MAIN] verifiche completate con successo %d/%d\n", data->sh->verified, data->sh->total_file);
                        
                    }else
                        printf("[MAIN] verifica con esito negativo %d/%d\n", data->sh->verified, data->sh->total_file);
                }
                return NULL;
            }else{

            for (int i = 0; i < MAX_REQUEST; i++)
            {
                if(data->sh->buffer[i].operation == 0){
                    data->sh->buffer[i].operator_1 = data->sh->n[data->sh->buffer[i].tn]; 
                    temp = data->sh->buffer[i].operator_1 + data->sh->buffer[i].operator_2;
                    data->sh->n[data->sh->buffer[i].tn] =  temp;
                    printf("[CALC] Operazione Effettuata: %lld + %lld = %lld\n", data->sh->buffer[i].operator_1, data->sh->buffer[i].operator_2, data->sh->n[data->sh->buffer[i].tn]);
                }
                else if(data->sh->buffer[i].operation == 1){
                    data->sh->buffer[i].operator_1 = data->sh->n[data->sh->buffer[i].tn]; 
                    temp = data->sh->buffer[i].operator_1 - data->sh->buffer[i].operator_2;
                    data->sh->n[data->sh->buffer[i].tn] = temp;
                    printf("[CALC] Operazione Effettuata: %lld - %lld = %lld\n", data->sh->buffer[i].operator_1, data->sh->buffer[i].operator_2, data->sh->n[data->sh->buffer[i].tn]);
                } 
                else if(data->sh->buffer[i].operation == 2){
                    data->sh->buffer[i].operator_1 = data->sh->n[data->sh->buffer[i].tn]; 
                    temp = data->sh->buffer[i].operator_1 * data->sh->buffer[i].operator_2;
                    data->sh->n[data->sh->buffer[i].tn] = temp;
                    if(data->sh->n[data->sh->buffer[i].tn] > LLONG_MAX)
                        printf("Overflow Detected\n");
                    printf("[CALC] Operazione Effettuata: %lld x %lld = %lld\n", data->sh->buffer[i].operator_1, data->sh->buffer[i].operator_2, data->sh->n[data->sh->buffer[i].tn]);
                }
            }
            }

            printf("\n\n");
            data->sh->element_in = 0;                   
        
        sem_post(&data->sh->empty);
        
    }
}

int main(int argc, char** argv){

    if((argc) < 2)
        printf("inserisci almeno un file es. ./calc-verifier-3.exe <path-file> <path-file>");

    shared* s = malloc(sizeof(shared));
    s->turn = malloc(sizeof(sem_t) * (argc-1));
    s->n = malloc(sizeof(long long int) * (argc-1));
    s->row = malloc(sizeof(int) * (argc-1));
    s->verify_results = malloc(sizeof(long long) * (argc-1));

    s->n_threads = (argc-1);
    s->total_file = (argc-1);
    s->element_in = 0;
    s->save_counter = 0;
    s->ready = 0;


    pthread_mutex_init(&s->mutex, NULL);
    sem_init(&s->full, 0, 0);
    sem_init(&s->empty, 0, 0);


    t_data t_file[(argc-1)];
        for(int i=0; i<(argc-1); i++){
            if(i == 0)
                sem_init(&s->turn[i], 0, 1);
            else
                sem_init(&s->turn[i], 0, 0);

            t_file[i].sh = s;
            t_file[i].tn = i;
            pthread_create(&t_file[i].pthread, NULL, readFile, (void*)&t_file[i]);
            s->paths[i] = argv[i+1];
            s->row[i] = 0;
            s->verify_results[i] = 0;
        }

    t_data t_calc;
        t_calc.sh = s;
        pthread_create(&t_calc.pthread, NULL, calculator, (void*) &t_calc);
    
    for (int i = 0; i < (argc-1); i++){
        pthread_join(t_file[i].pthread, NULL);
    }
        pthread_join(t_calc.pthread, NULL);

    sem_destroy(&s->full);
    sem_destroy(&s->empty);
    
    for(int i=0; i<(argc-1); i++)
        sem_destroy(&s->turn[i]);

    pthread_mutex_destroy(&s->mutex);

    free(s);
}