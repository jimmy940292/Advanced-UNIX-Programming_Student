#include <stdio.h>



int* f1(int val){

    int num = 0;
    int*ptr = &num;

    if(num == 0){
        /* text had val == 0, but val is not in scope */
        int val;
        val = 5;
        ptr = &val;
        // printf("Value %d is at %p\n", *ptr, ptr);
    }
    

    return ptr;
}

void f2(void){

    int v1 = 0;
    int v2 = 5;
    int v3 = 10;
}

int main(void){

    int val = 5;
    int *ptr = f1(val);
    
    f2();

    printf("Value %d is at %p\n", *ptr, ptr);


    return 0;
}