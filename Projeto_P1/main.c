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


char menu();

int main()
{
    int
    numPE=0, //Port�teis Existentes
    numPD=0, //Port�teis Dispon�veis
    numTRE=0, //Total de Requisi��es Efetuadas
    numRA=0; //Requisi��es ativas

    return 0;
}

