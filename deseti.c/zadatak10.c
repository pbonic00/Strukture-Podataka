#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 30

struct _tree;
typedef struct _tree* TPosition;
typedef struct _tree{
    char grad[MAX_LINE];
    int br_stan;
    TPosition left;
    TPosition right;
}tree;

struct _list;
typedef struct _list* LPosition;
typedef struct _list{
    char drzava[MAX_LINE];
    TPosition gradovi;
    LPosition next;
}list;

int InsertInListFromFile(LPosition head, char *fileName);
int InsertInTreeFromFile(LPosition drzava,char *fileName);
int SortListWhileInserting(LPosition head, LPosition newPerson);
int InsertAfter(LPosition who, LPosition where);
LPosition CreateListElement(char *drzava);
int PrintList(LPosition first);
int PrintTreeInOrder(TPosition current);
TPosition SortTreeWhileInserting(TPosition current, TPosition newElement);
TPosition CreateTreeElement(char *grad, int br_stan);

int main(){

    list lstDrzava = {.drzava = "", .gradovi = NULL, .next = NULL};
    LPosition listaDrzava = &lstDrzava;

    char drzave[] = "drzave.txt";
    InsertInListFromFile(listaDrzava, drzave);
    PrintList(listaDrzava);

    return 1;

}


int InsertInListFromFile(LPosition head, char *fileName){

    FILE* dat = NULL;
    dat = fopen(fileName, "r");
    char drzava[MAX_LINE] = {0}, buffer = {0}, datotekaGradova[MAX_LINE];
    
    list tempp = {.drzava = "", .gradovi = NULL, .next = NULL};
    LPosition temp = &tempp;
 
    if(!dat){
        printf("Greska pri alociranju.\n");
        return -1;
    }

    while(!feof(dat)){

            fscanf(dat, "%s %s\n", drzava, datotekaGradova);
            temp = CreateListElement(drzava);

            InsertInTreeFromFile(temp, datotekaGradova);

            SortListWhileInserting(head, temp);
    }

    fclose(dat);
    return EXIT_SUCCESS;
}

int InsertInTreeFromFile(LPosition drzava,char *fileName){
    FILE* dat = NULL;
    dat = fopen(fileName, "r");

    char grad[MAX_LINE] = {0};
    int br_stan = 0;

    if(!dat){
        printf("Greska pri alociranju.\n");
        return -1;
    }

    while(!feof(dat)){
            fscanf(dat, "%s %d", grad, &br_stan);
            TPosition temp = CreateTreeElement(grad, br_stan);
            drzava -> gradovi = SortTreeWhileInserting(drzava -> gradovi, temp);
    }

    fclose(dat);

    return EXIT_SUCCESS;

}

int SortListWhileInserting(LPosition head, LPosition newElement){

    LPosition temp = NULL;
    temp = head -> next;

    while( temp != NULL && strcmp(temp -> drzava, newElement -> drzava) > 0 ){ //ne triba next isprid temp!!
        temp = temp -> next;
    }

    InsertAfter(newElement, head);
    return EXIT_SUCCESS;
}

int InsertAfter(LPosition who, LPosition where){

    who -> next = where -> next;
    where -> next = who;

    return EXIT_SUCCESS;
}

LPosition CreateListElement(char *drzava){
    LPosition newElement = NULL;
    newElement = (LPosition) malloc (sizeof(list));

    if(!newElement){
        perror("\nCan't allocate memory!");
        return NULL;
    }

    strcpy(newElement -> drzava, drzava);
    newElement -> gradovi = NULL;
    newElement -> next = NULL;

    return newElement;
}

int PrintList(LPosition first){
    LPosition temp = first -> next;

    while(temp){
        printf("Drzava: %s\n ", temp -> drzava);
        PrintTreeInOrder(temp -> gradovi);
        temp = temp -> next;
    }

    return EXIT_SUCCESS;
}

int PrintTreeInOrder(TPosition current){
    if(current == NULL)
        return 0;

    PrintTreeInOrder(current -> left);
    printf("\t\t%s sa %d stanovnika\n", current -> grad, current -> br_stan);
    PrintTreeInOrder(current -> right);

    return 0;
}

TPosition SortTreeWhileInserting(TPosition current, TPosition newElement){

    if(!current)
        return newElement;

    if(current -> br_stan < newElement -> br_stan){
        current -> right = SortTreeWhileInserting(current -> right, newElement);
    }

    else if(current -> br_stan > newElement -> br_stan){
        current -> left = SortTreeWhileInserting(current -> left, newElement);
    }
    else free(newElement);

    return current;
}

TPosition CreateTreeElement(char *grad, int br_stan){
    TPosition newElement = NULL;
    newElement = (TPosition) malloc (sizeof(tree));

    if(!newElement){
        perror("\nCan't allocate memory.");
        return NULL;
    }
  
    strcpy(newElement -> grad, grad);
    newElement -> br_stan = br_stan;
    newElement -> right = NULL;
    newElement -> left = NULL;

    return newElement;
}

