All: start

start: compile
	./main

compile: main.o
	gcc -g main.o -o main

.SUFFIXES: .o .c

.c.o:
	gcc -g -c $*.c -Wall -O2 -ansi

order:
	rm -f *.o

clean: order
	rm -f main
