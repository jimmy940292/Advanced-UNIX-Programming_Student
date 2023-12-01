#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* new_pthread_barrier_wait(){

    // Lock
    pthread_mutex_lock(&mutex);

    // Critical Section
    printf("Thread %u running\n", (unsigned int)pthread_self());
    //

    // Unlock
    pthread_mutex_unlock(&mutex);

}

int main(void){

    int num_thread = 5;
    pthread_t tid[num_thread];
    void *tret;


    // Lock, Waiting for creating all threads
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < num_thread; i++)
    {
        printf("Starting thread %d\n", i);
        if (pthread_create(&tid[i], NULL, new_pthread_barrier_wait, NULL) != 0)
        {
            printf("Starting thread %d error !\n", i);
            return 0;
        }
    }

    // Unlock
    pthread_mutex_unlock(&mutex);


    // Waiting for thread termination
    for(int i = 0;i < num_thread;i++){
        if(pthread_join(tid[i], &tret) != 0){
            printf("Thead %d exit error !\n", i);
            return 0;
        }
    }

    return 0;
}