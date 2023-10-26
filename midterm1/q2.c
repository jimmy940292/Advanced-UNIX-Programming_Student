#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

    int
    fread_fwrite(size_t buffer_size, char *outputName)
{
    // Open the source file for reading
    FILE *sourceFile = fopen("q2", "rb");
    if (sourceFile == NULL)
    {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file for writing
    FILE *destFile = fopen(outputName, "wb");
    if (destFile == NULL)
    {
        perror("Error opening destination file");
        fclose(sourceFile); // Close the source file before exiting
        return 1;
    }

    // // Specify the buffer size 'x'
    // size_t buffer_size = 1;

    // Create a buffer using fmemopen for reading
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL)
    {
        perror("Error allocating memory");
        fclose(sourceFile);
        fclose(destFile);
        return 1;
    }

    FILE *memStream = fmemopen(buffer, buffer_size, "w+");
    if (memStream == NULL)
    {
        perror("Error creating memory stream");
        free(buffer);
        fclose(sourceFile);
        fclose(destFile);
        return 1;
    }

    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, buffer_size, sourceFile)) > 0)
    {
        // Write data from the memory stream to the destination file
        fwrite(buffer, 1, bytes_read, destFile);
    }

    // Close the streams and free the buffer
    fclose(sourceFile);
    fclose(destFile);
    fclose(memStream);
    free(buffer);

    return 0;
}

int fgets_fputs(size_t buffer_size, char *outputName)
{
    // Open the source file for reading
    FILE *sourceFile = fopen("q2", "r");
    if (sourceFile == NULL)
    {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file for writing
    FILE *destFile = fopen(outputName, "w");
    if (destFile == NULL)
    {
        perror("Error opening destination file");
        fclose(sourceFile); // Close the source file before exiting
        return 1;
    }

    // // Specify the buffer size 'x'
    // size_t buffer_size = buffer_size;

    char buffer[buffer_size];

    while (fgets(buffer, buffer_size, sourceFile) != NULL)
    {
        // Write the data from the buffer to the destination file
        fputs(buffer, destFile);
    }

    // Close the files
    fclose(sourceFile);
    fclose(destFile);

    return 0;
}

int fgetc_fputc(char *outputName)
{
    // Open the source file for reading
    FILE *sourceFile = fopen("q2", "rb");
    if (sourceFile == NULL)
    {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file for writing
    FILE *destFile = fopen(outputName, "wb");
    if (destFile == NULL)
    {
        perror("Error opening destination file");
        fclose(sourceFile); // Close the source file before exiting
        return 1;
    }

    int c;

    while ((c = fgetc(sourceFile)) != EOF)
    {
        // Write the character 'c' to the destination file
        fputc(c, destFile);
    }

    // Close the files
    fclose(sourceFile);
    fclose(destFile);

    return 0;
}

int cal_time(int mode, size_t buffer_size, char *outputName)
{
    // if mode == 0 means fread_fwrite
    // if mode == 1 means fgets_fputs
    // else means fgetc_fputc
    struct tms start, end;
    clock_t start_real, end_real;

    if (mode == 0)
    {
        // Record the start times
        times(&start);
        start_real = clock();

        // Call the function to be measured
        fread_fwrite(buffer_size, outputName);

        // Record the end times
        times(&end);
        end_real = clock();
    }
    else if (mode == 1)
    {
        // Record the start times
        times(&start);
        start_real = clock();

        // Call the function to be measured
        fgets_fputs(buffer_size, outputName);

        // Record the end times
        times(&end);
        end_real = clock();
    }
    else
    {
        // Record the start times
        times(&start);
        start_real = clock();

        // Call the function to be measured
        fgetc_fputc(outputName);

        // Record the end times
        times(&end);
        end_real = clock();
    }

    // Calculate CPU usage in user and system mode
    double user_cpu = (double)(end.tms_utime - start.tms_utime) / sysconf(_SC_CLK_TCK);
    double system_cpu = (double)(end.tms_stime - start.tms_stime) / sysconf(_SC_CLK_TCK);

    // Calculate clock time
    double clock_time = (double)(end_real - start_real) / CLOCKS_PER_SEC;
    printf("mode: %d\n", mode);
    printf("buffer size: %zu\n", buffer_size);
    printf("User CPU time: %.2f seconds\n", user_cpu);
    printf("System CPU time: %.2f seconds\n", system_cpu);
    printf("Clock time: %.2f seconds\n\n", clock_time);

    return 0;
}
int main()
{
    cal_time(0, 1, "mode0_1");
    cal_time(0, 32, "mode0_32");
    cal_time(0, 1024, "mode0_1024");
    cal_time(0, 4096, "mode0_4096");
    cal_time(1, 4096, "mode1_4096");
    cal_time(2, 4096, "mode2_4096");

    return 0;
}
