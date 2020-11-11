#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>


// define the screen
#define WIDTH 600
#define HEIGHT 600

// define how big the maze is
#define row 60
#define col 60


// define all the states a cell can have
#define visited 0
#define wall 1
#define unvisited 2

// define the grid
int arr[row][col];

// recursive prototype
void createMaze(int, int); 
// neightbour check
int hasUnvisitedNeighbour(int, int);

// directions
int dir[4][2] = {
    {0, -2},
    {-2, 0},
    {0, 2},
    {2, 0}
};

int main() {
    // boilerplate code for SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow(
            "MAZE",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            SDL_WINDOW_SHOWN
            );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // create the wall
    SDL_Rect wallRect = {.w = WIDTH/col, .h = HEIGHT/row};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);



    // initiate the randomness
    srand(time(0));


    // initiate the grid
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i%2 || j%2) arr[i][j] = wall;
            else arr[i][j] = unvisited;
        }
    }

    // call the recursive function
    createMaze(0, 0);

    // show the maze
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (arr[i][j] == wall) {
                wallRect.x = j * wallRect.w;
                wallRect.y = i * wallRect.h;
                SDL_RenderFillRect(renderer, &wallRect);
            }
        }
    }

    // everything done, now finishing
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}

void createMaze(int i, int j) {
    // mark the cell as visited
    arr[i][j] = visited;
    while (1) {
        int p = hasUnvisitedNeighbour(i, j);
        if (p==-1) return;
        int ni = i + dir[p][0];
        int nj = j + dir[p][1];
        arr[(i+ni)/2][(j+nj)/2] = visited;
        createMaze(ni, nj);
    }
}


int hasUnvisitedNeighbour(int i, int j) {
    // make a list of all the unvisited neighbours
    int list[4];
    int count = 0;
    if (i-2 >= 0 && arr[i-2][j] == unvisited) {
        list[count] = 1; ++count;
    }
    if (i+2 < row && arr[i+2][j] == unvisited) {
        list[count] = 3; ++count;
    }
    if (j-2 >= 0 && arr[i][j-2] == unvisited) {
        list[count] = 0; ++count;
    }
    if (j+2 < col && arr[i][j+2] == unvisited) {
        list[count] = 2; ++count;
    }
    if (count) return list[rand() % count];
    return -1;
}







