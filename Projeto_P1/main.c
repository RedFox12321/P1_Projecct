#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "funcoes_auxiliares.c"
typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct{
    int nIdentif;
    char SerialNum[50];
    char CPU[20];
} Portatil;

int
numPE=0, //Port�teis Existentes
numPD=0, //Port�teis Dispon�veis
numTRE=0, //Total de Requisi��es Efetuadas
numRA=0; //Requisi��es ativas

void menu();

int main()
{
    lerInteiro("Indique um numero", 0, 50);
    menu();
    return 0;
}

void menu()
{
    printf("\t\t\tComputadores portateis\n"
           "Numero total de portateis - %d\n"
           "Numero de portateis disponiveis - %d\n"
           "Numero total de requisicoes efetuadas - %d\n"
           "Numero de requisicoes ativas - %d\n"
           , numPE, numPD, numTRE, numRA);
}
