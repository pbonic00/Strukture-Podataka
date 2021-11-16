#ifndef DECLARATIONS_H
#define DECLARATIONS_H

struct _StackElement;
typedef struct _StackElement* Position;
typedef struct _StackElement{
    double number;
    Position next;
} StackElement;

Position CreateStackElement(double number);
int InsertAfter(Position position, Position newElement);
int Push(Position head, double number);
int DeleteAfter(Position position);
int Pop(double* destination, Position head); //salje adresu di ce zapisat rezultat, a ako ne uspije ne minja se
int PerformOperation(Position head, char operation);
int CalculatePostfixFile(double *destination, char* fileName);

#endif