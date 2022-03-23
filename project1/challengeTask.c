#include "stdlib.h"
#include "deadLockFunc.h"
#include "challengeTask.h"

/**
* for challenge task my idea is to check the first process what files it need, record them, compare to the next one
 * in the list, if the next one contains part of the files of the first one, move it to the end of the list.
 * iterate through all to rearrange all processers, then reiterate through from the top, check the next one contains
 * any, if not, set the time to be zero, if yes, wait for the next one.
*/


//challenge task
void challenge(int** process,int row){
    //first step, make a linked list
    struct Node* head=NULL;
    struct Node* temp=NULL;
    struct Node* current=NULL;
    int count=0;

    for (int i=0;i<row;i++){
        current= malloc(sizeof (struct Node));

        if (!current){
            exit(EXIT_FAILURE);
        }

        current->dealing=process[i][1];
        current->waiting=process[i][2];
        current->processNumber=process[i][0];
        current->time=-1;

        if (count==0){
            head=temp=current;
        }

        else {
            temp->next = current;
            temp = current;
        }
        count++;
    }
    struct Node* copy=head;

   //second step rearrange
    rearrange(&copy,count);

   //calculate time
    calculateTime(&head);
   freeList(head);
}

//append node to the last node in the list
void append(struct Node** head_ref, int processID, int dealing, int waiting)
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

//free all memories in the list
void freeList(struct Node* head)
{
    struct Node* tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }

}

//rearrange all nodes in the list
void rearrange(struct Node** head_ref, int count){
    struct Node* copy=*head_ref;
    for (int i=0;i<count;i++){
        if (copy->waiting==copy->next->dealing || copy->dealing==copy->next->waiting){
            int processNumber=copy->next->processNumber;
            int dealing=copy->next->dealing;
            int waiting=copy->next->waiting;

            //delete this node
            deleteLl(&copy,copy->next->processNumber);

            //append this node to the last
            append(&copy,processNumber,dealing,waiting);

            i++;
        }
        copy=copy->next;
    }
}

//to iterate through in order to calculate time.
void calculateTime(struct Node** head_ref){
    struct Node* copy=*head_ref;
    int count=0;
    int time=0;
    int skip=0;
    int skipFlag=1;

    //iterate through the linked list
    while (copy!=NULL){
        if (count==0){
            copy->time=0;
        }
        else{
            struct Node* copy1=*head_ref;
            skipFlag=1;
            for (int i=0;i<count-skip;i++){
                int j=0;
                while (j<skip && skipFlag==1){
                    copy1=copy1->next;
                    j++;
                }
                if (j>0){
                    skipFlag=0;
                }


                if (copy1->dealing==copy->waiting || copy1->waiting==copy1->dealing){
                    time++;
                    copy->time=time;
                    skip=count;
                    break;
                }
                else{
                    copy->time=time;
                }

                if (copy1->next!=NULL){
                    copy1=copy1->next;
                }



            }
        }
        count++;
        copy=copy->next;

    }
    printList(*head_ref);

}





