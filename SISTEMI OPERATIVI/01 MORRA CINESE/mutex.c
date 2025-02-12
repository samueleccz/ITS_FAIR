#include "../lib/lib-misc.h"    //NON PENSO DI AVERLA UTILIZZATA
#include <stdio.h>      //27-09-2024: A VOLTE CRASHA QUANDO SI INSERISCONO MOLTEPLICI PARTITE, LEGGERI PROBLEMI DI SINCRONIZZAZIONE
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

typedef enum {
    CARTA,
    FORBICE,
    SASSO
} move;

typedef enum {
    G1,
    G2,
    JD,
    TB
} thread_n;

typedef struct {
    move m1;
    move m2;

    bool g1_ready;
    bool g2_ready;

    int numeroPartite;
    int counterVittorie[2];

    pthread_mutex_t gameplay;
    pthread_cond_t judge;
    pthread_cond_t results;
    pthread_cond_t giocatore1;
    pthread_cond_t giocatore2;
} shared;

typedef struct {
    shared *sh;
    thread_n tn;
    pthread_t pthread;
} t_data;

void *Giocatore(void *arg) {
    t_data *data = (t_data*) arg;

     srand(time(NULL) + data->tn);

    while (1) {
        pthread_mutex_lock(&data->sh->gameplay);

        if (data->tn == G1) {
            printf("P1 fa la sua mossa ");
            data->sh->m1 = rand() % 3;
            printf("%d\n", data->sh->m1);
            data->sh->g1_ready = true;
        } else {
            printf("P2 fa la sua mossa ");
            data->sh->m2 = rand() % 3;
            printf("%d\n", data->sh->m2);
            data->sh->g2_ready = true;
        }

        if (data->sh->g1_ready==true && data->sh->g2_ready==true) {
            pthread_cond_signal(&data->sh->judge);            
        }

        if (data->tn == G1) {
            pthread_cond_wait(&data->sh->giocatore1, &data->sh->gameplay);
        } else {
            pthread_cond_wait(&data->sh->giocatore2, &data->sh->gameplay);
        }

        pthread_mutex_unlock(&data->sh->gameplay);
    }

    return NULL;
}

void *Giudice(void *arg) {
    t_data *data = (t_data*) arg;

    while (1) {
        pthread_mutex_lock(&data->sh->gameplay);

        pthread_cond_wait(&data->sh->judge, &data->sh->gameplay);

        printf("mosse: %d - %d\n", data->sh->m1, data->sh->m2);

        if (data->sh->m1 == data->sh->m2) {

            printf("Pareggio, ricalcolo mosse\n");
            data->sh->g1_ready = false;
            data->sh->g2_ready = false;
            pthread_cond_signal(&data->sh->giocatore1);
            pthread_cond_signal(&data->sh->giocatore2);
        } else if ((data->sh->m1 == CARTA && data->sh->m2 == SASSO) ||
                   (data->sh->m1 == SASSO && data->sh->m2 == FORBICE) ||
                   (data->sh->m1 == FORBICE && data->sh->m2 == CARTA)) {
            printf("Punto a G1\n");
            data->sh->counterVittorie[0]++;
            pthread_cond_signal(&data->sh->results); 
        } else {
            printf("Punto a G2\n");
            data->sh->counterVittorie[1]++;
            pthread_cond_signal(&data->sh->results);
        }

       pthread_mutex_unlock(&data->sh->gameplay);
    }

    return NULL;
}

void *Tabellone(void *arg) {
    t_data *data = (t_data*) arg;
    int partiteGiocate = 0;

    while (partiteGiocate < data->sh->numeroPartite) {
        pthread_mutex_lock(&data->sh->gameplay);

        pthread_cond_wait(&data->sh->results, &data->sh->gameplay);
        
        printf("Tabellone: G1 %d - G2 %d\n", data->sh->counterVittorie[0], data->sh->counterVittorie[1]);

        partiteGiocate++;

        if (partiteGiocate == data->sh->numeroPartite) {
            printf("Partita terminata! Risultato finale: G1 %d - G2 %d\n",
                   data->sh->counterVittorie[0], data->sh->counterVittorie[1]);

            pthread_mutex_unlock(&data->sh->gameplay);
            break;
        }

        data->sh->g1_ready = false;
        data->sh->g2_ready = false;
        pthread_cond_signal(&data->sh->giocatore1);
        pthread_cond_signal(&data->sh->giocatore2);

        pthread_mutex_unlock(&data->sh->gameplay);
    }

    return NULL;
}


int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Uso: %s <numero_partite>\n", argv[0]);
        return -1;
    }

    shared *s = malloc(sizeof(shared));
    s->g1_ready = false;
    s->g2_ready = false;
    s->counterVittorie[0] = 0;
    s->counterVittorie[1] = 0;
    s->numeroPartite = atoi(argv[1]);

    pthread_mutex_init(&s->gameplay, NULL);
    pthread_cond_init(&s->judge, NULL);
    pthread_cond_init(&s->results, NULL);
    pthread_cond_init(&s->giocatore1, NULL);
    pthread_cond_init(&s->giocatore2, NULL);

    t_data td[4];

    for (int i = 0; i < 4; i++) {
        td[i].sh = s;
        td[i].tn = i;
    }

    pthread_create(&td[0].pthread, NULL, Giocatore, &td[0]);
    pthread_create(&td[1].pthread, NULL, Giocatore, &td[1]);
    pthread_create(&td[2].pthread, NULL, Giudice, &td[2]);
    pthread_create(&td[3].pthread, NULL, Tabellone, &td[3]);

    for (int i = 0; i < 4; i++) {
        pthread_join(td[i].pthread, NULL);
    }

    pthread_mutex_destroy(&s->gameplay);
    pthread_cond_destroy(&s->judge);
    pthread_cond_destroy(&s->results);
    pthread_cond_destroy(&s->giocatore1);
    pthread_cond_destroy(&s->giocatore2);
    free(s);

    return 0;
}
