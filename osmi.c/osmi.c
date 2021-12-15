#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024

struct _stablo;
typedef struct _stablo* Position;
typedef struct _stablo{
    int num;
    Position right;
    Position left;
}stablo;

Position Insert(Position current, Position q);
int InOrder(Position current);
Position Create(int num);
int PreOrder(Position current);
int PostOrder(Position current);
Position Find(Position root, int a);
Position DeleteEl(Position root, int num);
Position FindMax(Position root);

int main(){

    int i = 0, br = 0, broj = 0;
    char sl = 'y', k = 'y';

    printf("\nUnesi pocetni element: ");
    scanf("%d", &broj);

    stablo Head1 = {.num = broj, .right = NULL, .left = NULL};
    Position root = &Head1;
    Position pom = &Head1;
    Position element = NULL; 

    while(sl == 'y'){

        printf("\nIzbornik:\n1-unos novog elementa  \n2-ispis elemenata (inorder) \n3-ispis elemenata (preorder) \n4-ispis elemenata (postorder) \n5-brisanje elementa \n6-pronalazenje elementa\nUnesite svoj izbor:   ");
        scanf("%d", &i);
            
            switch(i){



                case 1: {
                   
                   printf("Broj koji zelite unijeti: ");
                   scanf("%d", &br);

                   element = Create(br);
                   pom = Insert(root, element);

                    break;
                }
                

                case 2: {

                    InOrder(root);
                    break;
                }
                
                case 3: {

                    PreOrder(root);
                    break;
                }

                 case 4: {

                    PostOrder(root);
                    break;
                }            

                case 5: {
                    
                    int k = 0;
                    printf("\nUnesite element koji zelite izbrisati: ");
                    scanf("%d", &k);

                    if(DeleteEl(root, k))
                        printf("\nElement %d je izbrisan iz stabla.", k);

                    break;
                }

                case 6: {
                    
                    int n = 0;
                    Position pom = NULL;

                    printf("\nUnesite element koji zelite pronac: ");
                    scanf("%d", &n);

                    pom = Find(root, n);

                    if(!pom){
                        printf("\nTrazeni element  nije pronaden u stablu!");
                        break;
                    }

                    printf("\nElement %d je pronaden u listi.",pom -> num);
                    if(pom -> left != NULL && pom -> right != NULL) 
                        printf("\nElement ispod njega lijevo je %d, a element ispod njega desno je %d.", pom -> left -> num, pom -> right -> num);

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

Position Create(int num){
    Position newEl = NULL;
    newEl = (Position) malloc (sizeof(stablo));

    if(!newEl){
        perror("Can't allocate memory");
        return NULL;
    }

    newEl -> left = NULL;
    newEl -> right = NULL;
    newEl -> num = num;

    return newEl;
}

Position Insert(Position current, Position q){

    if(current == NULL)
        return q;
    

    if(current -> num < q -> num){
        current -> right = Insert(current -> right, q);
        //printf("\nBroj %d je dodan desno od broja %d.", q -> num, current -> num);
    }
    else if(current -> num > q -> num){
        current -> left = Insert(current -> left, q);
        //printf("\nBroj %d je dodan lijevo od broja %d.", q -> num, current -> num);
    }
    else free(q);
    
    return current;
}


int InOrder(Position current){

    if(current == NULL)
        return 0;

    InOrder(current -> left);
    printf("%d ", current -> num);
    InOrder(current -> right);

    return 0;
}


int PreOrder(Position current){

    if(current == NULL)
        return 0;

    printf("%d ", current -> num);
    InOrder(current -> left);
    InOrder(current -> right);

    return 0;
}


int PostOrder(Position current){

    if(current == NULL)
        return 0;

    InOrder(current -> left);
    InOrder(current -> right);
    printf("%d ", current -> num);

    return 0;
}

Position Find(Position root, int a){

    if(root == NULL || root -> num == a) 
        return root;

    if(root -> num > a)
        return Find(root -> left, a);

    else if(root -> num < a)
        return Find(root -> right, a);

}


Position FindMax(Position root){

    if(root -> right != NULL) root = FindMax( root -> right);
    return root;

}


Position DeleteEl(Position root, int n){

    Position temp = NULL, pom = NULL, k = NULL;
    temp = Find(root, n);

    if(!temp){
        printf("\nElement kojeg zelite izbrisat (%d) ne postoji!", n);
        return 0;
    }

    if(root -> num < n)
        root -> right = DeleteEl(root -> right, n);

    else if(root -> num > n)
        root -> left = DeleteEl(root -> left, n);

    else if(root -> num == n){

        if( root -> left != NULL && root -> right == NULL ){

            k = FindMax(root -> left);
            root -> num = k -> num;
            root -> left = DeleteEl( root -> left, root -> num);

        }

        else if( root -> left != NULL && root -> right == NULL ){

            pom = root;
            root = root -> left;
            free(pom);
        }

        else if( root -> left == NULL && root -> right != NULL ){

            pom = root;
            root = root -> right;
            free(pom);
        }
    }
    
    return root;
    
}