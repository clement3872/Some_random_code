#ifndef CHECKERS_HANDLER_H
#define CHECKERS_HANDLER_H
unsigned int array_get(unsigned int arr[], int row, int col);
int dync_array_get(int* arr, int row, int col);
int* dync_array_append(int* arr, int current_size, int new_item);
#endif