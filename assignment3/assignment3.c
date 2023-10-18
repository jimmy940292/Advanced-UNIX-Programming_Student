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
    // printf("Read\n");
    // printf("buf: %s\n", buf);
    // printf("size: %d\n", size);
    // printf("cookie: %s\n", cookie);
    // int tmp = fread(&buf, 1, 12, cookie);
    // printf("c: %c\n", fgetc(cookie));
    // printf("tmp: %d\n", tmp);
    return fread(buf, 1, size, cookie);
}

int write_to_memory(void *cookie, const char *buf, int size)
{
    // printf("Write\n"); // for checking
    // printf("%s\n", buf); // for checking
    // printf("%d\n", size); // for checking
    return fwrite(buf, 1, size, cookie);
}

int seek_memory(void *cookie, long offset, int whence)
{
    // printf("Seek\n");
    // printf("%ld\n", offset);
    FILE *memfile = (FILE *)cookie;
    return fseek(memfile, (long)offset, whence);
}

int close_memory(void *cookie)
{
    // Implement closing your memory buffer here.
    // printf("Close\n");
    fclose(cookie); // close the file
    return 0;
}

int main()
{
    size_t numwritten;
    char input_data[12] = "hello, world"; // len = 12
    char new_buffer[1024];

    FILE *file = fmemopen(new_buffer, 1024, "rw");
    FILE *customStream = funopen(file, read_from_memory, write_to_memory, seek_memory, close_memory);

    size_t bytesWrite = write_to_memory(file, input_data , 12);
    // printf("bytesWrite: %zu\n", bytesWrite);

    char buffer[1024] = "";

    // Print "world"
    int seekPos = seek_memory(file, 7, SEEK_SET);
    // printf("seekPos: %d\n", seekPos);

    size_t bytesRead = read_from_memory(file, buffer, 5);
    // printf("%zu\n", bytesRead);
    printf("%s\n", buffer);

    // Print "hello, world"
    seekPos = seek_memory(file, 0, SEEK_SET);
    // printf("seekPos: %d\n", seekPos);

    bytesRead = read_from_memory(file, buffer, 12);
    // printf("%zu\n", bytesRead);
    printf("%s\n", buffer);

    fclose(customStream); // trigger the close_to_memory function
    return 0;
}