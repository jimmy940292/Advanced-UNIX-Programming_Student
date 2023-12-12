#include <stdio.h>
int* f1(int* val){

    int num = 0;
    int*ptr = &num;
    // printf("Value %d is at %p in function f1\n", *val, val);

    if(num == 0){
        /* text had val == 0, but val is not in scope */
        // int val;
        // val = 5;
        ptr = val;
        printf("Value %d is at %p in function f1\n", *ptr, ptr);
    }
    
    return ptr;
}
int main(void){

    int val = 5;
    printf("Value %d is at %p \n", val, &val);
    int *ptr = f1(&val);
    
    printf("Value %d is at %p\n", *ptr, ptr);

    return 0;
}