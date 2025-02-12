#include <stdio.h>      //Esempio sulle Barriere + Mutex
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 5

typedef struct{
    pthread_mutex_t mutex;
    pthread_barrier_t barrier;
    sem_t *turn;
    
    int n_threads;
    int counter;
}shared;

typedef struct{
    pthread_t pthread;
    int tn;
    shared* sh;
}t_data;

void wait(int t_id){
    printf("thread %d procede con del lavoro\n", t_id);
}

void *thread_barrier_func(void* arg){
    t_data *data = (t_data*) arg;
    
        sem_wait(&data->sh->turn[data->tn]);
    
                if(data->tn == 1)
                    wait(data->tn);
    
                if(data->sh->counter != (data->sh->n_threads - 1))
                printf("arrivato %d nella barriera, attende fratello\n", data->tn);
                else
                printf("ultimo thread %d fratello arrivato alla barriera\n");
    
                data->sh->counter++;

    sem_post(&data->sh->turn[((data->tn+1) % data->sh->n_threads)]);

    pthread_barrier_wait(&data->sh->barrier);

            printf("thread %d uscito dalla barriera\n", data->tn);

}

void *main_func(void* arg){
    t_data *data = (t_data*) arg;

    pthread_mutex_lock(&data->sh->mutex);

        printf("Main arrivato alla barriera, impossibilitato a procedere \n");
    
    pthread_mutex_unlock(&data->sh->mutex);

    pthread_barrier_wait(&data->sh->barrier);

        printf("Superata la barriera \n");    

}

int main(int argc, char** argv){
    shared* s = malloc(sizeof(shared));
    s->n_threads = (argc-1);
    s->turn = malloc(sizeof(sem_t) * (argc-1));
    s->counter = 0;

    pthread_barrier_init(&s->barrier, NULL, (argc));

    pthread_mutex_init(&s->mutex, NULL);

    sem_init(&s->turn[0], 0, 1);
    sem_init(&s->turn[1], 0, 0);

    t_data t_barrier[(argc-1)];
        for (int i = 0; i < (argc-1); i++)
        {
            t_barrier[i].sh = s;
            t_barrier[i].tn = i;
            pthread_create(&t_barrier[i].pthread, NULL, thread_barrier_func, (void*) &t_barrier[i]);
        }
    
    t_data t_main;
        t_main.sh = s;
        pthread_create(&t_main.pthread, NULL, main_func, (void*) &t_main);

    for(int i=0; i<argc-1; i++){
        pthread_join(t_barrier[i].pthread, NULL);
    }
        pthread_join(t_main.pthread, NULL);


    free(s);
}