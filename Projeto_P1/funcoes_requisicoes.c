#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_portateis.h"
#include "funcoes_requisicoes.h"

dadosRequisisao *efetuarRequisicao(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis, dadosRequisisao arrayRequisicao[], int *numRequisicoes, int *numPD, int *numRA)
{
    int pos;
    dadosRequisisao *backup;
    backup = arrayRequisicao;
    arrayRequisicao = realloc(arrayRequisicao, (*numRequisicoes+1)*sizeof(dadosRequisisao));
    if(arrayRequisicao==NULL)
    {
        arrayRequisicao = backup;
        printf("\nErro ao reservar memoria para adicionar requisicao\n");
    }
    else
    {

        mostrarDadosPortateis(arrayPortateis, numPortateis);
        pos = pedirPosicao(arrayPortateis,numPortateis);
        switch(arrayPortateis[pos].estado.estado)
        {
        case 0:                                                            //no caso de estado "disponivel"
            do
            {
                if(arrayPortateis[pos].estado.estado==-1)
                {
                    printf("\nEste portatil ja se encontra requisitado por outro utente!\n");
                }
            }
            while(arrayPortateis[pos].estado.estado==-1);

            arrayPortateis[pos].estado.estado = -1;
            arrayRequisicao[*numRequisicoes].estado= 1;
            arrayRequisicao[*numRequisicoes].nIdentif=arrayPortateis[pos].dataPortatil.nIdentif;
            lerString("\nCodigo da Requisicao: ",arrayRequisicao[*numRequisicoes].codigo,MAX_CODIGO);
            lerString("\nNome do Utente Requisitante: ",arrayRequisicao[*numRequisicoes].nomeUtente,MAX_NAME_CHARACTERS);
            escolherTipoUtente(arrayRequisicao[*numRequisicoes].tipoUtente);
            arrayRequisicao[*numRequisicoes].dataRequisicao=pedirData("\nData do Inicio da Requisicao: ",2010,1,1);
            arrayRequisicao[*numRequisicoes].prazo=lerInteiro("Por quantos dias sera requisitado:",1,30);
            arrayRequisicao[*numRequisicoes].multa=0.0;
            arrayPortateis[pos].numRequisicoes++;
            (*numRequisicoes)++;
            (*numPD)--;
            (*numRA)++;
            printf("\nEstado trocado com sucesso.\n");
            break;
        case 1:                                                            //no caso de estado "avariado"
            printf("\nNao e possivel requisitar o portatil, pois apresenta estar avariado.\n");
            break;
        case -1:                                                            //no caso de estado "requisitado"
            printf("\nNao e possivel requisitar o portatil, pois foi requisitado anteriormente.\n");
            break;
        }
    }
    return arrayRequisicao;
}

void mostrarDadosRequisicao(dadosRequisisao arrayRequisicao[], int numRequisicoes)
{
    int i;
    printf("\nNumero   Cod. Requisicao\tRequisitante\tTipo Utente           \tQuando comecou: dia/mes/ano\tDias Requisitados\tEstado:\n");
    for(i=0; i<numRequisicoes; i++)
    {

        printf("%5i    %15s\t%12s\t%22s\t\t %02d/%02d/%4d\t%12d dias\t", arrayRequisicao[i].nIdentif, arrayRequisicao[i].codigo, arrayRequisicao[i].nomeUtente,
               arrayRequisicao[i].tipoUtente, arrayRequisicao[i].dataRequisicao.dia,arrayRequisicao[i].dataRequisicao.mes,arrayRequisicao[i].dataRequisicao.ano
               ,arrayRequisicao[i].prazo);
        switch(arrayRequisicao[i].estado)
        {
        case 0:
            printf("Concluida\n");
            break;
        case 1:
            printf("Ativa\n");
        }
    }
}

int ProcurarRequisicaoAtiva(dadosRequisisao arrayRequisicao[], int numRequisicoes)
{
    char pesquisa[MAX_CODIGO];
    int i,pos,renovacao;

    mostrarDadosRequisicao(arrayRequisicao,numRequisicoes);

    pos=-1;
    lerString("\nDigite o Codigo da Requisicao: ",pesquisa,MAX_CODIGO);

    for(i=0; i<numRequisicoes; i++)
    {
        if(strcmp(pesquisa, arrayRequisicao[i].codigo)==0 && arrayRequisicao[i].estado==1)
        {
            pos=i;
            i=numRequisicoes;
        }
    }
    return pos;


}

void RenovarRequisicao(dadosRequisisao arrayRequisicao[], int numRequisicoes)
{
    int pos,renovacao;
    do
    {
        pos=ProcurarRequisicaoAtiva(arrayRequisicao, numRequisicoes);
        if(pos==-1)
        {
            printf("\nNao existe nenhuma requisicao ativa com este codigo.\n");
        }
    }
    while(pos==-1);
    renovacao=lerInteiro("Por quanto tempo pretende renovar a requisicao?",1,7);
    arrayRequisicao[pos].prazo+=renovacao;
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
