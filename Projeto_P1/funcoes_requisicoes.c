#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_portateis.h"
#include "funcoes_requisicoes.h"

dadosRequisicao *efetuarRequisicao(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis, dadosRequisicao arrayRequisicoes[], int *numRequisicoes, int *numPD, int *numRA)
{
    int pos, posReq;
    char codigo[MAX_CODIGO];
    dadosRequisicao *backup;
    backup = arrayRequisicoes;
    arrayRequisicoes = realloc(arrayRequisicoes, (*numRequisicoes+1)*sizeof(dadosRequisicao));
    if(arrayRequisicoes==NULL)
    {
        arrayRequisicoes = backup;
        printf("\nErro ao reservar memoria para adicionar requisicao\n");
    }
    else
    {
        do
        {
            mostrarDadosPortateis(arrayPortateis, numPortateis);
            pos = pedirPosicao(arrayPortateis,numPortateis);
            if(arrayPortateis[pos].estado.estado==-1)
            {
                printf("\nNao e possivel requisitar o portatil, pois foi requisitado anteriormente.\n");    //no caso de estado "requisitado"
            }
            if(arrayPortateis[pos].estado.estado==1)
            {
                printf("\nNao e possivel requisitar o portatil, pois apresenta estar avariado.\n");         //no caso de estado "avariado"
            }
        }
        while(arrayPortateis[pos].estado.estado==-1 || arrayPortateis[pos].estado.estado==1);
            do
            {
                lerString("\nCodigo da Requisicao: ", codigo, MAX_CODIGO);
                posReq = procuraCodigo(arrayRequisicoes, *numRequisicoes, codigo);
                if(posReq!=-1){
                    printf("\n Ja existe uma requisicao com este codigo!\n");
                }
            }
            while(posReq!=-1);

            strcpy(arrayRequisicoes[*numRequisicoes].codigo, codigo);
            arrayPortateis[pos].estado.estado = -1;
            arrayRequisicoes[*numRequisicoes].estado=1;
            arrayRequisicoes[*numRequisicoes].recente=0;
            arrayRequisicoes[*numRequisicoes].nIdentif=arrayPortateis[pos].dataPortatil.nIdentif;
            lerString("\nNome do Utente Requisitante: ",arrayRequisicoes[*numRequisicoes].nomeUtente,MAX_NAME_CHARACTERS);
            escolherTipoUtente(arrayRequisicoes[*numRequisicoes].tipoUtente);
            arrayRequisicoes[*numRequisicoes].dataRequisicao=pedirData("\nData do Inicio da Requisicao: ",arrayPortateis[pos].dataPortatil.dataAquisicao.ano,arrayPortateis[pos].dataPortatil.dataAquisicao.mes,arrayPortateis[pos].dataPortatil.dataAquisicao.dia);
            arrayRequisicoes[*numRequisicoes].prazo=lerInteiro("Por quantos dias sera requisitado:",1,30);
            arrayRequisicoes[*numRequisicoes].multa=0.0;
            arrayPortateis[pos].numRequisicoes++;
            (*numRequisicoes)++;
            (*numPD)--;
            (*numRA)++;
            printf("\nEstado trocado com sucesso.\n");
    }
    return arrayRequisicoes;
}

void mostrarDadosRequisicao(dadosRequisicao arrayRequisicoes[], int numRequisicoes)
{
    int i;
    printf("\nNumero   Cod. Requisicao\tRequisitante\t      Tipo Utente      \tData de requisicao\tDias Requisitados\tEstado\n");
    for(i=0; i<numRequisicoes; i++)
    {

        printf("%5i    %15s\t%12s\t%16s\t       %02d/%02d/%4d\t%12d dias\t", arrayRequisicoes[i].nIdentif, arrayRequisicoes[i].codigo, arrayRequisicoes[i].nomeUtente,
               arrayRequisicoes[i].tipoUtente, arrayRequisicoes[i].dataRequisicao.dia,arrayRequisicoes[i].dataRequisicao.mes,arrayRequisicoes[i].dataRequisicao.ano
               ,arrayRequisicoes[i].prazo);
        switch(arrayRequisicoes[i].estado)
        {
        case 0:
            printf("Concluida\n");
            break;
        case 1:
            printf("Ativa\n");
        }
    }
}

