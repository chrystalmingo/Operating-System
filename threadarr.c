#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "rdtsc.h"
int size = 100000000;
void * myFunction(void* args){
    int *arr = (int*)args;
    for(int i = 0;i<size/4;i++){
        arr[i]= 50;
    }
    return NULL;
}

int main(){
    int* arr = malloc(size * sizeof(int));
    //initialize our threads
    pthread_t p1,p2,p3,p4;
    //time
    int sTime = rdtsc();
    printf("main start\n");
    //create the threads
    pthread_create(&p1,NULL,myFunction,arr);
    pthread_create(&p2,NULL,myFunction,arr+25000000);
    pthread_create(&p3,NULL,myFunction,arr+50000000);
    pthread_create(&p4,NULL,myFunction,arr+75000000);
    //Once the threads are done we join them together 
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    pthread_join(p4,NULL);
    int eTime = rdtsc();
    printf("single threads ticks = %d", eTime-sTime);
    printf(" main end \n");
}
