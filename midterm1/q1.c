#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int params_c = 0;
int params_i = 0;
int params_u = 0;
int tot_index = 0;
int opt;

int compare_func(char *s1, char *s2){
    
    if(params_i == 1){
        return strcasecmp(s1, s2);
    }
    else{
        return strcmp(s1, s2);
    }
}



int find_func(char **list, char * tar, int *count, int cur_index){
    
    // return 0 if it is not unique
    // return 1 if it is unique

    if (compare_func(list[cur_index - 1], tar) != 0)
    {

        if (params_u == 1 && cur_index + 1 < tot_index  && compare_func(list[cur_index + 1], tar) == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        count[cur_index - 1] += count[cur_index];
        return 0;
    }
}

int cmp(const void *a, const void *b){
    // printf("%s : %s\n", *(const char **)a, *(const char **)b);
    return strcmp(*(const char **)a, *(const char **)b);
}

// int new_cmp(const void *a, const void *b)
// {
//     // printf("%s : %s\n", *(const char **)a, *(const char **)b);

//     // Compare case
//     if(strcasecmp(*(const char **)a, *(const char **)b) == 0){
//         return -1 * strcmp(*(const char **)a, *(const char **)b);
//     }else{
//         return strcasecmp(*(const char **)a, *(const char **)b);
//     }

// }

int main(int argc, char *argv[])
{
    char *list[100];
    int count[100];
    int print[100];

    // Read parameters
    while ((opt = getopt(argc, argv, "iuc")) != -1)
    {
        switch (opt)
        {
        case 'i':
            params_i = 1;
            break;
        case 'u':
            params_u = 1;
            break;
        case 'c':
            params_c = 1;
            break;
        case '?':
            if (opt == 'i' || opt == 'u' || opt == 'c')
            {
                fprintf(stderr, "Option -%c requires an argument.\n", opt);
            }
            else
            {
                fprintf(stderr, "Unknown option -%c\n", opt);
            }
            return 1;
        default:
            abort();
        }
    }
    
    // printf("c: %d\n", params_c);
    // printf("i: %d\n", params_i);
    // printf("u: %d\n", params_u);
    // printf("s: %d\n", params_s);

    // Initialize
    for(int i = 0;i < 100;i++){
        list[i] = malloc(100 * sizeof(char));
        count[i] = 1;
        print[i] = 0;
    }

    // Read file
    FILE * fp;
    char line_buf[100];
    int len = 100;
    
    fp  = fopen(argv[argc-1], "r");

    while (fgets(line_buf, 100, fp))
    {
        strcpy(list[tot_index], line_buf);

        // printf("%c", list[tot_index][0]);
        tot_index++;
    }
    fclose(fp);

    // (BUG)
    // Add nextline in the last string
    // strcat(list[tot_index - 1], "\n");

    // Sort Function
    qsort(list, tot_index, sizeof(const char *), cmp);
    // qsort(list, tot_index, sizeof(const char *), cmp);

    // for(int i = 0;i < tot_index; i++){
    //     printf("%s", list[i]);
    // }


    // Unique Function
    for (int i = tot_index - 1; i >= 0; i--)
    {
        if(i == 0)
        {
            print[i] = 1;
        }
        else
        {

            if (find_func(list, list[i], count, i))
            {
                print[i] = 1;
            }
        }

    }

    

    // Print Function
    for(int i = 0;i < tot_index;i++){
        
        if(print[i] == 1){
            if (params_c == 1)
            {
                printf("      %d %s", count[i], list[i]);
            }
            else
            {
                printf("%s", list[i]);
            }
        }
        
    }


    // Free Space
    for(int i = 0;i < tot_index;i++){
        free(list[i]);
    }

    return 0;
}