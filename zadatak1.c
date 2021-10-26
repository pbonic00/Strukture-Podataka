#include <stdio.h>
#include <stdlib.h>
#define MAX_NAME 128
#define MAX_LINE 1024

typedef struct {
    char ime [MAX_NAME];
    char prezime [MAX_NAME];
    double br_bodova;
} student;


int procitajDat(char *nazivDat){
    int br = 0;
    char buffer [MAX_LINE] = {0};
    FILE* dat = NULL;
    dat = fopen(nazivDat, "r");
   
    if(!dat){
        printf("Neuspjelo otvaranje datoteke!\n");
        return -1;
    }

    while(!feof(dat)){
        fgets(buffer, MAX_LINE, dat);
        br++;
    }

    fclose(dat); 
    return br;
}


student* alocirajProcitaj(int br_stud, char *nazivDat){
    int brojac = 0;
    FILE* dat = NULL;
    student* studenti = NULL;

    studenti = (student*) malloc (br_stud * sizeof(student));
    dat = fopen(nazivDat, "r");
    if(!dat){
        printf("Greska pri alociranju");
        free (studenti);
        return NULL;
    }

    while(!feof(dat)){
        fscanf(dat, " %s %s %lf\n", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].br_bodova);
        brojac++;
    }

    fclose(dat);
    return studenti;
}


int maxBodovi (int brStudenata, student* studenti){
	int max, i, poz;
	max = studenti[0].br_bodova;
	i = 0;

	for(i=1; i<brStudenata; i++){
		if(studenti[i].br_bodova > max){
			max = studenti[i].br_bodova;
			poz = i;
		}
	}	

	return poz; 
}


void ispis(int brStud, student *studenti, double max){
	int i=0;
	double r;
	r = 0;
	
	for(i=0; i<brStud; i++){
		r = studenti[i].br_bodova / max * 100;
		printf(" %s %s %.2lf %.2lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].br_bodova, r);
	}
}


int main(){

	char* imeDatoteke = "studenti.txt";
	int brStud = 0;
	double maxBod;
	student* studenti = NULL;
 
	brStud = procitajDat (imeDatoteke);
	studenti = alocirajProcitaj (brStud, imeDatoteke);
	maxBod = studenti[maxBodovi(brStud, studenti)].br_bodova;
	ispis(brStud, studenti, maxBod);

	return 0;
	
}