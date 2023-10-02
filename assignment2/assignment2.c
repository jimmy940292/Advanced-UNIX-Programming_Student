#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    
    char c; // buffer to store the char ready to read and write
    int read_sit; // read situation, which is the return value from read()

    // argv[0] is the exec file name
    int ref_fd = open(argv[1], O_RDONLY); 
    int tar_fd = open(argv[2], O_TRUNC | O_RDWR | O_CREAT);

    struct stat info; // for storing the file mode
    stat(argv[1], &info); // get ref file mode
    // printf("Permissions are: %08x\n", info.st_mode);
    chmod(argv[2], info.st_mode); // change tar file mode
    // stat(argv[2], &info);
    // printf("Permissions are: %08x\n", info.st_mode);
    
    lseek(ref_fd, 0, SEEK_SET); // move cursor (ref file) to first
    lseek(tar_fd, 0, SEEK_SET); // move cursor (ref file) to first
    
    read_sit = read(ref_fd, &c, 1);
    while(read_sit!=0){
        write(tar_fd, &c, 1);
        // printf("%c", c);
        read_sit = read(ref_fd, &c, 1);
    }

    close(ref_fd);
    close(tar_fd);
}