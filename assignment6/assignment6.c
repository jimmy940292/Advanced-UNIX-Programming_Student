#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main(void){

    pid_t p = fork();
    int link[2];

    // Create pipe
    if(pipe(link) == -1){
        printf("Create Pipe fail\n");
        exit(-1);
    }

    if(p<0){
        printf("Fork fail\n");
    }else if(p == 0){

        // Create Zombie process
        exit(0);
    }else if(p != 0){
        
        char *arg[2] = {"ps",NULL};
        // Create process to run ps command 
        // And pipe the output to main process
        pid_t ps_p = fork();

        if(ps_p == 0){
            close(link[0]);
            dup2(link[1], STDOUT_FILENO);

            execvp("ps", arg);

        }else{
            close(link[1]);
            sleep(1);
            char buf[200];
            FILE * pipe_out;
            // Print output from ps command
            int nbytes = read(link[0], buf, 200);
            // printf("%d\n", nbytes);
            printf("%s\n", buf);
            int status;
            sleep(5);

        }

        
        // wait(NULL);
    }


    return 0;
}