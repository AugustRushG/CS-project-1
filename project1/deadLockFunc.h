struct Node{
    unsigned int processNumber;
    unsigned int dealing;
    unsigned int waiting;
    int waitingInTheList;
    int time;
    struct Node* next;
};

int task3(int** process,int row, int* position);
int* task5(int** process,int row, int column,int* terminateSize);
void deleteLl(struct Node** head_ref, unsigned int key);
int printList(struct Node* node);
int smallest(struct Node** head_ref, int list_size);
void append(struct Node** head_ref, unsigned int processID, unsigned int dealing, unsigned int waiting);
void printList1(struct Node* node);
int find(struct Node** head_ref,unsigned waiting,struct Node** append_list,struct Node* alist_Head,int *check2);
int detectLoop(struct Node* list);
void swap(int* xp, int* yp);
void selectionSort(int arr[], int n);
int check(struct Node* new_head, unsigned int processNumber, int length);
int getCount(struct Node* head);
