#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rdtsc.h"

int main(){
    int size = 100000000;
    int* arr = malloc(size * sizeof(int));
    int sTime = rdtsc();
    for(int i = 0; i<size; i++){
        arr[i]=50;
    }
    int eTime = rdtsc();
    printf("single threads ticks = %d", eTime-sTime);
}