#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "funcoes_portateis.h"
#include "funcoes_requisicoes.h"
#include "funcoes_ficheiros.h"

char menu(int numTPE, int numPD, int numTRE, int numRA);
char menuPortateis(int numTPE, int numPD, int numTRE, int numRA);
char menuRequisicoes(int numTPE, int numPD, int numTRE, int numRA);
char menuFicheiro(int numTPE, int numPD, int numTRE, int numRA);

int main()
{
    int
    numTPE=0, //Total de Portateis Existentes
    numPD=0, //Portateis Disponiveis
    numTRE=0, //Total de Requisicoes Efetuadas
    numRA=0; //Requisicoes ativas
    dadosPortatil portateis[MAX_PORTATEIS];
    dadosRequisisao *requisicoes;
    requisicoes = NULL;
    char opcao='v'; //inicializar no menu
    do
    {
        switch(opcao)
        {
        case 'v': //Menu principal
            opcao = menu(numTPE, numPD, numTRE, numRA);
            if(opcao == 'm')
            {

                opcao = 'v';
            }
            break;
        case 'p': //Submenu da parte dos portateis
            opcao = menuPortateis(numTPE, numPD, numTRE, numRA);
            switch(opcao)
            {
            case 'i':
                adicionarPortatil(portateis, &numPD, &numTPE);
                opcao = 'p';
                break;
            case 'a':

                opcao = 'p';
                break;
            case 'r':

                opcao = 'p';
                break;
            case 'd':

                opcao = 'p';
                break;
            case 'p':

                opcao = 'p';
                break;
            case 'm':
                mostrarDadosPortateis(portateis, numPD);
                opcao = 'p';
            }
            break;
        case 'r': //Submenu da parte das reservas
            opcao = menuRequisicoes(numTPE, numPD, numTRE, numRA);
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
            opcao = menuFicheiro(numTPE, numPD, numTRE, numRA);
            switch(opcao)
            {
            case 'b':
                gravarFicheiroBinario(portateis, numPD, numTPE);
                opcao = 'f';
                break;
            case 't':
                gravarFicheiroBinario_Log(portateis, numPD, numTPE);
                opcao = 'f';
                break;
            case 'c':
                carregarFicheiroBinario(portateis, &numPD, &numTPE);
                opcao = 'f';
            }
        }
    }
    while(opcao != 's');
    free(requisicoes);
    return 0;
}

char menu(int numTPE, int numPD, int numTRE, int numRA)
{
    char opcao = '\0';
    do
    {
        printf("\n\t\t\tComputadores portateis\n"
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
               , numTPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
        if(opcao != 'p' && opcao != 'r' && opcao != 'f' && opcao != 'm' && opcao != 's')
        {
            printf("Nao e uma opcao valida!\n");
        }
    }
    while(opcao != 'p' && opcao != 'r' && opcao != 'f' && opcao != 'm' && opcao != 's');
    return opcao;
}

char menuPortateis(int numTPE, int numPD, int numTRE, int numRA)
{
    char opcao = '\0';
    do
    {
        printf("\n\t\t\tComputadores portateis\n"
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
               , numTPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
        if(opcao != 'i' && opcao != 'a' && opcao != 'd' && opcao != 'r' && opcao != 'm' && opcao != 'p' && opcao != 'v')
        {
            printf("Nao e uma opcao valida!\n");
        }
    }
    while(opcao != 'i' && opcao != 'a' && opcao != 'd' && opcao != 'r' && opcao != 'm' && opcao != 'p' && opcao != 'v');
    return opcao;
}

char menuRequisicoes(int numTPE, int numPD, int numTRE, int numRA)
{
    char opcao = '\0';
    do
    {
        printf("\n\t\t\tComputadores portateis\n"
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
               , numTPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
        if(opcao != 'a' && opcao != 'r' && opcao != 'e' && opcao != 'd' && opcao != 'p' && opcao != 'm' && opcao != 'v')
        {
            printf("Nao e uma opcao valida!\n");
        }
    }
    while(opcao != 'a' && opcao != 'r' && opcao != 'e' && opcao != 'd' && opcao != 'p' && opcao != 'm' && opcao != 'v');
    return opcao;
}

char menuFicheiro(int numTPE, int numPD, int numTRE, int numRA)
{
    char opcao = '\0';
    do
    {
        printf("\n\t\t\tComputadores portateis\n"
               "Numero total de portateis - %03d\t\t\t\tNumero total de requisicoes efetuadas - %03d\n"
               "Numero de portateis disponiveis - %03d\t\t\tNumero de requisicoes ativas - %03d\n"
               "\n"
               "\t\t\t____________________________________________\n"
               "\n"
               "B - Gravar ficheiro binario\n"
               "T - Gravar ficheiro binario e de texto\n"
               "C - Carregar ficheiro binario\n"
               "V - Voltar\n"
               , numTPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
        if(opcao != 'b' && opcao != 't' && opcao != 'c' && opcao != 'v')
        {
            printf("Nao e uma opcao valida!\n");
        }
    }
    while(opcao != 'b' && opcao != 't' && opcao != 'c' && opcao != 'v');
    return opcao;
}

