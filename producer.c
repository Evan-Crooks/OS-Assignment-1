#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/shm_table"
#define TABLE_SIZE 2

typedef struct {
    int items[TABLE_SIZE];
    int count;
} SharedTable;

//global variables
sem_t *emptySlots, *fullSlots, *mutex;
SharedTable *table;
int shm_fd;

void *producer() {
    int item = 1;
    while (1) {
        sem_wait(emptySlots);
        sem_wait(mutex);
        table->items[table->count++] = item++;
        printf("Produced item %d\n", item - 1);
        sem_post(mutex);
        sem_post(fullSlots);
        sleep(1);
    }
}

int main() {
    // Unlink semaphores to ensure fresh initialization
    sem_unlink("/emptySlots");
    sem_unlink("/fullSlots");
    sem_unlink("/mutex");

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedTable));
    table = mmap(0, sizeof(SharedTable), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    table->count = 0;

    emptySlots = sem_open("/emptySlots", O_CREAT, 0666, TABLE_SIZE);
    fullSlots = sem_open("/fullSlots", O_CREAT, 0666, 0);
    mutex = sem_open("/mutex", O_CREAT, 0666, 1);

    pthread_t prodThread;
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_join(prodThread, NULL);

    return 0;
}