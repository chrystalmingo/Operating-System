#include <stdio.h>
#include <stdlib.h>

//This creates the structure for the Node
//The Job has a name, srrival time, duration, turn around, and points to the next node aka job
typedef struct node{
    char name[100];
    int arrival_time;
    int duration;
    int turnaround;
    struct node* next;
} p;

//Here we print the entire process
void process(p* head){
    process* cursor = head;
    while (cursor != NULL){
        printf("%s %d %d %d \n", cursor->name, cursor->arrival_time, cursor->duration, cursor->turnaround);
        cursor = cursor->next;
    }
}
p* Insert(p* head, p* node, int(*comparison)(p*, p*)){
    if(head == null || comparison(head,node)==1){
        node->next = head;
        head = node;
    }
    else{
        p* current = head;
        p* prev = NULL;
        while(current->next != NULL && comparison(node, current)==1){
            prev = current;
            current = current->next;
        }
        if(comparison(node,current)){
            node->next = current->next;
            current->next = node;
        }
        else{
            if(prev != NULL){
                prev->next = node;
                node->next = current;
            }
        }
    }

}


 