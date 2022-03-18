#include "task12Func.h"
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define INITIAL 5

//task one get processors and file numbers
int task1(FILE *fptr, int* fileCount){
    int currentNumber=0;
    char current;
    int filecount=0;
    int processCount=0;
    int *fileArr;

    fileArr= malloc(INITIAL*sizeof (int));
    int count=0;

    //by using fscanf to count how many lines and file
    while(fscanf(fptr,"%d%c",&currentNumber,&current)>0){

        if(count>INITIAL){
            fileArr= realloc(fileArr,2*count*sizeof (int));
        }

        for (int i=0;i<3;i++){
            //printf("%d\n",fileArr[i]);
        }

        if (contains(fileArr,currentNumber,count)==0&&filecount!=0){
            //printf("contains %d\n", contains(fileArr,2));
            //printf("%d\n",currentNumber);
            fileArr[count]=currentNumber;
            count++;
        }
        //printf("count is %d\n",count);

        filecount++;

        if (current=='\n'){
            processCount++;
            filecount=0;
        }
    }
    //printf("processCount is %d filecount is %d \n",processCount,filecount);
    *fileCount=count+1;

    //clean up
    free(fileArr);
    fileArr=NULL;
    processCount--;
    return processCount;
}

//workout the execution time
int executionTime(int **process,int fileNumber,int processNumber){
    int time=-1;
    int arr[processNumber];
    for (int i=1;i<fileNumber;i++){
        for (int j=0;j<processNumber;j++){
            arr[j]=process[j][i];

            //put those number into an array
            //printf("array %d\n",arr[j]);
        }

        //if no duplicate task just add one
        if (duplicate(arr,processNumber)==0){
            time++;
        }

        else if (duplicate(arr,processNumber)==1){
            time++;
            time+= removeDuplicate(arr,processNumber);
        }
    }
    return time;
}

//check if an array have duplicate
int duplicate(int* arr,int length){
    for (int i=0;i<length;i++){
        for (int j=i+1;j<length;j++){
            if (arr[i]==arr[j]&&arr[i]>=0){
                return 1;
            }
        }
    }
    return 0;
}

//the idea is to keep checking the duplicate and remove one at a time to calculate the time
int removeDuplicate(int* arr, int length){
    int time=0;
    int dup[length];

    while (duplicate(arr,length)==1){
        //reset each time
        int dupCount=0;
        for (int i=0;i<length;i++){
            dup[i]=-1;
        }


        for (int i=0;i<length;i++){
            for (int j=i+1;j<length;j++){
                if (arr[i]==arr[j] && contains(dup,arr[i],length)==0){
                    dup[dupCount]=arr[i];
                    dupCount++;
                    arr[i]=-1;
                }
            }
        }


        /* testing for array
        for (int i=0;i<length;i++){
            //printf("%d\n",arr[i]);
        }*/

        time++;
        //printf("time now is %d duplicate or not %d \n",time, duplicate(arr,length));
    }



    time++;
    return time;
}

//check if this num is in the array or not
int contains(int* arr, int num,int length){


    for (int i=0;i<length;i++){
        if (num==arr[i]){
            return 1;
        }
    }
    return 0;

}