int procurarRequisicaoAtiva(dadosRequisicao arrayRequisicoes[], int numRequisicoes)
{
    int i,pos=-1,renovacao;
    char codigo[MAX_CODIGO];

    lerString("\nDigite o Codigo da Requisicao: ", codigo, MAX_CODIGO);
    for(i=0; i<numRequisicoes; i++)
    {
        if(strcmp(codigo, arrayRequisicoes[i].codigo)==0 && arrayRequisicoes[i].estado==1)
        {
            pos=i;
            i=numRequisicoes;
        }
    }
    return pos;
}

void renovarRequisicao(dadosRequisicao arrayRequisicoes[], int numRequisicoes)
{
    int pos;
    mostrarDadosRequisicao(arrayRequisicoes,numRequisicoes);
    do
    {
        pos=procurarRequisicaoAtiva(arrayRequisicoes, numRequisicoes);
        if(pos==-1)
        {
            printf("\nNao existe nenhuma requisicao ativa com este codigo.\n");
        }
    }
    while(pos==-1);
    arrayRequisicoes[pos].prazo+=lerInteiro("Por quanto tempo pretende renovar a requisicao?",1,7);
}

void efetuarDevolucao(dadosRequisicao arrayRequisicoes[], dadosPortatil arrayPortateis[MAX_PORTATEIS], int numRequisicoes, int numPortateis)
{
    int i, posReq;
    mostrarDadosRequisicao(arrayRequisicoes,numRequisicoes);
    do
    {
        posReq = procurarRequisicaoAtiva(arrayRequisicoes, numRequisicoes);
        if(posReq==-1)
        {
            printf("\nNao existe nenhuma requisicao ativa com este codigo.\n");
        }
    }
    while(posReq==-1);
    registarRequisicao_Log(arrayRequisicoes, arrayPortateis, numRequisicoes, numPortateis, posReq);
}

int pesquisarRequisicao(dadosRequisicao arrayRequisicoes[], dadosPortatil arrayPortateis[MAX_PORTATEIS], int numRequisicoes, int numPortateis)
{
    int pos, posReq;
    char codigo[MAX_CODIGO];
    mostrarDadosRequisicao(arrayRequisicoes, numRequisicoes);
    do
    {
        lerString("\nCodigo da Requisicao:",codigo,MAX_CODIGO);
        posReq = procuraCodigo(arrayRequisicoes, numRequisicoes, codigo);
        if(posReq==-1)
        {
            printf("Nao existe requisicao com esse codigo de identificacao.\n");
        }
    }
    while(posReq==-1);
    pos = procuraPortatil(arrayPortateis, numPortateis, arrayRequisicoes[posReq].nIdentif);
    printf("\n\t___Dados da Requisicao___\n"
           "Numero de Identidficacao: %d\n"
           "Processador(CPU): Intel i%d\n"
           "Memoria(RAM): %d GB\n"
           "Codigo: %s\n"
           "Utente: %s\n"
           "Nome do utente: %s\n"
           "Requisitado por: %d dias\n"
           "Data de requisicao: %02d/%02d/%4d\n",
           arrayRequisicoes[posReq].nIdentif, arrayPortateis[pos].dataPortatil.CPU, arrayPortateis[pos].dataPortatil.RAM ,arrayRequisicoes[posReq].codigo, arrayRequisicoes[posReq].tipoUtente, arrayRequisicoes[posReq].nomeUtente,
           arrayRequisicoes[posReq].prazo ,arrayRequisicoes[posReq].dataRequisicao.dia, arrayRequisicoes[posReq].dataRequisicao.mes, arrayRequisicoes[posReq].dataRequisicao.ano);
    if(arrayRequisicoes[posReq].estado==0)
    {
        printf("Data de devolucao: %02d/%02d/%4d\n"
               "Multa: %.2f Euros\n",
               arrayRequisicoes[posReq].dataDevolucao.dia, arrayRequisicoes[posReq].dataDevolucao.mes, arrayRequisicoes[posReq].dataDevolucao.ano, arrayRequisicoes[posReq].multa);
    }
    switch(arrayRequisicoes[posReq].estado)
    {
    case 0:
        printf("Estado: Devolvido\n");
        break;
    case 1:
        printf("Estado: Requisitado\n");
    }
}

void escolherTipoUtente(char tipo[MAX_UTENTE])
{
    printf("\nIndique o tipo de utente.\n\n"
           "1 - Estudante\n"
           "2 - Docente\n"
           "3 - Tecnico Administrativo\n");
    switch(lerInteiro("\tOpcao", 1, 3))
    {
    case 1:
        strcpy(tipo, "Estudante");
        break;
    case 2:
        strcpy(tipo, "Docente");
        break;
    case 3:
        strcpy(tipo, "Tecnico Administrativo");

    }
}
