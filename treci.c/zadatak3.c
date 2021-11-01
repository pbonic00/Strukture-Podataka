#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (30)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

//2. zadatak
int PrependList(Position head, char* name, char* surname, int birthYear);  
int PrintList(Position first);                                             
Position CreatePerson(char* name, char* surname, int birthYear);           
int InsertAfter(Position position, Position newPerson);                    
Position FindLast(Position head);                                          
int AppendList(Position head, char* name, char* surname, int birthYear);   
Position FindBySurname(Position first, char* surname);                     
Position FindBefore(Position first, Position position);                    
int DeleteAfter(Position head, char* surname); 
/*3. zadatak
koristeni -InsertAfter 
          -
          iz prethodnog zadataka
*/
int InsertBefore(Position who, Position where, Position first);
Position FindElement(Position first, char* surname);
int SortWhileInserting(Position head, Position newPerson);
int InsertInFile(Position head, char* nazivDat);
int InsertFromFile(Position head, char* nazivDat);


int main(int argc, char** argv)
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head, wantedPerson = NULL, pos = NULL;
    int i = 0;
    char sl = 'y', k = 'y';
    char name[MAX_SIZE];
    char surname [MAX_SIZE] = {0}, wantedSurname [MAX_SIZE] = {0}, nazivDat[MAX_SIZE] = {0};
    int birthYear;


    while(sl == 'y'){

        printf("\nIzbornik:\n1-dodavanje elementa na pocetak liste \n2-ispis liste \n3-dodavanje elementa na kraj liste \n4-pronalazenje elementa u listi po prezimenu \n5-brisanje elementa iz liste \n6-unosenje novog elementa prije zeljenog elementa \n7-Unosenje elementa poslije zeljenog elementa \n8-Sortiranje liste \n9-Unos u datoteke \n10-unos iz datoteke \nUnesite svoj izbor(jednoznamenkasti broj): ");
        scanf("%d", &i);
            
            switch(i){

                case 1: {
                    printf("\nUnesite ime: ");
                    scanf("%s", name);
                    printf("Unesite prezime: ");
                    scanf("%s", surname);
                    printf("Unesite godinu rodenja: ");
                    scanf("%d", &birthYear);

                    PrependList(p, name, surname, birthYear);
                    break;
                }
                

                case 2: {
                    PrintList(p -> next);
                    break;
                }
                
                case 3: {
                    printf("\nUnesite ime: ");
                    scanf("%s", name);
                    printf("Unesite prezime: ");
                    scanf("%s", surname);
                    printf("Unesite godinu rodenja: ");
                    scanf("%d", &birthYear);

                    AppendList(p, name, surname, birthYear);
                    break;
                }


                case 4: {
                    printf("\nKoje prezime zelite pronaci: ");
                    scanf("%s", surname);
                    wantedPerson = FindBySurname(p -> next, surname);
                    if(wantedPerson != NULL){
                        printf("Osoba je pronadena:\nIme: %s\nPrezime: %s\nGodina rodenja: %d", wantedPerson -> name, wantedPerson -> surname, wantedPerson -> birthYear);
                    }
                    else printf("Osoba s prezimenom %s nije pronadena.\n ", surname);
                    break;
                }

                case 5: {
                    printf("\nUnesite prezime osobe koju zelite izbrisati: ");
                    scanf("%s", surname);
                    DeleteAfter(p, surname);
                    break;
                }

                case 6: {
                    printf("\nOsoba koju zelite unijeti ");
                    printf("\nUnesite ime: ");
                    scanf("%s", name);
                    printf("Unesite prezime: ");
                    scanf("%s", surname);
                    printf("Unesite godinu rodenja: ");
                    scanf("%d", &birthYear);

                    wantedPerson = CreatePerson(name, surname, birthYear);

                    printf("\nUnesite prezime osobe ispred koje zelite unijeti novu osobu: ");
                    scanf("%s", wantedSurname);

                    pos = FindBySurname(p, wantedSurname);

                    InsertBefore(wantedPerson, pos, p);
                    break;
                    
                }

                case 7: {
                    printf("\nOsoba koju zelite unijeti ");
                    printf("\nUnesite ime: ");
                    scanf("%s", name);
                    printf("Unesite prezime: ");
                    scanf("%s", surname);
                    printf("Unesite godinu rodenja: ");
                    scanf("%d", &birthYear);

                    wantedPerson = CreatePerson(name, surname, birthYear);

                    printf("\nUnesite prezime osobe iza koje zelite unijeti novu osobu: ");
                    scanf("%s", wantedSurname);

                    pos = FindBySurname(p, wantedSurname);
                    if(pos){
                        InsertAfter(pos, wantedPerson);
                        printf("Novi element je unesen.\n");
                    }
                    else printf("Element iz kojeg zelite unijeti novi element ne postoji.\n");

                    break;
                }

                case 8:{
                    printf("\nOsoba koju zelite unijeti ");
                    printf("\nUnesite ime: ");
                    scanf("%s", name);
                    printf("Unesite prezime: ");
                    scanf("%s", surname);
                    printf("Unesite godinu rodenja: ");
                    scanf("%d", &birthYear);

                    wantedPerson = CreatePerson(name, surname, birthYear);
                    if(wantedPerson) SortWhileInserting(p, wantedPerson);
                    else printf("Osoba nije upisana.");
                    break;
                }

                case 9:{
                    char nazivDat[] = "ljudi";
                    InsertInFile(p, nazivDat);
                    break;
                }

                case 10:{
                    char nazivDat[] = "ljudi";
                    InsertFromFile(p, nazivDat);
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



	return EXIT_SUCCESS;
}


int PrependList(Position head, char* name, char* surname, int birthYear) {
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);

	if (!newPerson) {
        perror("Can't allocate memory! \n");
		return -1;
    }

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}


int PrintList(Position first) {
    Position temp = first;

	while (temp) {
		printf("\nIme: %s \nPrezime: %s" //spajanje dvi linije
		" \nGodina rodenja: %d", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
        printf("\n");
	}

	return EXIT_SUCCESS;
}


Position CreatePerson(char* name, char* surname, int birthYear) {
    Position newPerson = NULL;
    newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) {
		perror("Can't allocate memory! \n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}


int InsertAfter(Position position, Position newPerson) {
	newPerson -> next = position -> next;
    position -> next = newPerson;

    return EXIT_SUCCESS;
}


Position FindLast(Position head) {
	Position temp = head;

	while (temp->next) {
		temp = temp->next;
	}

	return temp;
}


int AppendList(Position head, char* name, char* surname, int birthYear) {
    Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);

	if (!newPerson) {
        perror("Can't allocate memory! \n");
		return -1;
	}

	last = FindLast(head);
    InsertAfter(last, newPerson);
	
    return EXIT_SUCCESS;
}


Position FindBySurname(Position first, char* surname) {
    Position temp = first;

	while (temp) {
		if (strcmp(temp->surname, surname) == 0)
			return temp;
        temp = temp -> next;
	}

	return NULL;
}


Position FindBefore(Position first, Position position){
    Position temp = first;
    while(temp){
        if(temp->next == position)
            return temp;
        temp = temp -> next;
    }
    return NULL;
}


int DeleteAfter(Position head, char* surname){
    Position temp1 = NULL;
    Position temp2 = NULL;

    temp2 = FindBySurname(head, surname);
    if(temp2 != NULL){
        temp1 = FindBefore (head, temp2);
        if(temp1 != NULL){
            temp1 -> next = temp2 -> next;
            free (temp2);
        }
        printf("Osoba s prezimenom %s je uspjesno izbrisana.\n", surname);
    }
    else printf("Osoba s prezimenom %s nije pronadena.\n", surname);

    return EXIT_SUCCESS;
}


int InsertBefore(Position who, Position where, Position first){
    Position temp = NULL;
    if(where != NULL){
        temp = FindBefore(first, where);
        if(temp){
            InsertAfter(temp, who);
             printf("Novi element je unesen.");
        }
        else printf("Greska.\n");
    }
    else printf("Element ispred kojeg zelite unijeti novi element ne postoji!\n");

    return EXIT_SUCCESS;
}

int SortWhileInserting(Position head, Position newPerson){
    Position temp = NULL;
    temp = head -> next;

    while(strcmp( newPerson->surname, temp->next->surname ) > 0){
        temp = temp -> next;
    }

    InsertAfter(temp, newPerson);
    return EXIT_SUCCESS;
}

int InsertInFile(Position head, char* nazivDat){
    Position temp = head -> next;

    FILE* dat = NULL;
    dat = fopen(nazivDat, "w");

    if(!dat){
        printf("Greska pri alociranju.\n"); //zasto izbacuje ovo kad se upise .txt u imenu
        return -1;
    }

    while(temp){
         fprintf(dat, "%s %s %d\n", temp -> name, temp -> surname, temp -> birthYear);
         temp = temp -> next;
    }
    fclose(dat);

    return EXIT_SUCCESS;
}

int InsertFromFile(Position head, char* nazivDat){
    FILE* dat = NULL;
    dat = fopen(nazivDat, "r");
    char name[MAX_SIZE] = {0}, surname[MAX_SIZE] = {0}, buffer = {0};
    int birthYear = 0;

    Position newPerson = 0, temp = head;

    if(!dat){
        printf("Greska pri alociranju.\n");
        return -1;
    }

    while(!feof(dat)){
            fscanf(dat, "%s %s %d\n", name, surname, &birthYear);
            AppendList(head, name, surname, birthYear);
    }

    fclose(dat);
    return EXIT_SUCCESS;
}