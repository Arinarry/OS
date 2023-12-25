#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> sh(0);
std::atomic<int> turn(0);
std::atomic<int> flagReady[2] = {0, 0};

void *my_thread0(void* arg) {
    int i = 0;
    for (; i <= 100; i++) {
        flagReady[0] = 1;
        turn = 1;

        while (flagReady[1] && turn == 1) {
            std::this_thread::yield();
        }

        sh += 1;

        flagReady[0] = 0;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    return nullptr;
}

void *my_thread1(void* arg) {
    int i = 0;
    for (; i <= 100; i++) {
        flagReady[1] = 1;
        turn = 0;

        while (flagReady[0] && turn == 0) {
            std::this_thread::yield();
        }

        sh += 2;

        flagReady[1] = 0;
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    return nullptr;
}

int main() {
    pthread_t th_id[2];

    pthread_create(&th_id[0], nullptr, &my_thread0, nullptr);
    pthread_create(&th_id[1], nullptr, &my_thread1, nullptr);

    // Ждем завершения обоих потоков
    pthread_join(th_id[0], nullptr);
    pthread_join(th_id[1], nullptr);

    std::cout << sh << std::endl;
    return 0;
}
