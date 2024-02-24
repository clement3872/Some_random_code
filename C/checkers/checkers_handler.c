#include <stdio.h>
#include <stdlib.h>
#include "checkers_handler.h"


int array_get(int arr[], int row, int col){
    return (arr + row * 8 + col);
    // return arr[row * 8 + col]; // this is also possible
}