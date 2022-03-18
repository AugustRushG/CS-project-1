for (int k=0;k<actualLsSize;k++){
if (current->dealing==copy->waiting){
printf("1temp dealing %d, waiting for %d\n",temp->dealing,temp->waiting);
//printf("1current dealing %d, waiting for %d\n",current->dealing,current->waiting);
temp->next=current;
}
if (current->waiting==copy->dealing){
//printf("2temp dealing %d, waiting for %d\n",temp->dealing,temp->waiting);
//printf("2current dealing %d, waiting for %d\n",current->dealing,current->waiting);
printf("head now is ID %d,dealing %d,waiting %d\n",head->processNumber,head->dealing,head->waiting);
current->next=copy;

if (k<2){
printf("k=%d actualsize=%d\n",k,actualLsSize);
printf("processNumber = %d\n",copy->processNumber);
terminateArr[terminateCount]=copy->processNumber;
terminateCount++;
deleteLl(&copy,copy->processNumber);
actualLsSize--;
} else{

printf("-- k=%d actualsize=%d\n",k,actualLsSize);
printf("processNumber = %d\n",copy->next->processNumber);
terminateArr[terminateCount]=copy->next->processNumber;
terminateCount++;
deleteLl(&copy,copy->next->processNumber);
actualLsSize--;
}


}


copy=copy->next;

}