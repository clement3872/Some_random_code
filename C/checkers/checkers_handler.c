#include <stdio.h>
#include <stdlib.h>
#include "checkers_handler.h"


int* checkers_create_grid(int rows, int cols) {
    int* arr = malloc(rows * cols * sizeof(int));

    const int board[8][8] = {
        {0, 2, 0, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 2, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0} 
    };
    
    // Example initialization
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            *(arr + i * cols + j) = board[i][j]; // arr[i][j] in multi-array syntax
        }
    }

    return arr;
}


int array_get(int* arr, int row, int col){
    return *(arr + row * 8 + col);
}