#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

char sh[6];
int turn = 0;
int flag[2] = {0, 0};

void* thread(void* params);

int main(void) {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &thread, NULL);

    while (1) {
        flag[0] = 1; // устанавливаем флаг для потока 0
        turn = 1;    // передаём ход потоку 1
        while (flag[1] && turn == 1) {}  // ожидаем, пока поток 1 не закончит свою работу
        // Критическая секция начинается
        printf("%s\n", sh);
        // Критическая секция заканчивается
        flag[0] = 0;  // сбрасываем флаг для потока 0
        usleep(500000);
    }

    return 0;
}

void* thread(void* params) {
    int counter = 0;
    while (1) {
        flag[1] = 1; // устанавливаем флаг для потока 1
        turn = 0;    // передаём ход потоку 0
        while (flag[0] && turn == 0) {}  // ожидаем, пока поток 0 не закончит свою работу
        // Критическая секция начинается
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
        // Критическая секция заканчивается
        flag[1] = 0; // сбрасываем флаг для потока 1
    }
    return NULL;
}
