CC=gcc
CFLAGS=-I../lib -Wall -std=c99
LDFLAGS=-L../lib -Wl,-rpath=../lib -lhelpers

all: cat

cat: cat.o libhelpers
	${CC} cat.o ${LDFLAGS} -o cat

cat.o:
	${CC} ${CFLAGS} -c cat.c

libhelpers:
	${MAKE} -C ../lib

clean:
	rm -f cat.o cat
