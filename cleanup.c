#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/shm_table"

int main() {
    // Unlink shared memory
    if (shm_unlink(SHM_NAME) == 0) {
        printf("Shared memory unlinked successfully.\n");
    } else {
        perror("Failed to unlink shared memory");
    }

    // Unlink semaphores
    if (sem_unlink("/emptySlots") == 0) {
        printf("Semaphore /emptySlots unlinked successfully.\n");
    } else {
        perror("Failed to unlink semaphore /emptySlots");
    }

    if (sem_unlink("/fullSlots") == 0) {
        printf("Semaphore /fullSlots unlinked successfully.\n");
    } else {
        perror("Failed to unlink semaphore /fullSlots");
    }

    if (sem_unlink("/mutex") == 0) {
        printf("Semaphore /mutex unlinked successfully.\n");
    } else {
        perror("Failed to unlink semaphore /mutex");
    }

    return 0;
}
