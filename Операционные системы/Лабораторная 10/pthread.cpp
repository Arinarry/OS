#include <pthread.h>
#include <vector>
#include <chrono>
#include <iostream>

using namespace std;

void* get_sum1(void*);
void* get_sum2(void*);
void* get_sum3(void*);
void* get_sum4(void*);

vector<int> v;
long int sum = 0;

// Реализация блокировки Петерсона
int turn = 0;
int flag[2] = {0, 0};

void lock(int self) {
    flag[self] = 1;
    turn = 1 - self;
    while (flag[1 - self] && turn == 1 - self) {}
}

void unlock(int self) {
    flag[self] = 0;
}

void* get_sum1(void*) {
    for (int i = 0; i < 250; ++i) {
        lock(0);
        sum += v[i];
        unlock(0);
    }
    return NULL;
}

void* get_sum2(void*) {
    for (int i = 250; i < 500; ++i) {
        lock(1);
        sum += v[i];
        unlock(1);
    }
    return NULL;
}

void* get_sum3(void*) {
    for (int i = 500; i < 750; ++i) {
        lock(0);
        sum += v[i];
        unlock(0);
    }
    return NULL;
}

void* get_sum4(void*) {
    for (int i = 750; i < 1000; ++i) {
        lock(1);
        sum += v[i];
        unlock(1);
    }
    return NULL;
}

int main() {
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i + 1);
    }
    auto r_tnow = std::chrono::high_resolution_clock::now();
    pthread_t t1, t2, t3, t4;
    int idt1 = pthread_create(&t1, NULL, get_sum1, NULL);
    int idt2 = pthread_create(&t2, NULL, get_sum2, NULL);
    int idt3 = pthread_create(&t3, NULL, get_sum3, NULL);
    int idt4 = pthread_create(&t4, NULL, get_sum4, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    auto r_time = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now() - r_tnow);
    cout << "Pthread-lib\t" << sum << "\t" << r_time.count() * 1e-9 << "\n";

    return 0;
}
