#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_portateis.h"
#include "funcoes_avarias.h"
#include "funcoes_requisicoes.h"
#include "funcoes_ficheiros.h"
#include "funcoes_informacoes.h"

char menu(int numTPE, int numPD, int numTRE, int numRA);
char menuPortateis(int numTPE, int numPD, int numTRE, int numRA);
char menuAvarias(int numTPE, int numPD, int numTRE, int numRA);
char menuRequisicoes(int numTPE, int numPD, int numTRE, int numRA);
char menuFicheiro(int numTPE, int numPD, int numTRE, int numRA);
char menuInformacoes(int numTPE, int numPD, int numTRE, int numRA);

int main()
{
    int numTPE=0, //Total de Portateis Existentes
    numPD=0, //Portateis Disponiveis
    numTRE=0, //Total de Requisicoes Efetuadas
    numRA=0, //Requisicoes ativas
    numTA=0; //Total de avarias
    dadosPortatil portateis[MAX_PORTATEIS];
    dadosRequisicao *requisicoes;
    dadosAvaria *avarias;
    requisicoes = NULL;
    avarias = NULL;
    char opcao='v'; //inicializar no menu
    do
    {
        switch(opcao)
        {
        case 'v':                                                   //Menu principal
            opcao = menu(numTPE, numPD, numTRE, numRA);
            break;
        case 'p':                                                   //Submenu da parte dos portateis
            opcao = menuPortateis(numTPE, numPD, numTRE, numRA);
            switch(opcao)
            {
            case 'i':
                if(numTPE == MAX_PORTATEIS)
                {
                    printf("\nChegou ao limite maximo de portatateis.\n");
                }
                else
                {
                    adicionarPortatil(portateis, &numTPE);
                    numPD++;
                }
                opcao = 'p';
                break;
            case 'a':
                if(numTPE==0)
                {
                    printf("\nNao existem portateis para alterar.\n");
                }
                else
                {
                    alterarDadosPortatil(portateis, numTPE);
                }
                opcao = 'p';
                break;
            case 'm':
                if(numTPE==0)
                {
                    printf("\nAinda nao existem dados de portateis.\n");
                }
                else
                {
                    mostrarDadosPortateis(portateis, numTPE);
                }
                opcao = 'p';
            }
            break;
        case 'a':                                                   //Submenu da parte das avarias
            opcao = menuAvarias(numTPE, numPD, numTRE, numRA);
            switch(opcao)
            {
            case 't':
                if(numTPE==0)
                {
                    printf("\nNao existem portateis para registar a avaria/reparo.\n");
                }
                else
                {
                    avarias = trocarAvaria(portateis, numTPE, avarias, requisicoes, numTRE, &numTA, &numPD);
                }
                opcao = 'a';
                break;
            case 'm':
                if(numTA==0)
                {
                    printf("\nAinda nao foi registada nenhuma avaria.\n");
                }
                else
                {
                    mostrarAvarias(portateis, avarias, numTA, numTPE);
                }
                opcao = 'a';
            }
            break;
        case 'r':                                                   //Submenu da parte das reservas
            opcao = menuRequisicoes(numTPE, numPD, numTRE, numRA);
            switch(opcao)
            {
            case 'a':
                if(numTPE==0)
                {
                    printf("\nAinda nao existem dados de portateis.\n");
                }
                else
                {
                    if(numRA==0 && numPD==0)
                    {
                        printf("\nTodos os portateis estao avariados, por isso nao e possivel registar uma requisicao.\n");
                    }
                    else
                    {
                    requisicoes = efetuarRequisicao(portateis, numTPE, requisicoes, &numTRE, &numPD, &numRA);
                    }
                }
                opcao = 'r';
                break;
            case 'r':
                if(numRA==0)
                {
                    printf("\nNao existem requisicoes para renovar.\n");
                }
                else
                {
                    renovarRequisicao(requisicoes, numTRE);
                }
                opcao = 'r';
                break;
            case 'd':
                if(numRA==0)
                {
                    printf("\nNao existem requisicoes para fazer devolucao.\n");
                }
                else
                {
                    efetuarDevolucao(requisicoes, portateis, numTRE, numTPE);
                    numRA--;
                    numPD++;
                }
                opcao = 'r';
                break;
            case 'p':
                if(numTRE==0)
                {
                    printf("\nNao existem dados de requisicoes ainda.\n");
                }
                else
                {
                    pesquisarRequisicao(requisicoes, portateis, numTRE, numTPE);
                }
                opcao = 'r';
                break;
            case 'm':
                if(numTRE==0)
                {
                    printf("\nNao existem dados de requisicoes ainda.\n");
                }
                else
                {
                    mostrarDadosRequisicao(requisicoes, numTRE);
                }
                opcao = 'r';
            }
            break;
        case 'f':                                                   //Submenu da parte dos ficheiros
            opcao = menuFicheiro(numTPE, numPD, numTRE, numRA);
            switch(opcao)
            {
            case 'b':
                gravarFicheiroBinario(portateis, avarias, requisicoes, numTPE, numPD, numTRE, numRA, numTA);
                opcao = 'f';
                break;
            case 't':
                gravarFicheiroBinario_Log(portateis, avarias, requisicoes, numTPE, numPD, numTRE, numRA, numTA);
                opcao = 'f';
                break;
            case 'c':
                carregarFicheiroBinario(portateis, avarias, requisicoes, &avarias, &requisicoes, &numTPE, &numPD, &numTRE, &numRA, &numTA);
                opcao = 'f';
            }
            break;
        case 'i':                                                   //Submenu
            opcao = menuInformacoes(numTPE, numPD, numTRE, numRA);
            switch(opcao)
            {
            case 't':
                if(numTPE==0)
                {
                    printf("\nAinda nao existem dados de portateis.\n");
                }
                else
                {
                    mostrarTudo(portateis, avarias, requisicoes, numTPE, numTA, numTRE);
                }
                opcao = 'i';
                break;
            case 'd':
                if(numTPE==0)
                {
                    printf("\nAinda nao existem dados de portateis.\n");
                }
                else
                {
                    mostrarPortatil(portateis, avarias, requisicoes, numTPE, numTA, numTRE);
                }
                opcao = 'i';
                break;
            case 'p':
                if(numTPE==0)
                {
                    printf("\nAinda nao existem dados de portateis.\n");
                }
                else
                {
                    mostraProcessadores(portateis, numTPE);
                }
                opcao = 'i';
                break;
            case 'm':
                if(numTRE==0)
                {
                    printf("\nAinda nao existem requisicoes de portateis.\n");
                }
                else
                {
                    mediaMulta(requisicoes, numTRE);
                }
                opcao = 'i';
                break;
            case 'u':
                if(numTRE==0)
                {
                    printf("\nAinda nao existem requisicoes de portateis.\n");
                }
                else
                {
                    utenteRequisitacoes(requisicoes, numTRE);
                }
                opcao = 'i';
                break;
            case 'r':
                if(numRA>=numTRE)
                {
                    printf("\nAinda nao existem devolucoes de portateis.\n");
                }
                else
                {
                    mostrarDevolucaoRecente(requisicoes, numTRE);
                }
                opcao = 'i';
            }
        }
    }
    while(opcao != 's');
    free(requisicoes);
    free(avarias);
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
               "A - Avarias\n"
               "R - Requisicoes\n"
               "F - Ficheiros\n"
               "I - Informacoes\n"
               "S - Sair\n"
               , numTPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
        if(opcao != 'p' && opcao != 'a' && opcao != 'r' && opcao != 'f' && opcao != 'i' && opcao != 's')
        {
            printf("Nao e uma opcao valida!\n");
        }
    }
    while(opcao != 'p' && opcao != 'a' && opcao != 'r' && opcao != 'f' && opcao != 'i' && opcao != 's');
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
               "M - Mostrar dados dos portateis\n"
               "V - Voltar\n"
               , numTPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
        if(opcao != 'i' && opcao != 'a' && opcao != 'm' && opcao != 'v')
        {
            printf("Nao e uma opcao valida!\n");
        }
    }
    while(opcao != 'i' && opcao != 'a' && opcao != 'm' && opcao != 'v');
    return opcao;
}

