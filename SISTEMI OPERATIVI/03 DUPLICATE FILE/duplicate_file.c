#include <stdio.h>                  
#include <stdlib.h>
#include <fcntl.h>
#include <sys/nnan.h>   //PROGRAMMA FUNZIONANTE SOLO IN SISTEMI UNIX
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <libgen.h>

// Definizioni delle dimensioni dei blocchi e dello stack
#define BLOCK_SIZE 1024       // Dimensione di ciascun blocco da copiare (1024 byte)
#define STACK_SIZE 10         // Numero massimo di record nello stack condiviso

// Struttura per rappresentare un blocco di dati
typedef struct {
    char buffer[BLOCK_SIZE]; // Buffer per memorizzare i dati del blocco
    char filename[256];      // Nome del file sorgente
    size_t total_size;       // Dimensione totale del file sorgente
    size_t offset;           // Posizione dell'offset nel file sorgente
    size_t actual_size;      // Dimensione effettiva dei dati copiati nel blocco
    int end_of_file;         // Flag per indicare se si è raggiunta la fine del file
} record_t;

// Stack condiviso per memorizzare i record dei blocchi letti
record_t stack[STACK_SIZE]; // Array di record che rappresentano lo stack
int stack_index = 0;         // Indice corrente nello stack

// Mutex e semafori per sincronizzazione tra i thread
pthread_mutex_t stack_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex per proteggere l'accesso allo stack
sem_t empty_slots;          // Semaforo per contare gli slot vuoti nello stack
sem_t full_slots;           // Semaforo per contare gli slot pieni nello stack

// Parametri per i thread
typedef struct {
    const char *file_src;    // Percorso del file sorgente
    const char *dest_dir;    // Cartella di destinazione per il file duplicato
} thread_param_t; // Struttura per passare i parametri ai thread, la t_data delle altre esercitazioni. Volendo potremmo mettere le strutture di sincronizzazione qui

// Funzione del thread READER
void *reader_thread(void *arg) {
    thread_param_t *params = (thread_param_t *)arg; // Cast dei parametri passati al thread
    const char *file_src = params->file_src;        // Percorso del file sorgente

    // Ottieni il nome del file dalla sua path
    char *filename = basename((char *)file_src);    // Estrae il nome del file dalla path

    // Apri il file sorgente in modalità lettura
    int fd_src = open(file_src, O_RDONLY);
    if (fd_src == -1) { // Controllo errore apertura file
        perror("Errore nell'apertura del file sorgente");
        pthread_exit(NULL);
    }

    // Ottieni la dimensione del file sorgente
    struct stat st;
    if (fstat(fd_src, &st) == -1) { // Controllo errore recupero info file
        perror("Errore nel recupero delle informazioni del file sorgente");
        close(fd_src);
        pthread_exit(NULL);
    }
    size_t file_size = st.st_size; // Dimensione totale del file

    // Mappa il file sorgente in memoria
    char *src_map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd_src, 0);
    if (src_map == MAP_FAILED) { // Controllo errore mapping file
        perror("Errore nel mapping del file sorgente");
        close(fd_src);
        pthread_exit(NULL);
    }

    size_t offset = 0; // Inizializzazione dell'offset
    while (offset < file_size) { // Loop fino a coprire l'intero file
        size_t bytes_to_copy = (file_size - offset < BLOCK_SIZE) ? (file_size - offset) : BLOCK_SIZE; // Calcola quanti byte copiare

        // Attendi uno slot libero nello stack
        sem_wait(&empty_slots); 

        // Inserisci nel buffer
        pthread_mutex_lock(&stack_mutex); // Acquisisci il mutex per l'accesso sicuro allo stack
            record_t *record = &stack[stack_index]; // Ottieni il record corrente dallo stack
            memcpy(record->buffer, src_map + offset, bytes_to_copy); // Copia i dati dal file sorgente
            strncpy(record->filename, filename, sizeof(record->filename)); // Copia il nome del file
            record->total_size = file_size; // Salva la dimensione totale del file
            record->offset = offset; // Salva l'offset corrente
            record->actual_size = bytes_to_copy; // Salva la dimensione effettiva copiato
            record->end_of_file = (offset + bytes_to_copy >= file_size) ? 1 : 0; // Controlla se è la fine del file
            stack_index++; // Incrementa l'indice dello stack
        pthread_mutex_unlock(&stack_mutex); // Rilascia il mutex

        // Notifica che c'è un blocco pieno
        sem_post(&full_slots);

        // Stampa informazioni di debug
        printf("READER: Copiato blocco di %zu byte da offset %zu per il file %s\n", bytes_to_copy, offset, filename);

        offset += bytes_to_copy; // Incrementa l'offset
    }

    // De-mappa e chiudi il file sorgente
    munmap(src_map, file_size); // Rilascia la mappatura
    close(fd_src); // Chiudi il file
    pthread_exit(NULL); // Termina il thread
}

