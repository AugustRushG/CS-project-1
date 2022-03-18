struct Node{
    int processNumber;
    int dealing;
    int waiting;
    int waitingInTheList;
    struct Node* next;
};


int task3(int** process,int row, int* position);
int* task5(int** process,int row, int column,int* terminateSize);
void deleteLl(struct Node** head_ref, int key);
void push(struct Node** head_ref, int processID, int dealing, int waiting);
void printList(struct Node* node);
int detectLoop(struct Node* list, int* terminate);
