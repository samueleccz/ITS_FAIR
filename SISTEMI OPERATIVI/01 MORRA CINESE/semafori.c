#include "../lib/lib-misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <time.h>

typedef enum{
    CARTA,
    FORBICE,
    SASSO
}move;

typedef enum {
    G1,
    G2,
    JD,
    TB
} thread_n;

typedef struct{
    sem_t gameplay[2];
    sem_t tabellone;
    sem_t giudice;
    move m1;
    move m2;
    int vincitore;
    int numeroPartite;
    int counterVittorie[2];

}shared;

typedef struct{
    thread_n tn;
    shared* sh;
    pthread_t pthread;
}t_data;


void *Giocatore1(void *arg)
{
    t_data *data = (t_data *)arg;
    printf("Thread %d partito\n", data->tn);
    srand(time(NULL) + data->tn);

    while (1)
    {
        sem_wait(&data->sh->gameplay[0]);
        
        srand(time(NULL)+data->tn);
        data->sh->m1 = rand() % 3;
        printf("P1 ");
        if (data->sh->m1 == 0)
            printf("carta\n");
        if (data->sh->m1 == 1)
            printf("forbice\n");
        if (data->sh->m1 == 2)
            printf("sasso\n");

        sem_post(&data->sh->gameplay[1]);
        }
}

void *Giocatore2(void *arg)
{
    t_data *data = (t_data *)arg;
    printf("Thread %d partito\n", data->tn);

    while (1)
    {
        sem_wait(&data->sh->gameplay[1]);
        
        srand(time(NULL) + data->tn);
        data->sh->m2 = rand() % 3;
        printf("P2 ");
        if (data->sh->m2 == 0)
            printf("carta\n");
        if (data->sh->m2 == 1)
            printf("forbice\n");
        if (data->sh->m2 == 2)
            printf("sasso\n");

        sem_post(&data->sh->giudice);
    }
}

void *Giudice(void *arg){
    t_data *data = (t_data *)arg;
    
    while (1){
        sem_wait(&data->sh->giudice);
        printf("Thread %d partito\n", data->tn);

        int mossa1 = data->sh->m1;
        int mossa2 = data->sh->m2;

        if (mossa1 == mossa2){
            printf("Pareggio, stiamo per ripartire\n");
            sem_post(&data->sh->gameplay[0]);  
        }else if(mossa1 > mossa2){
            data->sh->vincitore = 0;
            sem_post(&data->sh->tabellone);      
        }else if(mossa1 < mossa2){
            data->sh->vincitore = 1;
            sem_post(&data->sh->tabellone);  
        }      
    }
}

void *Tabellone(void *arg){
    t_data *data = (t_data *)arg;

    while (1)
    {
        sem_wait(&data->sh->tabellone);
        printf("Thread %d partito\n", data->tn);

        if (data->sh->vincitore == 1)
        {
            data->sh->counterVittorie[0]++;
            //printf("counter vittorie %d\n", data->sh->counterVittorie[0]);
        }
        else if (data->sh->vincitore == 0)
        {
            data->sh->counterVittorie[1]++;
            //printf("counter vittorie %d\n", &data->sh->counterVittorie[1]);
        }

        printf("Punteggio : %d - %d\n", data->sh->counterVittorie[0], data->sh->counterVittorie[1]);
        data->sh->numeroPartite--;
       
        if (data->sh->numeroPartite == 0){
            if(data->sh->counterVittorie[0] > data->sh->counterVittorie[1]){
                printf("G1 vince su G2 con il seguente ");
            }else if(data->sh->counterVittorie[0] < data->sh->counterVittorie[1]){
                printf("G2 vince su G1 con il seguente ");
            }else if(data->sh->counterVittorie[0] == data->sh->counterVittorie[1]){
                printf("La partita finisce con un pareggio con il seguente ");
            }            
            printf("Punteggio : %d - %d\n", data->sh->counterVittorie[0], data->sh->counterVittorie[1]);
            
            exit(-1);
        }

        sem_post(&data->sh->gameplay[0]);
    }
}

int main(int argc, char **argv){
    if (argc != 2)
    {
        printf("numero argomenti errato\n");
        exit(-1);
    }
    int err;
    shared *s = malloc(sizeof(shared));
    s->numeroPartite = atoi(argv[1]);
    
    for (int i = 0; i < 2; i++)
    {
        s->counterVittorie[i] = 0;
    }
  
    t_data td[4];

    for (int i = 0; i < 4; i++)
    {
        td[i].tn = i;
        td[i].sh = s;
    }

    if ((err = pthread_create(&td[0].pthread, NULL, Giocatore1, (void *)&td[0])) != 0)
        exit_with_err("pthread_create", err);
    if ((err = pthread_create(&td[1].pthread, NULL, Giocatore2, (void *)&td[1])) != 0)
        exit_with_err("pthread_create", err);
    if ((err = pthread_create(&td[2].pthread, NULL, Giudice, (void *)&td[2])) != 0)
        exit_with_err("pthread_create", err);
    if ((err = pthread_create(&td[3].pthread, NULL, Tabellone, (void *)&td[3])) != 0)
        exit_with_err("pthread_create", err);

    sem_init(&s->gameplay[0], 0, 1);
    sem_init(&s->gameplay[1], 0, 0);
    sem_init(&s->tabellone, 0, 0);
    sem_init(&s->giudice, 0, 0);

    for (int i = 0; i < 4; i++)
    {
        if ((err = pthread_join(td[i].pthread, NULL)) != 0)
            exit_with_err("pthread_join", err);
    }

    for (int i = 0; i < 2; i++)
        sem_destroy(&s->gameplay[i]);

        sem_destroy(&s->tabellone);
        sem_destroy(&s->giudice);

    free(s);
    return EXIT_SUCCESS;
}