// Funzione del thread WRITER
void *writer_thread(void *arg) {
    thread_param_t *params = (thread_param_t *)arg; // Cast dei parametri passati al thread
    const char *dest_dir = params->dest_dir; // Cartella di destinazione

    // Scrittura dei blocchi
    while (1) { // Loop infinito finché non viene interrotto
        // Attendi un blocco disponibile nello stack
        sem_wait(&full_slots);

        // Estrai il blocco dallo stack
        pthread_mutex_lock(&stack_mutex); // Acquisisci il mutex
        stack_index--; // Decrementa l'indice dello stack
        record_t *record = &stack[stack_index]; // Ottieni il record dallo stack
        pthread_mutex_unlock(&stack_mutex); // Rilascia il mutex

        // Crea il percorso del file di destinazione
        char file_dst[1024]; // Buffer per il percorso del file di destinazione
        snprintf(file_dst, sizeof(file_dst), "%s/%s", dest_dir, record->filename); // Componi il percorso

        // Crea o apri il file di destinazione
        int fd_dst = open(file_dst, O_RDWR | O_CREAT, 0644); // Apri il file in scrittura
        if (fd_dst == -1) { // Controllo errore apertura file
            perror("Errore nell'apertura del file di destinazione");
            pthread_exit(NULL);
        }

        // Alloca lo spazio nel file di destinazione
        if (ftruncate(fd_dst, record->total_size) == -1) { // Imposta la dimensione del file
            perror("Errore nell'allocazione dello spazio nel file di destinazione");
            close(fd_dst);
            pthread_exit(NULL);
        }

        // Mappa il file di destinazione
        char *dst_map = mmap(NULL, record->total_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_dst, 0);
        if (dst_map == MAP_FAILED) { // Controllo errore mapping file
            perror("Errore nel mapping del file di destinazione");
            close(fd_dst);
            pthread_exit(NULL);
        }

        // Scrivi il blocco nella posizione corretta
        memcpy(dst_map + record->offset, record->buffer, record->actual_size); // Copia il blocco nel file di destinazione

        // Stampa informazioni di debug
        printf("WRITER: Scritto blocco di %zu byte nell'offset %zu del file %s\n", record->actual_size, record->offset, record->filename);

        // Sincronizza il file
        msync(dst_map, record->total_size, MS_SYNC); // Sincronizza i dati nel file

        // De-mappa e chiudi il file di destinazione
        munmap(dst_map, record->total_size); // Rilascia la mappatura
        close(fd_dst); // Chiudi il file

        // Notifica che c'è uno slot libero
        sem_post(&empty_slots);

        // Controlla se è l'ultimo blocco
        if (record->end_of_file) {
            break; // Esci dal loop se è l'ultimo blocco
        }
    }

    pthread_exit(NULL); // Termina il thread
}

int main(int argc, char *argv[]) {
    if (argc < 3) { // Controlla se ci sono abbastanza argomenti
        fprintf(stderr, "Utilizzo: %s <file-1> <file-2> ... <cartella-destinazione>\n", argv[0]);
        return 1; // Esci con errore
    }

    int num_files = argc - 2;  // Numero di file sorgente
    const char *dest_dir = argv[argc - 1];  // Cartella di destinazione

    // Inizializza semafori
    sem_init(&empty_slots, 0, STACK_SIZE); // Inizializza il semaforo degli slot vuoti
    sem_init(&full_slots, 0, 0); // Inizializza il semaforo degli slot pieni

    pthread_t readers[num_files]; // Array per i thread lettori
    pthread_t writer; // Thread scrittore

    // Crea i thread READER
    thread_param_t params[num_files]; // Array per i parametri dei thread
    for (int i = 0; i < num_files; i++) {
        params[i].file_src = argv[i + 1]; // Percorso del file sorgente
        params[i].dest_dir = dest_dir; // Cartella di destinazione
        pthread_create(&readers[i], NULL, reader_thread, &params[i]); // Crea il thread lettore
    }

    // Crea il thread WRITER
    pthread_create(&writer, NULL, writer_thread, &params[0]); // Crea il thread scrittore

    // Attendi che i thread READER terminino
    for (int i = 0; i < num_files; i++) {
        pthread_join(readers[i], NULL); // Aspetta la terminazione di ogni thread lettore
    }

    // Attendi che il thread WRITER termini
    pthread_join(writer, NULL); // Aspetta la terminazione del thread scrittore

    // Distruggi semafori
    sem_destroy(&empty_slots); // Distruggi il semaforo degli slot vuoti
    sem_destroy(&full_slots); // Distruggi il semaforo degli slot pieni

    printf("Duplicazione completata.\n"); // Messaggio finale
    return 0; // Esci con successo
}