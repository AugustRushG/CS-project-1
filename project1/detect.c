#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "deadLockFunc.h"
#include "task12Func.h"
#include "challengeTask.h"

#define INITIAL 5

//main function
int main(int argc, char** argv) {

    int eFlag=0;
    int cFlag=0;
    int fFlag=0;
    char *fileName = NULL;
    int c;

    //getopt to identify input
    while ((c = getopt (argc, argv, "ecf:")) != -1)
        switch (c)
        {
            case 'e':
                eFlag=1;
                break;
            case 'c':
                cFlag=1;
                break;
            case 'f':
                fFlag=1;
                fileName = optarg;
                break;
            default:
                abort ();
        }

    FILE*fptr=fopen(fileName,"r");

    //assert if no file is reading
    assert(fileName!=NULL);

    //creating a 2d array
    int** process=NULL;
    int fileNumber;

    //getting numbers of files and processes
    int processCount= task1(fptr,&fileNumber);
    processCount+=1;
    fileNumber-=1;

    //reset file
    fseek(fptr,0,SEEK_SET);

    //allocate memory into 2d array
    process=malloc(processCount*sizeof(int*));
    for (int i=0;i<processCount;i++){
        process[i]= malloc((fileNumber+1)*sizeof (int));
    }

    int currentNumber=0;
    char current;
    int row=0;
    int column=0;
    int realColumn=0;

    //scan txt into 2d array
    while (fscanf(fptr,"%d%c",&currentNumber,&current)>0){
        process[row][column]=currentNumber;
        column++;

        if (current=='\n'){
            row++;
            realColumn=column;
            column=0;
        }
    }

    //execute if -e -f -c  is entered
    if(fFlag==1){

        printf("Processes %d\n",processCount);
        printf("Files %d\n",fileNumber);

        int positionID=0;
        int detectDeadlock= task3(process,row,&positionID);

        int terminateSize=0;

        if (detectDeadlock==0&&eFlag==0&&cFlag==0){
            printf("Deadlock detected\n");

            int* terminateArr= task5(process,row,realColumn,&terminateSize);
            printf("Terminate ");
            for (int i=0;i<terminateSize;i++){
                printf("%d ",terminateArr[i]);
            }
            printf("\n");

        }

        else if (detectDeadlock==1 && eFlag==0){
            printf("No deadlocks\n");
        }

    }

    if(eFlag==1){
        int time=executionTime(process,realColumn,row);
        if (row==0){
            time=0;
        }
        printf("Execution time %d\n",time);
    }

    if(cFlag==1){
        challenge(process,row);
    };

    //cleanup
    for(int i=0;i<processCount;i++){
        free(process[i]);
        process[i]=NULL;
    }

    free(process);
    process=NULL;

    fclose(fptr);
    return 0;
}



