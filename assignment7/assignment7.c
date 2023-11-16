#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){

    // Create pipe
    int link[2];
    if (pipe(link) == -1)
    {
        printf("Create Pipe fail\n");
        exit(-1);
    }

    // Create Child Process 
    pid_t p = fork();
    if(p == 0){

    // Create New Session
    int sid = setsid();
    // printf("Sid: %d\n", sid);

    // Run 'ps' command
    char *arg[3] = {"ps","-opid,pgid,tpgid", NULL};
    // char *arg[2] = {"ps", NULL};
    close(link[0]);
    dup2(link[1], STDOUT_FILENO);
    execvp("ps", arg);

    }else{

        // Wait for pip
        sleep(1);
        close(link[1]);
        char buf[200];
        FILE * pipe_out;

        // Print output from ps command
        int nbytes = read(link[0], buf, 200);
        // printf("%d\n", nbytes);
        printf("Child Process: %d\n", p);
        printf("%s\n", buf);
        
    }

    return 0;
}