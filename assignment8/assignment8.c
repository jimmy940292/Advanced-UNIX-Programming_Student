#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

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
    static int counter = 1;
    char s[256];
    sprintf(s, "%d", counter);
    fwrite(s, sizeof(s), 1, file);

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
        int counter = increment_counter(fp);
        printf("Child incrementing, value: %d\n", counter);
        TELL_PARENT();
        while (counter < 99)
        {
            WAIT_PARENT();
            counter = increment_counter(fp);
            printf("Child incrementing, value: %d\n", counter);
            TELL_PARENT();
        }
    }else{
        // Parent process

        // Let child first write counter
        sleep(1);
        int counter = 0;
        while (counter < 100)
        {
            WAIT_CHILD();
            counter = increment_counter(fp);
            printf("Parent incrementing, value: %d\n", counter);
            TELL_CHILD(p);
        }
    }

    fclose(fp);
    return 0;

}