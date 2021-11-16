//#define _CRT_SECURE_NO_WARNINGS
#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    char fileName[] = "postfix.txt";
    double rezultat = 0;

    if(CalculatePostfixFile(&rezultat, fileName) == EXIT_SUCCESS){
        printf("\nRezultat je %lf", rezultat);
        return EXIT_SUCCESS;
    }

    else    return EXIT_FAILURE;

    return 0;
}