all:
	gcc -o main main.c -D_REENTRANT -I/usr/include/SDL2 -lSDL2main -lSDL2
