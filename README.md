#  RbTree - Glossary

## About
A simple glossary implementated with a [Red-Black Tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) in C.

This project was made as a Data Structure work in UFFS.

## Setup

Compiling using gcc:
```bash
gcc -c rbtree/rbtree.c -Wall -O2 -ansi -Wno-unused-result -o rbtree/rbtree.o
gcc -c cmdtool/cmdtool.c -Wall -O2 -ansi -Wno-unused-result -o cmdtool/cmdtool.o
gcc -c main.c -Wall -O2 -ansi -Wno-unused-result -o main.o
gcc main.o rbtree/rbtree.o cmdtool/cmdtool.o -o main
```

Or with make just run:
```
make
```

## Runing
After compiling just run the `main` file
```
./main
```

When software are running you can use these commands:

| Command                  | Description                          |
|--------------------------|--------------------------------------|
| `h`                      | Help                                 |
| `i <word> <description>` | Add the word and it's description    |
| `e <word>`               | Erase the word and it's descriptions |
| `e <word> <description>` | Erase the word's description         |
| `q <word>`               | List words and it's descriptions     |
| `p`                      | List all words and descriptions      |
| `t`                      | Shows the glossary tree              |

## Make scripts
There are some Make scripts that may help you:
- ```bash
  make # The same as `make compile`
  ```
- ```bash
  make dev # Compiles and run `main` with `gdb` to debug;
  #Note: you need to install gdb to debug
  ```
- ```bash
  make test # Compiles and uses `./input.txt` as the input, saves it in `./output.txt`;
  #Note: You have to create the `./input.txt` file
  ```
- ```bash
  make compile # Compiles the code
  ```
- ```bash
  make clean # Removes the binary files
  ```
