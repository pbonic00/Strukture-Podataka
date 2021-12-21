#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LINE 30

struct _tree;
typedef struct _tree* TPosition;
typedef struct _tree{
    int number;
    TPosition left;
    TPosition right;
}tree;

struct _stack;
typedef struct _stack* SPosition;
typedef struct _stack{
    int number;
    SPosition next;
}stack;


int InOrder(TPosition current);
TPosition Create(int num);
SPosition CreateStackEl(TPosition current);
int InsertAfter(SPosition position, SPosition newElement);
SPosition FindLast(SPosition head);
TPosition Insert(TPosition current, TPosition el);
int Replace (TPosition current);
int InsertInFile(SPosition first, SPosition second, char *name);
int PrintList( SPosition first);
int InOrderStack (TPosition current, SPosition position);


int main(){


    stack stackRoot = {.number = 0, .next = NULL};
    SPosition sroot1 = &stackRoot;
    stack stackRoot1 = {.number = 0, .next = NULL};
    SPosition sroot2 = &stackRoot1;

    TPosition root1 = NULL;
    TPosition root2 = NULL;
    TPosition el;

    int niz[10] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
    int i = 0;

    time_t t;

    char nazivDat[MAX_LINE] = "zdk9.txt";

    srand((unsigned) time(&t));

    for(i = 0; i < 10; i++){

        el = Create(niz[i]);
        root1 = Insert(root1, el);
    }

    printf("\nInorder ispis stabla: ");
    InOrder(root1);

    printf("\nInorder ispis liste: ");
    InOrderStack(root1, sroot1);
    PrintList(sroot1 -> next);

    InsertInFile(sroot1, sroot2, nazivDat);

    for(i = 0; i < 10; i++){
        niz[i] = rand() % (89 + 1 - 11) + 11;
        el = Create(niz[i]);
        root2 = Insert(root2, el);
    }

    printf("\nInorder ispis: ");
    InOrder(root2);

    return 0;

}

int InOrderStack (TPosition current, SPosition position){
    SPosition new = NULL;

    if(current == NULL) return 0;

    InOrderStack (current -> left, position);

    new = CreateStackEl(current);
    InsertAfter(position, new);

    InOrderStack(current -> right, position);
    return 0;
}

int PrintList( SPosition first){

    SPosition pom = NULL;
    pom = first;

    while(pom){
        printf("%d", pom -> number);
        pom = pom -> next;
    }

    return EXIT_SUCCESS;
}


int InsertInFile(SPosition first, SPosition second, char *name){

    SPosition pom1 = NULL, pom2 = NULL;

    FILE *dat = NULL;
    dat = fopen(name, "w");

    if(!dat){
        perror("Couldn't open file!");
        return -1;
    }

    while(pom1 != 0){
        if(pom1 != first)
            fprintf(dat, "%d ", pom1 -> number);
        pom1 = pom1 -> next;
    }

    fprintf(dat, "\n");

    while(pom2 != 0){
        if(pom2 != second)
            fprintf(dat, "%d ", pom2 -> number);
        pom2 = pom2 -> next;
    }

    fclose(dat);
    return 0;
}


int Replace (TPosition current) {

    int pom = 0;

    if(current -> left == NULL && current -> right == NULL){

        pom = current -> number;
        current -> number = 0;
        return pom;
    }

    else if(current -> left == NULL && current -> right != NULL){

        pom = current -> number;
        current -> number = Replace (current -> right);
        pom = pom + current -> number;
        return pom;
    }

    else if(current -> left != NULL && current -> right == NULL){

        pom = current -> number;
        current -> number = Replace (current -> left);
        pom = pom + current -> number;
        return pom;
    }

    else {

        pom = current -> number;
        current -> number = Replace(current -> left) + Replace(current -> right);
        pom = pom + current -> number;
        return pom;
    }

    return current -> number;

}


TPosition Insert(TPosition current, TPosition el){

    if(current == NULL)
        return el;

    else if(current -> number <= el -> number)
        current -> left = Insert(current -> left, el);
    
    else if(current -> number > el -> number)
        current -> right = Insert(current -> right, el);

    return current;    

}

int InOrder(TPosition current){

    if(current == NULL)
        return 0;

    InOrder(current -> left);
    printf("%d ", current -> number);
    InOrder(current -> right);

    return 0;
}

TPosition Create(int num){
    TPosition newEl = NULL;
    newEl = (TPosition) malloc (sizeof(tree));

    if(!newEl){
        perror("Can't allocate memory");
        return NULL;
    }

    newEl -> left = NULL;
    newEl -> right = NULL;
    newEl -> number = num;

    return newEl;
}

SPosition CreateStackEl(TPosition current){
    SPosition newEl = NULL;
    newEl = (SPosition) malloc (sizeof(stack));

    if(!newEl){
        perror("Couldn't allocate memory.");
        return NULL;
    }

    newEl -> number = current -> number;
    newEl -> next = NULL;

    return newEl;
}



int InsertAfter(SPosition position, SPosition newElement) {
	newElement -> next = position -> next;
    position -> next = newElement;

    return EXIT_SUCCESS;
}


SPosition FindLast(SPosition head) {
	SPosition temp = head;

	while (temp->next) {
		temp = temp->next;
	}

	return temp;
}



