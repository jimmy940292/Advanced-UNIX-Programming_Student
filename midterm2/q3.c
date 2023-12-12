#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    time_t t = time(0);
    struct tm tm2;
    char buf[256];
    localtime_r(&t, &tm2);
    //printf("%ld", t);
    strftime(buf, sizeof(buf), "%T, %A %B %d, %Y", &tm2);
    //printf("localtime: %s\n", buf);
    printf("%s\n", buf);
    return 0;
}
