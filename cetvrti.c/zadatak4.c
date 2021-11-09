#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024

struct _Polinom;
typedef struct _Polinom* listPol;
typedef struct _Polinom{
    int koef;
    int pot;
    listPol next;
}Polinom;

int ZbrojiPolinome(listPol prvi, listPol drugi, listPol zbroj);
int UmnozakPolinoma(listPol prvi, listPol drugi, listPol umnozak);
int CitajIzDatoteke(char* nazivDat, listPol head1, listPol head2);
listPol Stvori (int koef, int pot);
int Printaj(listPol head);
int UnesiPolinom (char* buffer, listPol head);
int SortirajPriUnosu(listPol element, listPol head);
int UnesiIza(listPol position, listPol who);
int Izbrisi(listPol who, listPol head);
listPol NadiPrije(listPol head, listPol who);

int main(){

    Polinom Head1 = {.koef = 0, .pot = 0, .next = NULL};
    listPol p1 = &Head1;

    Polinom Head2 = {.koef = 0, .pot = 0, .next = NULL};
    listPol p2 = &Head2;

    Polinom Head3 = {.koef = 0, .pot = 0, .next = NULL};
    listPol p3 = &Head3;

    Polinom Head4 = {.koef = 0, .pot = 0, .next = NULL};
    listPol p4 = &Head4;


    char nazivDat[] = "polinomi";
    CitajIzDatoteke(nazivDat, p1, p2);
    printf("Prvi polinom: ");
    Printaj(p1 -> next);
    printf("\n\nDrugi polinom: ");
    Printaj(p2 -> next);

    ZbrojiPolinome (p1->next, p2->next, p3);
    printf("\n\nZbroj polinoma: ");
    Printaj(p3 -> next);

    UmnozakPolinoma (p1 -> next, p2 -> next, p4);
    printf("\n\nUmnozak polinoma: ");
    Printaj(p4 -> next);

    return 0;
}



int CitajIzDatoteke(char* nazivDat, listPol head1, listPol head2){
    
    char buffer1[MAX_LINE] = {0};
    char buffer2[MAX_LINE] = {0};

    FILE *dat = NULL;
    dat = fopen(nazivDat, "r");

    if(!dat){

        printf("Neuspjelo otvaranje datoteke");
        return -1;
    }

    fgets(buffer1, MAX_LINE, dat);
    UnesiPolinom(buffer1, head1);

    fgets(buffer2, MAX_LINE, dat);
    UnesiPolinom(buffer2, head2);

    return EXIT_SUCCESS;
}


int UnesiPolinom (char* buffer, listPol head){

    int pomak = 0, koef = 0, exp = 0, n = 0;
    listPol temp = NULL;

    while (buffer[pomak] != '\0'){
        sscanf(buffer + pomak, "%d %d %n", &koef, &exp, &n);
        pomak += n;

        temp = Stvori (koef, exp);
        if(temp == NULL){

            printf("Can't allocate memory.\n");
            return -1;
        } 

        SortirajPriUnosu(temp, head);
    }

    return EXIT_SUCCESS;
}


int SortirajPriUnosu(listPol element, listPol head){

    listPol temp = head -> next, prethodni = NULL;

    while( (temp != NULL) && ((element -> pot) < (temp -> pot)) )
        temp = temp -> next;
    
    if(temp != NULL && (element -> pot == temp -> pot) ){
        
        if( temp -> koef + element -> koef){

            temp -> koef = temp -> koef + element -> koef;
        }

        else{

            Izbrisi(temp, head);
            free(element);
        }
    }

    else{

        prethodni = NadiPrije(head, temp);
        UnesiIza(prethodni, element);
    }
    
    return EXIT_SUCCESS;
}


int Izbrisi(listPol who, listPol head){

    listPol temp = NULL;

    temp = NadiPrije(head, who);
    temp -> next = who -> next;
    free (who);

    return EXIT_SUCCESS;

}


listPol NadiPrije(listPol head, listPol who){

    listPol temp = head;
    while(temp -> next != who)
        temp = temp -> next;
        
    return temp;

}


int UnesiIza(listPol position, listPol who){

    who -> next = position -> next;
    position -> next = who;

    return EXIT_SUCCESS;
}


int Printaj(listPol head){

    listPol temp = head;

    printf("\n");
    while(temp != NULL){

        printf("%dx^%d ", temp -> koef, temp -> pot);
        temp = temp -> next;
    }

    return EXIT_SUCCESS;
}


listPol Stvori (int koef, int pot){
    
    listPol polinom = NULL;
    polinom = (listPol) malloc (sizeof(listPol));

    if(!polinom){

        printf("Can't allocate memory");
        return NULL;
    }

    polinom -> pot = pot;
    polinom -> koef = koef;
    polinom -> next = NULL;

    return polinom;
}


int Povezi(listPol pol1, listPol pol2){
    
    pol2 -> next = pol1 -> next;
    pol1 -> next = pol2; 

    return EXIT_SUCCESS;
}


listPol NadiZadnjeg (listPol head){
   
    listPol temp = head;

    while (temp -> next){

        temp = temp -> next;
    }

    return temp;
}


int ZbrojiPolinome (listPol prvi, listPol drugi, listPol zbroj){

    listPol temp = NULL, ostali = NULL;

    while (prvi  && drugi ){
        if(prvi -> pot == drugi -> pot){

            temp = Stvori (prvi -> koef + drugi -> koef, prvi -> pot);
            SortirajPriUnosu (temp, zbroj);
            prvi = prvi -> next;
            drugi = drugi -> next;
        }

        else if(prvi -> pot > drugi -> pot){

            temp = Stvori (prvi -> koef, prvi -> pot);
            SortirajPriUnosu (temp, zbroj);
            prvi = prvi -> next;
        }

        else{

            temp = Stvori (drugi -> koef, drugi -> pot);
            SortirajPriUnosu (temp, zbroj);
            drugi = drugi -> next;
        }
    }

    if (prvi && drugi == NULL){

        while(prvi -> next){

            ostali = Stvori (prvi-> koef, prvi -> pot);
            SortirajPriUnosu (ostali, zbroj);
            prvi = prvi -> next;
        }
    }

    else if (drugi && prvi == NULL){

        while(drugi -> next){

            ostali = Stvori (drugi -> koef, drugi -> pot);
            SortirajPriUnosu (ostali, zbroj);
            drugi = drugi -> next;
        }
    }

    return EXIT_SUCCESS;
}


int UmnozakPolinoma (listPol prvi, listPol drugi, listPol umnozak){

    listPol temp = NULL;
    listPol pom = prvi;

    for (drugi; drugi != NULL; drugi = drugi -> next){

        pom = prvi;

        for (pom; pom != NULL; pom = pom -> next){

            temp = Stvori(pom -> koef * drugi -> koef, pom -> pot + drugi -> pot);
            SortirajPriUnosu(temp, umnozak);
            printf("\nUsa san tu");
        }
    }

    return EXIT_SUCCESS;
}