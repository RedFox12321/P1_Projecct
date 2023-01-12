#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_portateis.h"
#include "funcoes_requisicoes.h"
#include "funcoes_avarias.h"

dadosAvaria *trocarAvaria(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis, dadosAvaria arrayAvaria[], dadosRequisicao arrayRequisicoes[], int numRequisicoes, int *numAvarias, int *numPD)
{
    int pos, posReq, escolhaInt;
    char escolha;
    dadosAvaria *backup;
    backup = arrayAvaria;
    arrayAvaria = realloc(arrayAvaria, (*numAvarias+1)*sizeof(dadosAvaria));
    if(arrayAvaria==NULL)
    {
        arrayAvaria = backup;
        printf("\nErro ao reservar memoria para registar avaria/reparo\n");
    }
    else
    {
        printf("\nEscolha um portatil para registar a avaria/reparo.");
        if(*numAvarias!=0)
        {
            mostrarAvarias(arrayPortateis, arrayAvaria, *numAvarias, numPortateis);
        }
        mostrarDadosPortateis(arrayPortateis, numPortateis);
        pos = pedirPosicao(arrayPortateis, numPortateis);
        switch(arrayPortateis[pos].estado.estado)
        {
            case 0:                                                             //no caso de estado "disponivel"
                printf("\nO portatil nao apresenta ter avaria.\n"
                       "Pretende registar o estado deste portatil como avariado?\n");
                do
                {
                    escolha = lerChar("\n\tOpcao (S - Sim | N - Nao): ");
                    tolower(escolha);
                    if(escolha!='s' && escolha!='n')
                    {
                        printf("\nOpcao nao existe.\n");
                    }
                }
                while(escolha!='s' && escolha!='n');
                if(escolha=='s')
                {
                    arrayAvaria[*numAvarias].dataPortatil = arrayPortateis[pos].dataPortatil;
                    printf("\nQue tipo de avaria tem o portatil:\n"
                           "1 - Temporaria\n"
                           "2 - Permanente (Nao sera possivel registar o reparo da avaria)\n");
                    escolhaInt = lerInteiro("\tOpcao", 1, 2);
                    arrayAvaria[*numAvarias].dataAvaria = pedirData("\nIndique quando comecou a avaria.", arrayPortateis[pos].dataPortatil.dataAquisicao.ano, arrayPortateis[pos].dataPortatil.dataAquisicao.mes, arrayPortateis[pos].dataPortatil.dataAquisicao.dia);

                    arrayPortateis[pos].estado.estado = 1;
                    arrayPortateis[pos].estado.avaria = escolhaInt-1;
                    arrayAvaria[*numAvarias].avaria.estado = 1;
                    arrayAvaria[*numAvarias].avaria.avaria = escolhaInt-1;
                    arrayAvaria[*numAvarias].diasAvariado=0;
                    arrayPortateis[pos].numAvarias++;
                    (*numAvarias)++;
                    (*numPD)--;
                    printf("\nEstado registado com sucesso.\n");
                }
                break;
            case 1:                                                             //no caso de estado "avariado"
                if(arrayPortateis[pos].estado.avaria==0)                        //temporario
                {
                    data dataAcabaAvaria;
                    printf("\nO portatil ja apresenta ter avaria.\n"
                           "Pretende mudar o estado deste portatil para disponivel?\n");
                    do
                    {
                        escolha = lerChar("\n\tOpcao (S - Sim | N - Nao): ");
                        tolower(escolha);
                        if(escolha!='s' && escolha!='n')
                        {
                            printf("\nOpcao nao existe.\n");
                        }
                    }
                    while(escolha!='s' && escolha!='n');
                    if(escolha=='s')
                    {
                        arrayPortateis[pos].estado.estado = 0;
                        pos = procuraAvaria(arrayAvaria, *numAvarias, pos+1);
                        dataAcabaAvaria = pedirData("\nIndique quando acabou a reparacao do portatil.", arrayAvaria[pos].dataAvaria.ano, arrayAvaria[pos].dataAvaria.mes, arrayAvaria[pos].dataAvaria.dia);
                        arrayAvaria[pos].diasAvariado = contarData(arrayAvaria[pos].dataAvaria, dataAcabaAvaria, 0);
                        arrayAvaria[pos].avaria.estado = 0;
                        (*numPD)++;
                        printf("\nEstado registado com sucesso.\n");
                    }
                }
                else                                                            //permanente
                {
                    printf("\nNao da para registar a reparacao deste portatil, pois tem uma avaria permanente.\n");
                }
                break;
            case -1:                                                            //no caso de estado "requisitado"
                printf("\nO portatil apresenta estar requisitado.\n"
                       "Pretende registar o estado deste portatil como avariado?\n");
                do
                {
                    escolha = lerChar("\n\tOpcao (S - Sim | N - Nao): ");
                    tolower(escolha);
                    if(escolha!='s' && escolha!='n')
                    {
                        printf("\nOpcao nao existe.\n");
                    }
                }
                while(escolha!='s' && escolha!='n');
                if(escolha=='s')
                {
                    arrayAvaria[*numAvarias].dataPortatil = arrayPortateis[pos].dataPortatil;
                    printf("\nQue tipo de avaria tem o portatil:\n"
                           "1 - Temporaria\n"
                           "2 - Permanente (Nao sera possivel registar o reparo da avaria)\n");
                    escolhaInt = lerInteiro("\tOpcao", 1, 2);
                    posReq = procuraRequisicao(arrayRequisicoes, numRequisicoes, arrayRequisicoes[posReq].nIdentif);

                    arrayAvaria[*numAvarias].dataAvaria=arrayRequisicoes[posReq].dataRequisicao;
                    printf("\nIndique quando foi devolvido o portatil com a avaria.");
                    registarRequisicao_Log(arrayRequisicoes, arrayPortateis, numRequisicoes, numPortateis, posReq);

                    arrayPortateis[pos].estado.estado = 1;
                    arrayPortateis[pos].estado.avaria = escolhaInt-1;
                    arrayAvaria[*numAvarias].avaria.estado = 1;
                    arrayAvaria[*numAvarias].avaria.avaria = escolhaInt-1;
                    arrayAvaria[*numAvarias].diasAvariado=0;
                    arrayPortateis[pos].numAvarias++;
                    (*numAvarias)++;
                    printf("\nEstado registado com sucesso.\n");
                }
        }
    }
    return arrayAvaria;
}

