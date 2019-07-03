All: start

start: compile

dev:
	gcc -g main.c rbtree/rbtree.c cmdtool/cmdtool.c helpers/helpers.c -Wall -O2 -ansi -Wno-unused-result  -o main
	gdb main

test: start
	./main < input.txt > output.txt
	cat output.txt

compile: main.o rbtree/rbtree.o cmdtool/cmdtool.o helpers/helpers.o
	gcc main.o rbtree/rbtree.o cmdtool/cmdtool.o helpers/helpers.o -o main

.SUFFIXES: .o .c
.c.o:
	gcc -c $*.c -Wall -O2 -ansi -Wno-unused-result -o $*.o

order:
	rm -f *.o

clean: order
	rm -f main
