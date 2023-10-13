CC = gcc
CFLAG = -std=c11 -O2 -Wall
TARGET = mock_test
SRCS = mock_test.c
OBJS = mock_test.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
