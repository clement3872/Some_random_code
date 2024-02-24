#include <stdio.h>
#include <stdlib.h>
#include "checkers_handler.h"


int* checkers_create_grid() {
    int rows = 8; int cols = 8;
    int* arr = (int*) malloc(rows * cols * sizeof(int));

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
    
    // copying board the dynamic array
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            *(arr + i * cols + j) = board[i][j]; // arr[i][j] in multi-array syntax
        }
    }

    return arr;
}

int dyn_array_get(int* arr, int size,int row, int col){
    return *(arr + row * 8 + col);
}

int array_get(int arr[], int row, int col){
    // return (arr + row * 8 + col); // this is also possible
    return arr[row * 8 + col];
}