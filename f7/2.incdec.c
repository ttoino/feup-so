#include <pthread.h>
#include <stdio.h>

int count = 0;
pthread_mutex_t lock;

void *inc(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
        if (count < 0)
            printf(".");
    }
    return NULL;
}

void *dec(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);
        count--;
        pthread_mutex_unlock(&lock);
        if (count < 0)
            printf(".");
    }
    return NULL;
}

int main() {
    printf("Start: %d\n", count);

    pthread_mutex_init(&lock, NULL);

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, inc, NULL);
    pthread_create(&tid2, NULL, dec, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&lock);

    printf("End: %d\n", count);
}
