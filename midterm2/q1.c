#include <stdio.h>
#include <time.h>
#include <unistd.h>
// #include <pthread.h>

void* threadFunction(void* arg) {
    int count = 0;
    while (1) {
        sleep(10);
        count++;
        if (count % 6 == 0) {
            time_t currentTime = time(NULL);
            struct tm* localTime = localtime(&currentTime);
            printf("tm_sec: %d\n", localTime->tm_sec);
        }
    }
    return NULL;
}

int main() {
    // pthread_t thread;
    // pthread_create(&thread, NULL, threadFunction, NULL);
    // pthread_join(thread, NULL);
    int count = 0;
    while (1) {
        sleep(10);
        count++;
        if (count % 6 == 0) {
            time_t currentTime = time(NULL);
            struct tm* localTime = localtime(&currentTime);
            printf("tm_sec: %d\n", localTime->tm_sec);
        }
    }
    // return NULL;
    return 0;
}
