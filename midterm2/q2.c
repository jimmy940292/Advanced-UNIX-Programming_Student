#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <ftw.h>

#define MAX_PATH 513

static int print_symlink(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    if (typeflag == FTW_SL) {
        // Check if symbolic link exists
        char actualpath[MAX_PATH];
        if (access(fpath, 0) == 0) {

            if (realpath(fpath, actualpath) != NULL) 
                printf("%s -> %s\n", fpath, actualpath);
            else 
                perror("realpath");    
        }
        else 
            // Symbolic link is broken or inaccessible
            printf("Inaccessible symbolic link: %s -> %s\n", fpath, actualpath);
        
    }

    return 0;
}

int main(int argc, char *argv[]){
    //Incorrect usage. Only one argument is allowed
    if (argc != 2) 
        exit(EXIT_FAILURE);
    

    if (nftw(argv[1], print_symlink, 10, FTW_PHYS) == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }

    return 0;
}
