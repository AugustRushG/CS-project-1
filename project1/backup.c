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
                        printf("<=2 position is at %d k=%d\n",position,k);
                        terminateArr[terminateCount]=copy->processNumber;
                        terminateCount++;
                        deleteLl(&copy,copy->processNumber);
                        actualLsSize--;
                        position--;
                    } else if (position-k>2 && copy->waitingInTheList==0){
                        printf(">2 position is at %d k=%d\n",position,k);
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
        current->time=0;

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
    int time=0;
    copy=head;
    struct Node* copy1;
    int skipped=0;

    for (int j=0;j<row;j++){
        // printf("run for how %d times, skipped =%d\n",j,skipped);
        //printf("copy=%d\n",copy->processNumber);
        copy1=copy->next;
        copy->time=time;
        //printf("copy1=%d\n",copy1->processNumber);
        for (int i=j+1;i<row;i++){
            if (copy1->dealing!=copy->waiting&&copy1->waiting!=copy->dealing){
                //printf("copy=%d when skip++\n",copy->processNumber);
                //printf("copy1=%d when skip++\n",copy1->processNumber);
                copy1->time=time;
                skipped++;
            }
            if (copy1->dealing==copy->waiting || copy1->waiting==copy->dealing){
                break;
            }
            copy1=copy1->next;
        }
        time++;
        for (int h=0;h<skipped;h++){
            if (copy->next==NULL){
                break;
            }
            copy=copy->next;
        }

        if (copy->next==NULL){
            break;
        }
        copy=copy->next;
        j+=skipped;

    }

    int simTime;

    if (row==0){
        simTime=0;
    }

    else{
        copy=head;
        for (int i=0;i<row-1;i++){
            copy=copy->next;
        }
        simTime=copy->time+1;
    }

    while (head!=NULL){
        printf("%d %d %d,%d\n",head->time,head->processNumber,head->dealing,head->waiting);
        head=head->next;
    }

    printf("Simulation time %d\n",simTime);
    freeList(head);
}