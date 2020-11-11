all:
	gcc -std=c99 -o main main.c -D_REENTRANT -I/usr/include/SDL2 -lSDL2main -lSDL2
