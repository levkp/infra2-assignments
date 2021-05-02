#include <stdio.h>
#include "pointer-practice.h"

void printArray(int array[MAX_INT]) 
{
    printf("Content of array:\n");
    for (int i = 0; i < MAX_INT; i++) {
        printf("Address: %p has value: %d\n", &array[i], array[i]);   
    }
}

void makeArray(int array[]) 
{
    for (int i = 0; i < MAX_INT; i++) {
        array[i] = i * SEVENFOLD;
    }
}
