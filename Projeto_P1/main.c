#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "funcoes_auxiliares.c"
#include "constantes.h"

typedef struct{
    int dia;
    int mes;
    int ano;
} data;

typedef struct{
    int nIdentif;
    char codigo[10];
    char nomeUtente[80];
    int tipoUtente;
    data dataRequisicao;
    data dataDevolucao;
    int estado;

} dadosRequisisao;

typedef struct{
    int nIdentif; //
    char SerialNum[50]; //
    char CPU[10]; //
    int RAM; //
    int estado; //
    int localizacao; //
    data dataAquisicao;
    int valor;
} dadosPortatil;


char menu(int numPE, int numPD, int numTRE, int numRA);
char menuPortateis(int numPE, int numPD, int numTRE, int numRA);
char menuRequisicoes(int numPE, int numPD, int numTRE, int numRA);
char menuFicheiro(int numPE, int numPD, int numTRE, int numRA);

int main()
{
    int
    numPE=0, //Total de Portateis Existentes
    numPD=0, //Portateis Disponiveis
    numTRE=0, //Total de Requisicoes Efetuadas
    numRA=0, //Requisicoes ativas
    numPortateis=0, //Numero total de portateis no vetor portateis
    numRequisicoes=0; //Numero total de requisicoes no vetor *requisicoes
    dadosPortatil portateis[MAX_PORTATEIS];
    dadosRequisisao *requisicoes;
    requisicoes = NULL;
    char opcao='v'; //inicializar no menu
    do
    {
        switch(opcao)
        {
        case 'v': //Menu principal
            opcao = menu(numPE, numPD, numTRE, numRA);
            if(opcao == 'm')
            {

                opcao = 'v';
            }
            break;
        case 'p': //Submenu da parte dos portateis
            opcao = menuPortateis(numPE, numPD, numTRE, numRA);
            switch(opcao)
            {
            case 'i':

                numPE++;
                numPD++;
                opcao = 'p';
                break;
            case 'a':

                opcao = 'p';
                break;
            case 'r':

                numPD--;
                opcao = 'p';
                break;
            case 'd':

                opcao = 'p';
                break;
            case 'p':

                opcao = 'p';
                break;
            case 'm':

                opcao = 'p';
            }
            break;
        case 'r': //Submenu da parte das reservas
            opcao = menuRequisicoes(numPE, numPD, numTRE, numRA);
            switch(opcao)
            {
            case 'a':

                numTRE++;
                numRA++;
                opcao = 'r';
                break;
            case 'r':

                opcao = 'r';
                break;
            case 'e':

                numRA--;
                opcao = 'r';
                break;
            case 'p':

                opcao = 'r';
                break;
            case 'm':

                opcao = 'r';
            }
            break;
        case 'f': //Submenu da parte dos ficheiros
            opcao = menuFicheiro(numPE, numPD, numTRE, numRA);
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
            }
        }
    }
    while(opcao != 's');
    free(requisicoes);
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
               "M - Mostrar todos os dados\n"
               "S - Sair\n"
               , numPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
    }
    while(opcao != 'p' && opcao != 'r' && opcao != 'f' && opcao != 'm' && opcao != 's');
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
               "I - Inserir portatil\n"
               "A - Alterar dados de um portatil\n"
               "D - Adicionar dados sobre a avaria/reparacao de um portatil\n"
               "R - Remover portatil\n"
               "M - Mostrar dados dos portateis\n"
               "P - Mostrar avarias\n"
               "V - Voltar\n"
               , numPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
    }
    while(opcao != 'i' && opcao != 'a' && opcao != 'd' && opcao != 'r' && opcao != 'm' && opcao != 'p' && opcao != 'v');
    return opcao;
}

char menuRequisicoes(int numPE, int numPD, int numTRE, int numRA)
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
               "A - Adicionar requisicao\n"
               "R - Renovar a requisicao\n"
               "E - Eliminar requisicao\n"
               "D - Fazer a Devolucao\n"
               "P - Pesquisar dados sobre uma requisicao\n"
               "M - Mostrar dados das requisicoes\n"
               "V - Voltar\n"
               , numPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
    }
    while(opcao != 'a' && opcao != 'r' && opcao != 'e' && opcao != 'd' && opcao != 'p' && opcao != 'm' && opcao != 'v');
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
               , numPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
    }
    while(opcao != 'b' && opcao != 't' && opcao != 'l' && opcao != 'v');
    return opcao;
}

