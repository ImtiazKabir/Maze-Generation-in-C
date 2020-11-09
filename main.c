#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define how big the maze is
#define row 19
#define col 19


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
    // initiate the randomness
    srand(time(0));


    // initiate the grid
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i%2) arr[i][j] = wall;
            else if (j%2) arr[i][j] = wall;
            else arr[i][j] = unvisited;
        }
    }

    // call to the recursive function
    createMaze(0, 0);

    // show the maze
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
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
    if (i-2 >= 0 && arr[i-2][j] == unvisited) list[count++] = 1;
    if (i+2 < row && arr[i+2][j] == unvisited) list[count++] = 3;
    if (j-2 >= 0 && arr[i][j-2] == unvisited) list[count++] = 0;
    if (j+2 < col && arr[i][j+2] == unvisited) list[count++] = 2;
    if (count) return list[rand() % count];
    return -1;
}