void mostrarAvarias(dadosPortatil arrayPortateis[MAX_PORTATEIS], dadosAvaria arrayAvarias[], int numAvarias, int numPortateis)
{
    int i,n;
    printf("\nNumero   Numero de serie\tProcessador(CPU)\tMemoria(RAM)\tTipo de avaria\t\t Estado \tQuando comecou: dia/mes/ano\tDias avariado\n");
    for(i=0;i<numPortateis;i++)
    {
        for(n=0;n<numAvarias;n++)
        {
            if(arrayAvarias[n].dataPortatil.nIdentif==arrayPortateis[i].dataPortatil.nIdentif)
            {
                printf("%5d    %15s\t    Intel i%i\t\t%8d GB\t",
                       arrayAvarias[n].dataPortatil.nIdentif, arrayAvarias[n].dataPortatil.SerialNum, arrayAvarias[n].dataPortatil.CPU, arrayAvarias[n].dataPortatil.RAM);
                switch(arrayAvarias[n].avaria.avaria)
                {
                case 0:
                    printf("    temporaria\t");
                    break;
                case 1:
                    printf("    permanente\t");
                }
                switch(arrayAvarias[n].avaria.estado)
                {
                    case 0:
                        printf("\tReparado\t");
                        break;
                    case 1:
                        printf("\tAvariado\t");
                }
                printf("\t\t %02d/%02d/%4d\t%10d\n", arrayAvarias[n].dataAvaria.dia, arrayAvarias[n].dataAvaria.mes, arrayAvarias[n].dataAvaria.ano, arrayAvarias[n].diasAvariado);
            }
        }
    }
}
