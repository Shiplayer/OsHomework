CC=gcc
CFLAGS=-I../lib -Wall -ggdb
LDFLAGS=-L../lib -Wl,-rpath=../lib -lhelpers

all: lenwords

lenwords: lenwords.o
	${CC} lenwords.o ${LDFLAGS} -o lenwords

lenwords.o: 
	${CC} -c lenwords.c ${CFLAGS} 

clean:
	rm -f lenwords.o lenwords
