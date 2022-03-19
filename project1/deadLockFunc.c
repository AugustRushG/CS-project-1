#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "deadLockFunc.h"


/**
 *task 3, detect deadlock by check if the linked list have a circle
 * task 4 and 5 are just improved version of task 3
 *
 */




int task3(int** process,int row, int* processID){
    struct Node* head=NULL;
    struct Node* temp=NULL;
    struct Node* current=NULL;
    struct Node* copy=NULL;

    int count=0;
    int actualLsSize=0;

    for (int i=0;i<row;i++){
        current= malloc(sizeof (struct Node));

        if (!current){
            exit(EXIT_FAILURE);
        }

        current->dealing=process[i][1];
        current->waiting=process[i][2];
        current->processNumber=process[i][0];
        current->waitingInTheList=1;

        if (count==0){
            head=temp=current;
            copy=head;
        }

        else{
            copy=head;

            temp->next=current;
            temp=current;

            for (int k=0;k<actualLsSize;k++){

                if (current->dealing==copy->waiting){
                    temp->next=current;
                    copy->waitingInTheList=0;
                }
                if (current->waiting==copy->dealing && copy->waitingInTheList==0){
                    current->next=copy;
                    return 0;
                }
                copy=copy->next;
            }

        }
        count++;
        actualLsSize++;
    }

    free(current);
    current=NULL;

    return 1;
}


int* task5(int** process,int row, int column, int* terminateSize){
    struct Node* head=NULL;
    struct Node* temp=NULL;
    struct Node* current=NULL;
    struct Node* copy=NULL;

    int* terminateArr= malloc(row-1);
    int terminateCount=0;
    //int terminate=0;

    int count=0;
    int actualLsSize=0;

    int position=0;


    for (int i=0;i<row;i++){
        current= malloc(sizeof (struct Node));

        if (!current){
            return NULL;
        }

        current->dealing=process[i][1];
        current->waiting=process[i][2];
        current->processNumber=process[i][0];
        current->waitingInTheList=1;

        if (count==0){
            head=temp=current;
            copy=head;
        }

        else{
            copy=head;

            temp->next=current;
            temp=current;

            for (int k=0;k<actualLsSize;k++){

                if (current->dealing==copy->waiting){
                    temp->next=current;
                    //set this node's waitingList to 0 indicate there is no file that this node need is dealing
                    copy->waitingInTheList=0;
                }
                if (current->waiting==copy->dealing ){
                    current->next=copy;

                    //if search is complete before 2 steps, just this node, > 2 the next node to terminate
                    if (position-k<=2 && copy->waitingInTheList==0){
                        //printf("<=2 position is at %d k=%d\n",position,k);
                        terminateArr[terminateCount]=copy->processNumber;
                        terminateCount++;
                        deleteLl(&copy,copy->processNumber);
                        actualLsSize--;
                        position--;
                    } else if (position-k>2 && copy->waitingInTheList==0){
                        //printf(">2 position is at %d k=%d\n",position,k);
                        terminateArr[terminateCount]=copy->next->processNumber;
                        terminateCount++;
                        deleteLl(&copy,copy->next->processNumber);
                        actualLsSize--;
                        position--;
                    }
                }
                copy=copy->next;
            }
        }
        count++;
        actualLsSize++;
        position++;
    }

    free(current);
    current=NULL;
    *terminateSize=terminateCount;
    return terminateArr;
}

//delete this node in the list
void deleteLl(struct Node** head_ref, int key){
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

//push into the list
void push(struct Node** head_ref, int processID, int dealing, int waiting)
{
    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->processNumber = processID;
    new_node->dealing=dealing;
    new_node->waiting=waiting;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

//print list
void printList(struct Node* node)
{
    while (node != NULL) {
        printf("ID %d %d %d\n", node->processNumber,node->dealing,node->waiting);
        node = node->next;
    }
}

//detect loop
int detectLoop(struct Node* list, int* terminate){
    struct Node *slow_p = list, *fast_p = list;

    while (slow_p && fast_p && fast_p->next) {
        slow_p = slow_p->next;
        fast_p = fast_p->next->next;
        if (slow_p == fast_p) {
            *terminate=fast_p->processNumber;
            return 1;
        }
    }
    return 0;
}






