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
    char *arg[3] = {"ps", "-opid,pgid,tpgid,sid,command", NULL};
    // char *arg[2] = {"ps", NULL};
    if(p == 0){

    // Create New Session
    int new_sid = setsid();
    printf("New Session id: %d\n", new_sid);
    int new_pgid = getpgrp();
    printf("New Group id: %d\n", new_pgid);

    // Run 'ps' command
    
    close(link[0]);
    dup2(link[1], STDOUT_FILENO);
    execvp("ps", arg);
    }else{

        // Wait for pipe
        // sleep(1);
        close(link[1]);
        char buf[200];
        FILE * pipe_out;

        // Print output from ps command
        int nbytes = read(link[0], buf, 200);
        // printf("%d\n", nbytes);
        printf("Child Process: %d\n", p);
        printf("Parent Process: %d\n", getpid());      
        printf("%s\n", buf);
        
    }

    return 0;
}