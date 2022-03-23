#include <stdio.h>
#include <stdlib.h>
#include "deadLockFunc.h"


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

//task 4 and 5 together
int* task5(int** process,int row, int column, int* terminateSize){
    struct Node* head=NULL;
    struct Node* temp=NULL;
    struct Node* current=NULL;
    struct Node* copy=NULL;
    struct Node* copy1=NULL;


    int* terminateArr= malloc(row-1);
    int terminateCount=0;

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
                    if (position-k<=2 && copy->waitingInTheList==0 ){
                        //printf("<=2 position is at %d k=%d\n",position,k);
                        terminateArr[terminateCount]=copy->processNumber;
                        terminateCount++;
                        deleteLl(&copy,copy->processNumber);
                        actualLsSize--;
                        position--;
                    } else if (position-k>2 && copy->waitingInTheList==0){
                        //printf(">2 position is at %d k=%d\n",position,k);
                        copy1=copy->next;
                        for (int h=0;h<actualLsSize-1;h++){
                            if (copy1->dealing==copy->waiting){
                                terminateArr[terminateCount]=copy1->processNumber;
                                terminateCount++;
                                deleteLl(&copy,copy1->processNumber);
                                actualLsSize--;
                                position--;
                                break;
                            }
                            copy1=copy1->next;
                        }

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

//print list
void printList(struct Node* node)
{
    while (node != NULL) {
        printf("time: %d ID %d %d %d\n",node->time, node->processNumber,node->dealing,node->waiting);
        node = node->next;
    }
}







