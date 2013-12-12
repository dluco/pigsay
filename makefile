CC=gcc
CFLAGS=-c -g -ansi -Wall

all: pigsay

pigsay: pigsay.o
	$(CC) pigsay.o -o pigsay

pigsay.o: pigsay.c
	$(CC) $(CFLAGS) pigsay.c

clean:
	-rm -f pigsay pigsay.o
