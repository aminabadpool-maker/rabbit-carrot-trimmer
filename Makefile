CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c11
TARGET = trimmer
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
