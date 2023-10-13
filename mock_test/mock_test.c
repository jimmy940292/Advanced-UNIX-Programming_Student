#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char list[100][100];

    int params_c = 0;
    int params_i = 0;
    int params_u = 0;

    // Read parameters
    for(int i = 1;i < argc;i++)
    {
        if(argv[i] == "c")
        {
            params_c = 1;
        }
        else if (argv[i] == "i")
        {
            params_i = 1;
        }
        else if (argv[i] == "u")
        {
            params_u = 1;
        }
        
    }

    // Read file
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int index = 0;
    fp  = fopen(argv[argc-1], "r");

    while ((read = getline(&line, &len, fp)) != -1)
    {
        strcpy(list[index], line);
        // printf("%s", line);
        index++;
    }
    fclose(fp);


    // Print Line

    char temp[100];
    strcpy(temp, list[0]);
    for(int i = 0;i < index; i++)
    {
        if(i ==0)
        {
            printf("%s", list[i]);
        }
        else
        {
            if(strcmp(temp, list[i]) != 0)
            {
                printf("%s", list[i]);
            }
        }

        strcpy(temp, list[i]);
    }

    printf("\n");
    return 0;
}