#include <pthread.h>
#include <stdio.h>
#include <stdbool.h> 

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int product = 0;
int consumerOne = 0;
int consumerTwo = 0;
bool flag[2] = {false,false};
int priority;

//The producer function is adding 50 to product
void * Producer(void* args)
{
    for(int i = 0; i < 50; i++){
        pthread_mutex_lock(&lock);
        //critical point
        product = product + 1;
        pthread_mutex_unlock(&lock);
        }
    return NULL;
}

void * ConsumerOne(void* arg){

    //int i = 0;
    while(consumerOne + consumerTwo < 50){
        flag[0] = true;
        priority = 1;
    //Waiting for ConsumerTwo to finish its process
        while (flag[1] == true && priority == 1){
            wait();
        }
        if(consumerOne + consumerTwo < 50){
    //Once the condition of the while loop becomes false (meaning ConsumerTwo finished), ConsumerOne runs
        pthread_mutex_unlock(&lock);
    //critical point
        consumerOne = consumerOne + 1;
        product = product - 1;
        pthread_mutex_unlock(&lock);}
    //change flag back to false to show that ConsumerOne has finished its process
        flag[0] = false;
    //    i++;
    }
    return  NULL;
}


void * ConsumerTwo(void* arg){
    //int i = 0;
    while(consumerOne + consumerTwo < 50){
    //Waiting for ConsumerOne to finish its process
        flag[1] = true;
        priority = 0;
        while (flag[0] == true && priority == 0){
            wait();
        }
        if(consumerOne + consumerTwo < 50){
    //Once the condition of the while loop becomes false (meaning ConsumerOne finished), ConsumerTwo runs
        pthread_mutex_unlock(&lock);
    //critical point
        consumerTwo = consumerTwo + 1;
        product = product - 1;
        pthread_mutex_unlock(&lock);}
    //change flag back to false to show that ConsumerTwo has finished its process
        flag[1] = false;
     //   i++;
    }

    return  NULL;
}

int main(){
//Creating my threads
pthread_t p,c1, c2;
pthread_create(&p, NULL, Producer, NULL);
pthread_create(&c1, NULL, ConsumerOne, NULL);
pthread_create(&c2, NULL, ConsumerTwo, NULL);

pthread_join(p, NULL);
pthread_join(c1, NULL);
pthread_join(c2, NULL);

printf("Product = %d\n", product);
printf("Consumer One = %d\n", consumerOne);
printf("Consumer Two = %d\n", consumerTwo);
printf("The consumers evenly ate the 50 products...yay!\n");
return 0;


}
