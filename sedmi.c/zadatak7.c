#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 30

struct _tree;
typedef struct _tree* TPosition;
typedef struct _tree{
    char name[MAX_LINE];
    TPosition sibiling;
    TPosition child;
}tree;

struct _stack;
typedef struct _stack* SPosition;
typedef struct _stack{
    TPosition directory;
    SPosition next;
}stack;


TPosition Create(char *name);
TPosition Insert(TPosition current, TPosition newEl);
int Print(TPosition current);
TPosition Pop(SPosition head, TPosition current);
int Push(SPosition root, SPosition newSElement);
SPosition CreateStackEl(TPosition current);
TPosition Find(TPosition current, char *name);


int main(){

    tree treeRoot = {.name = "root", .sibiling = NULL, .child = NULL};
    TPosition troot = &treeRoot;
    TPosition current = troot;

    stack stackRoot = {.directory = NULL, .next = NULL};
    SPosition sroot = &stackRoot;

    char sl = 'y', k = 'y';
    char name[15];
    int i = 0;

    TPosition newDirectory = NULL;

    while(sl == 'y'){

        printf("\nIzbornik:\n1-md \n2-cd dir \n3-cd \n4-dir \nUnesite svoj izbor:   ");
        scanf("%d", &i);
            
            switch(i){

                case 1: {
                   
                   printf("\nUnesi ime novog direktorija: ");
                   scanf("%s", name);

                    newDirectory = Create (name);
                    current -> child =  Insert (current -> child, newDirectory);
                  
                    break;
                }
                

                case 2: {

                    printf("\nUnesi ime direktorija u koji zelite uc: ");
                    scanf("%s", name);

                    TPosition tempp = Find(current, name);

                    if(tempp == NULL)
                        printf("Element %s ne postoji u direktoriju.", name);
                    else{
                        SPosition newSEl = CreateStackEl(current);
                        Push(sroot, newSEl);
                    }

                    current = tempp;

                    break;
                }
                
                case 3: {

                    current = Pop(sroot, current);
                    
                    break;
                }

                 case 4: {

                    printf("Subdirektoriji u direktoriju %s: \n", current -> name);
                    Print(current);
                    
                    break;
                }
                
                 default: 
                    printf("\nPogresan unos!");
            }
            
            
            printf("\nZelite li se vratiti u izbornik?\ny/n: ");
            scanf("\n%c", &k); 
            
            while (k != 'y' && k != 'n'){
                printf ("\nPogresan unos!");

                printf("\nZelite li se vratiti u izbornik?\ny/n: ");
                scanf("%c", &k);
            }
           
            sl = k;
    } 


   

}


TPosition Find(TPosition current, char *name){

    TPosition child = current -> child;

    if(current == NULL)
        printf("\nOvaj direktorij je prazan.");

    while(child != NULL && strcmp (child -> name, name) != 0)
        child = child -> sibiling;

    return child;

}



TPosition Create(char *name){

    //printf("Usa san u fju Create.");

    TPosition newEl = NULL;

    newEl = (TPosition) malloc (sizeof(tree));
    if(!newEl){
        perror("\n Can't allocate memory. ");
        return NULL;
    }

    strcpy(newEl -> name, name);
    newEl -> sibiling = NULL;
    newEl -> child = NULL;

    return newEl;
}


TPosition Insert(TPosition current, TPosition newElement){

   if (!current)
		return newElement;

	if (strcmp(current->name, newElement->name) < 0)
		current->sibiling = Insert(current->sibiling, newElement);

	else if (strcmp(current->name, newElement->name) > 0)
	{
		newElement->sibiling = current;
		return newElement;
	}
	return current;
}


int Print(TPosition current){

    TPosition pom = current -> child;

    while(pom != NULL){

        printf("\n%s ", pom -> name);
        pom = pom -> sibiling;

    }

    return EXIT_SUCCESS;
}




SPosition CreateStackEl(TPosition current){
    SPosition newEl = NULL;
    newEl = (SPosition) malloc (sizeof(stack));

    if(!newEl){
        perror("Couldn't allocate memory.");
        return NULL;
    }

    newEl -> directory = current;
    newEl -> next = NULL;

    return newEl;
}


int Push(SPosition root, SPosition newSElement){

    newSElement -> next = root -> next;
    root -> next = newSElement;

    return EXIT_SUCCESS;
}

TPosition Pop(SPosition head, TPosition current){

    SPosition first = NULL;
    first = head -> next;

    TPosition pom = NULL;

    if(!first){
        printf("This directory doesn't have a parent.");
        return current;
    }

    pom = first -> directory;

    head -> next = first -> next;
    free(first);

    return pom;

}