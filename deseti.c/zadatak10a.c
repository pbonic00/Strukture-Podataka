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
LPosition FindState (LPosition p, char *ime);
int FindTown (TPosition p, int broj);

int main(){

    list lstDrzava = {.drzava = "", .gradovi = NULL, .next = NULL};
    LPosition listaDrzava = &lstDrzava;
    char drzava[MAX_LINE] = {0};
    int br_stan = 0;
    LPosition p = NULL;

    char drzave[] = "drzave.txt";
    InsertInListFromFile(listaDrzava, drzave);
    PrintList(listaDrzava);

    printf("Koju drzavu zelite pretraziti: ");
    scanf("%s", drzava);

    p = FindState(listaDrzava -> next, drzava);

    if(p == NULL){
        printf("Drzava ne postoji");
        return 0;
    }

    printf("Upisite minimalan broj stanovnika: ");
    scanf("%d", &br_stan);

    printf("\nGradovi drzave %s sa vise od %d stanovnika: ", p -> drzava, br_stan);
    FindTown(p -> gradovi, br_stan);

    return 1;

}

LPosition FindState (LPosition p, char *ime){

    while( p != NULL){
        if(strcmp(p -> drzava, ime) == 0)
            return p;
        p = p  -> next;
    }
    return p;
}

int FindTown (TPosition p, int broj){

    if(p == NULL)
        return 0;

    FindTown(p -> left, broj);

    if((p -> br_stan) >= broj){
       // printf("\nBroj stanovnika %d i broj s kojin usporefdujemo je %d", p -> br_stan, broj);
        printf("\n%s %d", p -> grad, p -> br_stan);
    }

    FindTown(p -> right, broj);

    return 0;
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

    while( head -> next != NULL && strcmp(head -> next -> drzava, newElement -> drzava) < 0 ){ //ne triba next isprid temp!!
        head = head -> next;
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

    if(current -> br_stan > newElement -> br_stan){
        current -> right = SortTreeWhileInserting(current -> right, newElement);
    }

    else if(current -> br_stan < newElement -> br_stan){
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
