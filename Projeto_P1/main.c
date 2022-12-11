#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "funcoes_auxiliares.c"

#define max_portateis 30
typedef struct{
    int dia;
    int mes;
    int ano;
} data;

typedef struct{
    int nIdentif;
    data dataReserva;
} reserva;

typedef struct{
    int nIdentif;
    char SerialNum[50];
    char CPU[20];
} portatil;


char menu(int numPE, int numPD, int numTRE, int numRA);
char menuPortateis(int numPE, int numPD, int numTRE, int numRA);
char menuReservas(int numPE, int numPD, int numTRE, int numRA);
char menuFicheiro(int numPE, int numPD, int numTRE, int numRA);

int main()
{
    int
    numPE=0, //Total de Portateis Existentes
    numPD=0, //Portateis Disponiveis
    numTRE=0, //Total de Requisicoes Efetuadas
    numRA=0, //Requisicoes ativas
    numPortateis=0;
    portatil portateis[max_portateis];
    char opcao='v';
    do
    {
        switch(opcao)
        {
        case 'v': //Menu principal
            opcao = menu(numPE=0, numPD=0, numTRE=0, numRA=0);
            break;
        case 'p': //Submenu da parte dos portateis
            opcao = menuPortateis(numPE=0, numPD=0, numTRE=0, numRA=0);
            switch(opcao)
            {
            case 'a':
                numPE++;
                numPD++;

                opcao = 'p';
                break;
            case 'r':
                numPD--;

                opcao = 'p';
                break;
            case 'm':

                opcao = 'p';
                break;
            }
            break;
        case 'r': //Submenu da parte das reservas
            opcao = menuReservas(numPE=0, numPD=0, numTRE=0, numRA=0);
            switch(opcao)
            {
            case 'a':
                numTRE++;
                numRA++;

                opcao = 'r';
                break;
            case 'r':
                numRA--;

                opcao = 'r';
                break;
            case 'm':

                opcao = 'r';
                break;
            }
            break;
        case 'f': //Submenu da parte dos ficheiros
            opcao = menuFicheiro(numPE=0, numPD=0, numTRE=0, numRA=0);
            switch(opcao)
            {
            case 'b':

                opcao = 'f';
                break;
            case 't':

                opcao = 'f';
                break;
            case 'l':

                opcao = 'f';
                break;
            }
        }
    }
    while(opcao != 's');
    //free();
    return 0;
}

char menu(int numPE, int numPD, int numTRE, int numRA)
{
    char opcao = '\0';
    do
    {
        printf("\t\t\tComputadores portateis\n"
               "Numero total de portateis - %03d\t\t\t\tNumero total de requisicoes efetuadas - %03d\n"
               "Numero de portateis disponiveis - %03d\t\t\tNumero de requisicoes ativas - %03d\n"
               "\n"
               "\t\t\t____________________________________________\n"
               "\n"
               "P - Portateis\n"
               "R - Reservas\n"
               "F - Ficheiros\n"
               "S - Sair\n"
               "\tOpcao -> "
               , numPE, numPD, numTRE, numRA);
        opcao = tolower(getc(stdin));
        limpaBufferStdin();
    }
    while(opcao != 'p' && opcao != 'r' && opcao != 'f' && opcao != 's');
    return opcao;
}

char menuPortateis(int numPE, int numPD, int numTRE, int numRA)
{
    char opcao = '\0';
    do
    {
        printf("\t\t\tComputadores portateis\n"
               "Numero total de portateis - %03d\t\t\t\tNumero total de requisicoes efetuadas - %03d\n"
               "Numero de portateis disponiveis - %03d\t\t\tNumero de requisicoes ativas - %03d\n"
               "\n"
               "\t\t\t____________________________________________\n"
               "\n"
               "A - Adicionar portatil\n"
               "R - Remover portatil\n"
               "M - Mostrar os dados de todos os portateis\n"
               "V - Voltar\n"
               "\tOpcao -> "
               , numPE, numPD, numTRE, numRA);
        opcao = tolower(getc(stdin));
        limpaBufferStdin();
    }
    while(opcao != 'a' && opcao != 'r' && opcao != 'm' && opcao != 'v');

    return opcao;
}

char menuReservas(int numPE, int numPD, int numTRE, int numRA)
{
    char opcao = '\0';
    do
    {
        printf("\t\t\tComputadores portateis\n"
               "Numero total de portateis - %03d\t\t\t\tNumero total de requisicoes efetuadas - %03d\n"
               "Numero de portateis disponiveis - %03d\t\t\tNumero de requisicoes ativas - %03d\n"
               "\n"
               "\t\t\t____________________________________________\n"
               "\n"
               "A - Adicionar reserva\n"
               "R - Remover reserva\n"
               "M - Mostrar todas as reservas\n"
               "V - Voltar\n"
               "\tOpcao -> "
               , numPE, numPD, numTRE, numRA);
        opcao = tolower(getc(stdin));
        limpaBufferStdin();
    }
    while(opcao != 'a' && opcao != 'r' && opcao != 'm' && opcao != 'v');

    return opcao;
}

char menuFicheiro(int numPE, int numPD, int numTRE, int numRA)
{
    char opcao = '\0';
    do
    {
        printf("\t\t\tComputadores portateis\n"
               "Numero total de portateis - %03d\t\t\t\tNumero total de requisicoes efetuadas - %03d\n"
               "Numero de portateis disponiveis - %03d\t\t\tNumero de requisicoes ativas - %03d\n"
               "\n"
               "\t\t\t____________________________________________\n"
               "\n"
               "B - Gravar ficheiro binario\n"
               "T - Gravar ficheiro binario e de texto\n"
               "L - Ler ficheiro binario\n"
               "V - Voltar\n"
               "\tOpcao -> "
               , numPE, numPD, numTRE, numRA);
        opcao = tolower(getc(stdin));
        limpaBufferStdin();
    }
    while(opcao != 'b' && opcao != 't' && opcao != 'l' && opcao != 'v');

    return opcao;
}

