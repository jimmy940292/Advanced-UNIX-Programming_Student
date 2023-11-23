#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static int counter;

static void
sig_usr(int signo) /* one signal handler for SIGUSR1 and SIGUSR2 */
{
    sigflag = 1;
}

static void TELL_WAIT(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        perror("signal(SIGUSR1) error");

    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        perror("signal(SIGUSR2) error");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    /* Block SIGUSR1 and SIGUSR2, and save current signal mask */
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        perror("SIG_BLOCK error");

}

static void TELL_PARENT(void)
{
    kill(getppid(), SIGUSR2); /* tell parent we’re done */
}

static void WAIT_PARENT(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask); /* and wait for parent */
    sigflag = 0;
    /* Reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

static void TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1); /* tell child we’re done */
}

static void WAIT_CHILD(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask); /* and wait for child */
    sigflag = 0;
    /* Reset signal mask to original value */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

static int increment_counter(FILE *const file)
{
    /* TODO */
    char s[256];
    sprintf(s, "%d\n", counter);
    fwrite(s, strlen(s), 1, file);
    fflush(file);
    counter+=2;
    return counter - 2;
}

int main(void)
{
    /* TODO */

    // Open file
    FILE *fp;
    fp = fopen("counter.txt", "w+");

    // Create child process
    pid_t p = fork();
    if(p < 0){
        printf("Fork error\n");
        return -1;
    }
    if (p == 0){
        // Child process
        
        // Initialize signal handler for child
        if (signal(SIGUSR1, sig_usr) == SIG_ERR)
            perror("signal(SIGUSR1) error");

        // Set counter
        counter = 1;

        // Child first write file
        TELL_WAIT();
        printf("Child incrementing, value: %d\n", increment_counter(fp));
        TELL_PARENT();

        while(counter <= 99)
        {
            WAIT_PARENT();
            TELL_WAIT();
            printf("Child incrementing, value: %d\n", increment_counter(fp));
            TELL_PARENT();
            
        }
    }else{
        // Parent process
        
        // Initialize signal handler for parent
        if (signal(SIGUSR2, sig_usr) == SIG_ERR)
            perror("signal(SIGUSR2) error");


        // Set counter
        counter = 2;


        while(counter <= 100)
        {
            WAIT_CHILD();
            TELL_WAIT();
            printf("Parent incrementing, value: %d\n", increment_counter(fp));
            TELL_CHILD(p);
        }
    }

    fclose(fp);
    return 0;

}