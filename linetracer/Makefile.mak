CC = gcc
CFLAGS = -Wall -lwiringPi
TARGET = linetracer

all: $(TARGET)

$(TARGET): main.o
	$(CC) -o $(TARGET) main.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	rm -f *.o $(TARGET)