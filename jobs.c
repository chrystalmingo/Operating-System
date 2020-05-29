#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Job.h"

int main(int argc, char* argv[]) {
    Process* head = NULL;
    Process a = {"p1", 0, 10, 0,20, NULL};
    Process b = {"p2", 0, 12, 0,60, NULL};
    Process c = {"p3", 0, 8, 0,20, NULL};

    int time = 0;
    int total_time_of_duration = 30;
    while(time!=total_time_of_duration){//We arrive commpletion time when duration becomes
    //Now we need to work on the randomness
        int winner = (rand()%  +1;


    }





/*
        int (*compare)(Process*, Process*);
    // compare = &cmpArrival;
    compare = &cmpDuration;


    head = insert(&a, head, compare);
    head = insert(&b, head, compare);
    head = insert(&c, head, compare);

    print(head);
    printf("\n");

    float avg = FIFO(head);

    print(head);
    printf("%f", avg);
    printf("\n");
    //average turnaround := completion-arrival
    
 return 0;
*/ 
}