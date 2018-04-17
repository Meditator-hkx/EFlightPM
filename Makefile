CC=gcc
FLAGS=-I.

ptest: test.o init.o
	gcc -o ptest test.o init.o -I.
test.o: test.c init.c
	gcc -c test.c init.c
clean:
	rm -f *.o ptest