char menuAvarias(int numTPE, int numPD, int numTRE, int numRA)
{
    char opcao = '\0';
    do
    {
        printf("\n\t\t\tComputadores portateis\n"
               "Numero total de portateis - %03d\t\t\t\tNumero total de requisicoes efetuadas - %03d\n"
               "Numero de portateis disponiveis - %03d\t\t\tNumero de requisicoes ativas - %03d\n"
               "\n"
               "\t\t\t____________________________________________\n"
               "T - Trocar estado de um portatil\n"
               "M - Mostrar dados das avarias dos portateis\n"
               "V - Voltar\n"
               , numTPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
        if(opcao != 't' && opcao != 'm' && opcao != 'v')
        {
            printf("Nao e uma opcao valida!\n");
        }
    }
    while(opcao != 't' && opcao != 'm' && opcao != 'v');
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
               "D - Fazer Devolucao\n"
               "P - Pesquisar dados sobre uma requisicao\n"
               "M - Mostrar dados das requisicoes\n"
               "V - Voltar\n"
               , numTPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
        if(opcao != 'a' && opcao != 'r' && opcao != 'd' && opcao != 'p' && opcao != 'm' && opcao != 'v')
        {
            printf("Nao e uma opcao valida!\n");
        }
    }
    while(opcao != 'a' && opcao != 'r' && opcao != 'd' && opcao != 'p' && opcao != 'm' && opcao != 'v');
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
               "T - Gravar ficheiro binario (com Data Log)\n"
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

char menuInformacoes(int numTPE, int numPD, int numTRE, int numRA)
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
               "T - Mostrar todos os dados existentes\n"
               "D - Mostrar todos os dados de um portatil\n"
               "P - Lista de todos os processadores\n"
               "M - Media das multas pagas\n"
               "U - Dados sobre utentes\n"
               "R - Devolucao mais recente\n"
               "V - Voltar\n"
               , numTPE, numTRE, numPD, numRA);
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
        if(opcao != 't' && opcao != 'd' && opcao != 'p' && opcao != 'm' && opcao != 'u' && opcao != 'r' && opcao != 'v')
        {
            printf("Nao e uma opcao valida!\n");
        }
    }
    while(opcao != 't' && opcao != 'd' && opcao != 'p' && opcao != 'm' && opcao != 'u' && opcao != 'r' && opcao != 'v');
    return opcao;
}
