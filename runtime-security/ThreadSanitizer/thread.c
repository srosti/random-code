#include <stdio.h>
#include <pthread.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
int my_global = 0;


void *thread1() {
    printf("Hello Thread\n");
    pthread_mutex_lock(&my_mutex);
    my_global = 51;
    pthread_mutex_unlock(&my_mutex);
}

int main() {
    pthread_t my_thread;
    printf("global=%d\n", my_global);
    int result = pthread_create(&my_thread, 0, thread1, 0);
    if (result != 0) {
        printf("Error creating thread");
    }
    pthread_join(my_thread, NULL);
    printf("global=%d\n", my_global);
    return 1;
}