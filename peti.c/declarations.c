#define _CRT_SECURE_NO_WARNINGS
#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Position CreateStackElement(double number)
{
    Position newElement = NULL;

    newElement = (Position)malloc(sizeof(StackElement));
    if (!newElement){
        perror("Can't allocate.");
        return NULL;
    }

    newElement->number = number;
    newElement->next = NULL;

    return newElement;
}



int InsertAfter(Position position, Position newElement)
{
    newElement->next = position->next;
    position->next = newElement;
}



int Push(Position head, double number)
{
    Position newElement = NULL;

    newElement = CreateStackElement(number);
    if (!newElement)
    {
        return -1;
    }

    InsertAfter(head, newElement);

    return EXIT_SUCCESS;
}



int DeleteAfter(Position position)
{
    Position temp = position->next;

    if (!temp)
    {
        return EXIT_SUCCESS;
    }

    else
    {
        position->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}



int Pop(double *destination, Position head)
{
    Position first = head -> next;

    if (!first)
    {
        perror("Postfix not valid! Please check your file\n");
        return -1;
    }

    *destination = first->number;
    DeleteAfter(head);

    return EXIT_SUCCESS;
}

int PerformOperation(Position head, char operation)
{

    double operand2 = 0;
    double operand1 = 0;
    double result = 0;

    int status1 = EXIT_SUCCESS, status2 = EXIT_SUCCESS;

    status2 = Pop(&operand2, head);
    if (status2 != EXIT_SUCCESS)
    {
        return -1;
    }

    status1 = Pop(&operand1, head);
    if (status2 != EXIT_SUCCESS)
    {
        return -2;
    }

    switch(operation)
    {
        case '+':{
            result = operand1 + operand2;
            break;
        }

        case '-':{
            result = operand1 - operand2;
            break;
        }

        case '*':{
            result = operand1 * operand2;
            break;
        }

        case '/':{
            if (operand2 == 0)
            {
                printf("Cannot divide with 0.\n");
                return -3;
            }
            result = operand1 / operand2;
            break;
        }

        default:
            printf("Thisw operation is not supported yet!\n");
            return -4;
    }

    Push(head, result);

    return EXIT_SUCCESS;
}


int CalculatePostfixFile(double *destination, char* fileName){

    FILE* file = NULL;
    int fLength = 0;
    char *buffer = NULL;
    char *currentBuffer  = NULL;
    int numBytes = 0;
    char operation = 0;
    double number = 0;
    int status = 0;
    StackElement head = {.number = 0, .next = NULL};

    file = fopen(fileName, "rb"); //binary file
    if(!file){
        perror("Cannot open file!\n");
        return -1;
    }

    fseek(file, 0, SEEK_END); //fseek(file, offset, whence), offset is the number of bytes to offset from whence which can be SEEK_SET, SEEK_CUR, SEEK_END
    fLength = ftell(file); //ftell now returns total size of file using current position

    buffer = (char*) calloc (fLength + 1, sizeof(char));
    if(!buffer){
        perror("Can't allocate memory");
        return 0;
    }

    rewind(file); //sets the file position to the beginning of the file of the given stream
    fread(buffer, sizeof(char), fLength, file);
    printf("%s\n", buffer);
    fclose(file);

    currentBuffer = buffer;

    while(strlen(currentBuffer) > 0){
        sscanf(currentBuffer, "%lf %n", &number, &numBytes);
        if(status == 1){
            Push(&head, number);
            currentBuffer += numBytes;
        }
        else{
            status = sscanf(currentBuffer, "%c %n", &operation, &numBytes);
            status = PerformOperation(&head, operation);  
            if(status != EXIT_SUCCESS){
                free(buffer);
                while(head.next != NULL){  
                    DeleteAfter(&head);
                }
                return -1;
            }

            currentBuffer += numBytes;
        }
    }

    free(buffer);

    if(head.next -> next){
        printf("Postfix not valid.\n");
        return EXIT_FAILURE;
    }

    Pop(destination, &head);


    return EXIT_SUCCESS;
}