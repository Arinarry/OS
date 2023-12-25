#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

char sh[6];
pthread_spinlock_t lock;

void* thread(void* params);

int main(void) {
    pthread_t thread_id;
    pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);

    pthread_create(&thread_id, NULL, &thread, NULL);

    while (1) {
        pthread_spin_lock(&lock);
        printf("%s\n", sh);
        pthread_spin_unlock(&lock);
        usleep(500000);
    }

    pthread_spin_destroy(&lock);
    return 0;
}

void* thread(void* params) {
    int counter = 0;
    while (1) {
        pthread_spin_lock(&lock);
        if (counter % 2) {
            sh[0] = 'H';
            sh[1] = 'e';
            sh[2] = 'l';
            sh[3] = 'l';
            sh[4] = 'o';
            sh[5] = '\0';
        } else {
            sh[0] = 'B';
            sh[1] = 'y';
            sh[2] = 'e';
            sh[3] = '_';
            sh[4] = 'u';
            sh[5] = '\0';
        }
        counter++;
        pthread_spin_unlock(&lock);
    }
    return NULL;
}