#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void sleep_us(unsigned long microsec)
{
    struct timeval tv;
    tv.tv_sec = microsec / 1000000;
    tv.tv_usec = microsec % 1000000;
    select(0, NULL, NULL, NULL, &tv);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return EXIT_FAILURE;
    }
    unsigned long sleep_t = strtoul(argv[1], NULL, 10);
    struct timeval start_t, end_t;
    gettimeofday(&start_t, NULL);
    sleep_us(sleep_t);
    gettimeofday(&end_t, NULL);
    long elapse = (end_t.tv_sec - start_t.tv_sec) * 1000000 + (end_t.tv_usec - start_t.tv_usec);
    printf("Sleep time: %ld us\n", elapse);
    return EXIT_SUCCESS;
}