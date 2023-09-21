#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
    char c; // buffer to store the char ready to print
    int read_sit; // read situation, which is the return value from read()
    char newString[] = "NTHU student.\n";
    
    // Task 1
    // Task 3 (Append Flag => O_RDWR)
    int fd = open("sample.txt", O_RDWR); // [TODO]

    lseek(fd, 14, SEEK_SET); // move cursor to 14, which is "s"
    for(int i = 0; i < 8; i++){ // "student." have 8 char
        read_sit = read(fd, &c, 1); // read one char and save to the buffer
        printf("%c", c);
    }
    printf("\n"); // extra newline for demo
    

    // Task 2
    lseek(fd, 14, SEEK_SET); // move cursor to 14, which is "s"
    write(fd, newString, strlen(newString));
    
    lseek(fd, 0, SEEK_SET); // move cursor to first
    
    do{
        read_sit = read(fd, &c, 1);
        printf("%c", c);
    }while(read_sit!=0); // if read_sit == 0, means EOF

    close(fd);
}