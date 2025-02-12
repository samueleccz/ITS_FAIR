#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>                    // per adattarlo al calc-verifier basta adattare index per ogni thread
#include <stdlib.h>                     // BUFFER -> RECORD
#include <stdbool.h>                    // CONTEGGIO RIGHE
#include <string.h>                     //

#define BUFFER_SIZE 5
#define N 7
#define ROW 102

typedef struct{
    int element;
}buffer;

typedef struct{
    buffer buffer[BUFFER_SIZE];

    pthread_mutex_t mutex;
    sem_t *empty;
    sem_t full;

    int n_sum;

    int element_in;
    int total_row;
    int index;

}shared;

typedef struct{
    pthread_t pthread;
    int tn;
    shared *sh;
}t_data;

void* worker_thread(void* arg) {
    t_data *data = (t_data*)arg;

    
    while(1){
        sem_wait(&data->sh->empty[data->tn]);
            pthread_mutex_lock(&data->sh->mutex);

        data->sh->buffer[data->sh->element_in].element = data->tn;
        printf("Buffer %d riempito da %d con valore %d\n", data->sh->element_in, data->tn, data->sh->buffer[data->sh->element_in].element);
        //data->sh->element_in = (data->sh->element_in+1) % (BUFFER_SIZE);
        data->sh->element_in = data->sh->element_in+1 % (BUFFER_SIZE - 1);
        
        if(data->sh->element_in == 5){
            sem_post(&data->sh->full);
        }

        data->sh->index++;
        
        printf("data->index %d \n", data->sh->index);

        pthread_mutex_unlock(&data->sh->mutex); 

        if (data->sh->index == data->sh->total_row)
            break; //QUI DOVRESTI FARE IL CONTROLLO DELL'ULTIMA RIGA DI CALC

        sem_post(&data->sh->empty[(data->tn + 1) % N]);

    }

    return NULL;
}


void* main_thread(void* arg) {
    t_data *data = (t_data*)arg;

    while (1)
    {
    sem_wait(&data->sh->full);
    pthread_mutex_lock(&data->sh->mutex);
        
            printf("Consumo %d %d %d %d %d\n", data->sh->buffer[0].element, data->sh->buffer[1].element, data->sh->buffer[2].element, data->sh->buffer[3].element, data->sh->buffer[4].element);

            for(int i = 0; i<BUFFER_SIZE; i++){
                data->sh->buffer[i].element = 0;
            }
            data->sh->element_in = 0;

            if (data->sh->index == data->sh->total_row)
            {
                break;
            }
            

    pthread_mutex_unlock(&data->sh->mutex);
    
    }

    return NULL;
}

int main() {
    shared *s = malloc(sizeof(shared));
    s->empty = malloc(sizeof(sem_t) * N);
    s->element_in = 0;
    s->total_row = ROW; //Massimo righe fatte con fgets e contatore o impostate staticamente come in questo caso, meglio prima ipotesi
    s->index = 0; //Contatore righe eseguite

    sem_init(&s->full, 0, 0);

    pthread_mutex_init(&s->mutex, NULL);

    t_data t_work[N];

    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        sem_init(&s->empty[i], 0, 1);
        else
        sem_init(&s->empty[i], 0, 0);
 
        t_work[i].sh = s;
        t_work[i].tn = i;
        pthread_create(&t_work[i].pthread, NULL, worker_thread, (void*)&t_work[i]);
    }
    
    t_data t_main;
    t_main.sh = s;
        pthread_create(&t_main.pthread, NULL, main_thread, (void*)&t_main);

    for (int i = 0; i < N; i++)
    {
        pthread_join(t_work[i].pthread, NULL);
    }
        pthread_join(t_main.pthread, NULL);
    
    free(s);

    return 0;
}
