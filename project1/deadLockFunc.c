#include <stdio.h>
#include <stdlib.h>
#include "deadLockFunc.h"
#include "challengeTask.h"


/**
 *task 3, detect deadlock by check if the linked list have a circle
 * task 4 and 5 are just improved version of task 3
 *
 */



//task 3
int task3(int** process,int row, int* processID){
    struct Node* head=NULL;
    struct Node* temp=NULL;
    struct Node* current=NULL;

    int count=0;

    // make linked list first
    for (int i=0;i<row;i++){
        current= malloc(sizeof (struct Node));
        if (!current){
            exit(EXIT_FAILURE);
        }
        current->dealing=process[i][1];
        current->waiting=process[i][2];
        current->processNumber=process[i][0];
        current->waitingInTheList=1;
        current->next=NULL;

        if (count==0){
            head=temp=current;
        }

        else{
            temp->next=current;
            temp=current;
        }
        count++;
    }

    //connect if process are connectable
    struct Node* head_copy=head;

    while (head_copy!=NULL){

        struct Node* new_head= malloc(sizeof (struct Node));
        new_head->processNumber=head_copy->processNumber;
        new_head->dealing=head_copy->dealing;
        new_head->waiting=head_copy->waiting;
        new_head->next=NULL;
        struct Node* new_head_copy=new_head;

        int check2;
        while (find(&head,new_head->waiting,&new_head,new_head_copy,&check2)==0){
            new_head=new_head->next;
        }

        //printList1(new_head_copy);
        if (detectLoop(new_head_copy)==1){
            //printf("detected \n");
            free(current);
            current=NULL;
            free(new_head);
            return 0;
        }
        head_copy=head_copy->next;
    }

    free(current);
    current=NULL;

    return 1;
}

//task 4 and 5 together
int* task5(int** process,int row, int column, int* terminateSize){
    struct Node* head=NULL;
    struct Node* temp=NULL;
    struct Node* current=NULL;


    int* terminateArr= malloc(row-1);
    int terminateCount=0;

    int count=0;


    // make the linked list
    for (int i=0;i<row;i++){
        current= malloc(sizeof (struct Node));

        if (!current){
            return NULL;
        }

        current->dealing=process[i][1];
        current->waiting=process[i][2];
        current->processNumber=process[i][0];
        current->waitingInTheList=1;
        current->next=NULL;

        if (count==0){
            head=temp=current;
        }

        else{
            temp->next=current;
            temp=current;

        }

        count++;
    }


    struct Node* new_head=NULL;
    // iterate through the list
    int new_list_size=0;
    struct Node* head_copy=head;

    while (head_copy!=NULL){
        new_head= malloc(sizeof (struct Node));
        new_head->processNumber=head_copy->processNumber;
        new_head->waiting=head_copy->waiting;
        new_head->dealing=head_copy->dealing;
        new_head->next=NULL;
        new_list_size=1;

        struct Node* new_head_copy = new_head;

        int check2;
        while (find(&head,new_head->waiting,&new_head,new_head_copy,&check2)==0){
            new_list_size++;
            new_head=new_head->next;
        }

        //printf("move forward to %d\n",check2);
        for (int i=0;i<check2;i++){
            new_head_copy=new_head_copy->next;
        }



        if (detectLoop(new_head_copy)==1){
            //printf("detect loop\n");
            int small=smallest(&new_head_copy,new_list_size-check2);
            //printf("smallest is %d\n",small );
            terminateArr[terminateCount]=small;
            terminateCount++;
            deleteLl(&head,small);
            free(new_head);
        }

        if (new_list_size==count){
            break;
        }

        head_copy=head_copy->next;

    }

    //printList1(head);

    free(current);

    current=NULL;
    *terminateSize=terminateCount;
    selectionSort(terminateArr,terminateCount);
    return terminateArr;
}

//delete this node in the list
void deleteLl(struct Node** head_ref, unsigned int key){
    struct Node *temp = *head_ref, *prev;

    if (temp != NULL && temp->processNumber == key) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }

    while (temp != NULL && temp->processNumber != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;

    free(temp); // Free memory
}

//print list with time
int printList(struct Node* node)
{
    int simTime=1;
    while (node != NULL) {
        printf("time: %d ID %d %d %d\n",node->time, node->processNumber,node->dealing,node->waiting);
        if (node->next!=NULL&&node->time != node->next->time){
            //printf("simtime is %d\n",simTime);
            simTime++;
        }
        node = node->next;
    }
    return simTime;
}

//print list id dealing and waiting
void printList1(struct Node* node)
{
    while (node != NULL) {
        printf("ID %d %d %d\n", node->processNumber,node->dealing,node->waiting);
        node = node->next;
    }
}

//smallest process id
int smallest(struct Node** head_ref, int list_size){
    struct Node *temp = *head_ref;
    int smallest= temp->processNumber;
    for (int i=0;i<list_size;i++){
        if (temp->processNumber<smallest){
            smallest = temp->processNumber;
        }
        temp=temp->next;
    }

    return smallest;
}

//append node to the last node in the list
void append(struct Node** head_ref, unsigned int processID, unsigned int dealing, unsigned int waiting)
{
    struct Node* new_node =malloc(sizeof(struct Node));
    struct Node *last = *head_ref;

    new_node->processNumber  = processID;
    new_node->waiting=waiting;
    new_node->dealing=dealing;
    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    //iterate through to the end
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;

    return;
}

//find if there is a process dealing its current waiting and connect them if can find return 0
int find(struct Node** head_ref,unsigned waiting, struct Node** append_list, struct Node* alist_Head,int *check2){
    struct Node* head=*head_ref;
    struct Node* alist=*append_list;
    int append_count= getCount(alist_Head);
    *check2=0;

    if (*head_ref == NULL)
    {
        return 1;
    }


    while(head!=NULL){
        //printf("head is %d,waiting is %d\n",head->processNumber,waiting);
        if (head->dealing==waiting){

            int check1=check(alist_Head,head->processNumber,append_count-1);
            if (check1!=0){
                //printf("check is %d\n",check1);
                for (int i=0;i<check1;i++){
                    alist_Head=alist_Head->next;
                }
                alist->next=alist_Head;
                //printf("detect loop alisthead is %d\n",alist_Head->processNumber);

                *check2=check1;
                return 2;
            }




            append(append_list,head->processNumber,head->dealing,head->waiting);
            append_count++;
            //printf("appending %d appendCount is %d\n",head->processNumber,append_count-1);
            return 0;
        }
        head=head->next;
    }
    //printf("failed\n");

    return 1;


}

//detect loop in the list
int detectLoop(struct Node* list)
{
    struct Node *slow_p = list, *fast_p = list;

    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p) {
            return 1;
        }
    }
    return 0;
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform Selection Sort
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        swap(&arr[min_idx], &arr[i]);
    }
}

int check(struct Node* new_head, unsigned int processNumber, int length)
{
    int count=0;
    struct Node* head=new_head;
    for (int i=0;i<length;i++){
        //printf("check %d\n",head->processNumber);
        if (head->processNumber==processNumber){
            return count;
        }
        head=head->next;
        count++;
    }
    return 0;
}

int getCount(struct Node* head)
{
    int count = 0;  // Initialize count
    struct Node* current = head;  // Initialize current
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}









