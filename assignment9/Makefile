CC = gcc
CFLAG =  -std=c11 -O2 -Wall 
TARGET = assignment9
SRCS = assignment9.c
OBJS = assignment9.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS) -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -lpthread

clean:
	rm -f $(OBJS) $(TARGET)
