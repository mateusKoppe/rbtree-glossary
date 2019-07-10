All: start

start: compile

dev:
	gcc -g main.c rbtree/rbtree.c cmdtool/cmdtool.c -Wall -O2 -ansi -Wno-unused-result  -o main
	gdb main

test: start
	./main < input.txt > output.txt
	cat output.txt

compile: main.o rbtree/rbtree.o cmdtool/cmdtool.o
	gcc main.o rbtree/rbtree.o cmdtool/cmdtool.o -o main

clean:
	rm -f main
	rm -f *.o

.SUFFIXES: .o .c
.c.o:
	gcc -c $*.c -Wall -O2 -ansi -Wno-unused-result -o $*.o


