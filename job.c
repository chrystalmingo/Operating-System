#include <job.h>
int CmpDuration(p* p1, p* p2){
    return p2->duration < p1->duration ? 0:1;
}
int CmpArrival(p* p1, p* p2){
    return p2->arrival_time < p1->arrival_time ? 0:1;
}

float Fifo(p* head){
    float avg = 0;
    int turnaround = 0;
    int count = 0;
    p* current = head;
    while(current != NULL){
        turnaround += current->duration - current->arrival_time;
        current->turnaround = turnaround;
        avg += turnaround;
    }
    return avg/count;
}
float SSP(p* head){
    float avg = 0;
    int turnaround = 0;
    int count = 0;
    p* current = head;
    while(current != NULL){
        count++
        turnaround += current->duration - current->arrival_time;
        current->turnaround = turnaround;
        avg += turnaround;
    }
    return avg/count

}

int main(){
    head = Insert(head,node,&CmpDuration)

}
