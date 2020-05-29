//We need to learn how we create thread handle 
//We use this function below to create the thread handle and the tread must have a pointer
// pthread_create(pthread_t*, pthread_attr_t*,void*(*start_routine)(void*), void*)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void * myFunction(void* args){
    printf("%s\n", (char*)args);
    return NULL;
}

int main(){
    //initialize our threads
    pthread_t p1,p2;
    printf("main start\n");
    //create the threads
    pthread_create(&p1,NULL,myFunction,"A");
    pthread_create(&p2,NULL,myFunction,"B");
    //Once the threads are done we join them together 
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    printf("main end \n");
}

