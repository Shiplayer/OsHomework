CC=gcc
CFLAGS=-Wall -std=c99 -fPIC

all: libhelpers.so

libhelpers.so: helpers.o
	$(CC) helpers.o -shared -o libhelpers.so

helpers.o: helpers.c 
	$(CC) -c $(CFLAGS) helpers.c -o helpers.o

clean:
	rm -f libhelpers.so libhelpers.o