All: start

start: compile

dev:
	gcc -g main.c rbtree/rbtree.c cmdtool/cmdtool.c -Wall -O2 -ansi -Wno-unused-result  -o main
	gdb main

compile: main.o rbtree/rbtree.o cmdtool/cmdtool.o
	gcc main.o rbtree/rbtree.o cmdtool/cmdtool.o -o main

.SUFFIXES: .o .c
.c.o:
	gcc -c $*.c -Wall -O2 -ansi -Wno-unused-result -o $*.o

order:
	rm -f *.o

clean: order
	rm -f main
