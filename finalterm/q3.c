#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int count;
void sig_handler(){
    printf("Alarm!\n");
    count--;
}

void setAlarm(int sec)
{
    /* do something here ... */

    signal(SIGALRM, sig_handler);
    alarm(sec);
    
}
void clearAlarm()
{
    /* do something here ... */

    int remain_timer = count;
    for(;remain_timer > 0;remain_timer--){
        alarm(0);
    }
    
}
int main(void)
{
    count = 3;

    // ...
    /* You should copy and paste these test cases to your implementation */
    setAlarm(2); // set 2 sec alarm at 0s, will finish at 2s after execution
    sleep(1);
    setAlarm(6); // set 6 sec alarm at 1s, will finish at 7s after execution
    sleep(1);
    setAlarm(3); // set 3 sec alarm at 2s, will finish at 5s after execution
    sleep(4);
    clearAlarm(); // clear all alarms at 6s after execution
    //....
    


    return 0;
}