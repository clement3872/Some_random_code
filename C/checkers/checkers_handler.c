#include <stdio.h>
#include <stdlib.h>
#include "checkers_handler.h"

unsigned int array_get(unsigned int arr[], int row, int col){
    if (row >= 0 && col >= 0){
        return *(arr + row * 8 + col); 
        // return arr[row * 8 + col]; // this is also possible
    }
    else {
        printf("An index has to be positive");
        // returns nothing so it will make an error
    }
}

int dync_array_get(int* arr, int row, int col){
    if (row >= 0 && col >= 0){
        return *(arr + row * 8 + col); 
        // return arr[row * 8 + col]; // this is also possible
    }
    else {
        printf("An index has to be positive");
        // returns nothing so it will make an error
    }
}

int* dync_array_append(int* arr, int current_size, int new_item){
    int* temp = (int*) realloc(arr, (current_size+1) * sizeof(int));
    if (temp == NULL) {
        // Handle reallocation failure
        printf(stderr, "Memory reallocation failed\n");
        free(arr); // It's important to free the original array if not using it anymore
        return 1;
    }
    arr = temp; // Update the array pointer if reallocation succeeded
    arr[current_size] = new_item;
    return arr;
}
