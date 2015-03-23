CC=gcc
CFLAGS=-I../lib -Wall -ggdb 
LDFLAGS=-L../lib -Wl,-rpath=../lib -lhelpers

all: revwords

revwords: revwords.o
	${CC} revwords.o ${LDFLAGS} -o revwords

revwords.o:
	${CC} ${CFLAGS} -c revwords.c

clean:
	rm -f revwords.o revwords
