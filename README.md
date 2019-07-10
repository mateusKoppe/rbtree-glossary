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

| Command                  | Description                          |
|--------------------------|--------------------------------------|
| `h`                      | Help                                 |
| `i <word> <description>` | Add the word and it's description    |
| `e <word>`               | Erase the word and it's descriptions |
| `e <word> <description>` | Erase the word's description         |
| `q <word>`               | List words and it's descriptions     |
| `p`                      | List all words and descriptions      |

## Make scripts
- `make`: The same as `make compile`;
- `make dev`: compiles and run `main` with `gdb` to debug;
  - Note: you need to install gdb to debug
- `make test`: Compiles and uses `./input.txt` as the input, saves it in `./output.txt`;
  - Note: You have to create the `./input.txt` file
- `make compile`: Compiles the code
- `make clean`: Removes the binary files

## Contributing
Tips, discussions and bug reports are very welcome, feel free to open an issue.
There is no need for code contribuition.

## License
Feel free to use this code for whatever you want. I'll be happy if it helps you with something. :]