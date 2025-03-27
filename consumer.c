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

sem_t *emptySlots, *fullSlots, *mutex;
SharedTable *table;
int shm_fd;

void *consumer() {
    while (1) {
        sem_wait(fullSlots);
        sem_wait(mutex);

        int item = table->items[--table->count];
        printf("Consumed item %d\n", item);
        
        sem_post(mutex);
        sem_post(emptySlots);
        sleep(2);
    }
}

int main() {
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    table = mmap(0, sizeof(SharedTable), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    emptySlots = sem_open("/emptySlots", O_CREAT, 0666, TABLE_SIZE);
    fullSlots = sem_open("/fullSlots", O_CREAT, 0666, 0);
    mutex = sem_open("/mutex", O_CREAT, 0666, 1);

    pthread_t consThread;
    pthread_create(&consThread, NULL, consumer, NULL);
    pthread_join(consThread, NULL);

    return 0;
}