#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

struct CustomStream
{
    FILE *file;      // output file data
    char *buffer;    // Data buffer
    size_t size;     // Total size of the data buffer
    size_t position; // Current position in the buffer
};

int read_from_memory(void *cookie, char *buf, int size)
{
    printf("Read\n");
    printf("buf: %s\n", buf);
    printf("size: %d\n", size);
    int tmp = fread(&buf, 1, size, cookie);
    printf("c: %c\n", fgetc(cookie));
    printf("tmp: %d\n", tmp);
    return fread(&buf, 1, size, cookie);
}

int write_to_memory(void *cookie, const char *buf, int size)
{
    printf("Write\n"); // for checking
    // printf("%s\n", buf); // for checking
    // printf("%d\n", size); // for checking
    return fwrite(buf, 1, size, cookie);
}

int seek_memory(void *cookie, long offset, int whence)
{
    printf("Seek\n");
    printf("%ld\n", offset);
    FILE *memfile = (FILE *)cookie;
    return fseek(memfile, (long)offset, whence);
}

int close_memory(void *cookie)
{
    // Implement closing your memory buffer here.
    printf("Close\n");
    fclose(cookie); // close the file
    return 0;
}

int main()
{
    size_t numwritten;
    char input_data[12] = "hello, world"; // len = 12

    FILE *file = fopen("output.txt", "w");
    FILE *customStream = funopen(file, read_from_memory, write_to_memory, seek_memory, close_memory);

    size_t bytesWrite = fwrite(input_data, 1, 12, customStream);
    printf("bytesWrite: %zu\n", bytesWrite);

    int seekPos = fseek(customStream, 0, SEEK_SET);
    printf("seekPos: %d\n", seekPos);

    char buffer[1024];
    size_t bytesRead = fread(buffer, 1, 12, customStream);
    printf("%zu\n", bytesRead);
    printf("%s\n", buffer);

    fclose(customStream); // trigger the close_to_memory function
    return 0;
}