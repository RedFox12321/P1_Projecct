#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_ficheiros.h"

void gravarFicheiroBinario(dadosPortatil portateis[MAX_PORTATEIS], dadosAvaria avarias[], dadosRequisisao requisicoes[], int numPortateis, int numPortateisDisp, int numReq, int numReqAtivas, int numAvarias)
{
    if(numPortateis==0)
    {
        printf("\nNao existem dados para guardar.\n");
    }
    else
    {
        FILE *file;

        file = fopen("infoPortateis.dat", "wb");
        if(file == NULL)
        {
            printf("\nErro ao tentar abrir ficheiro \"infoPortateis.dat\"! Nao foi possivel guardar a informacao.\n");
        }
        else
        {
            fwrite(&numPortateisDisp, sizeof(int), 1, file);
            fwrite(&numPortateis, sizeof(int), 1, file);
            fwrite(&numReq, sizeof(int), 1, file);
            fwrite(&numReqAtivas, sizeof(int), 1, file);
            fwrite(&numAvarias, sizeof(int), 1, file);
            fwrite(portateis, sizeof(dadosPortatil), numPortateis, file);
            fwrite(avarias, sizeof(dadosAvaria), numAvarias, file);
            fwrite(requisicoes, sizeof(dadosRequisisao), numReq, file);
            fclose(file);
            printf("\nDados guardados com sucesso.\n");
        }
    }
}

void carregarFicheiroBinario(dadosPortatil portateis[MAX_PORTATEIS], dadosAvaria avarias[], dadosRequisisao requisicoes[], dadosAvaria **enderecoAvarias, dadosRequisisao **enderecoRequisicoes, int *numPortateis, int *numPortateisDisp, int *numReq, int *numReqAtivas, int *numAvarias)
{
    FILE *file;

    file = fopen("infoPortateis.dat", "rb");
    if(file == NULL)
    {
        printf("\nErro ao tentar abrir ficheiro \"infoPortateis.dat\"! Nao foi possivel carregar a informacao.\n");
    }
    else
    {
        fread(numPortateisDisp, sizeof(int), 1, file);
        fread(numPortateis, sizeof(int), 1, file);
        fread(numReqAtivas, sizeof(int), 1, file);
        fread(numReq, sizeof(int), 1, file);
        fread(numAvarias, sizeof(int), 1, file);
        fread(portateis, sizeof(dadosPortatil), *numPortateis, file);
        avarias = realloc(avarias, (*numAvarias)*sizeof(dadosAvaria));
        if(avarias == NULL)
        {
            avarias = *enderecoAvarias;
            printf("\nErro a reservar memoria para as avarias ao carregar os dados do ficheiros.\nOs dados carregados podem estar corrompidos.\n");
        }
        else
        {
            fread(avarias, sizeof(dadosAvaria), *numAvarias, file);
        }
        requisicoes = realloc(requisicoes, (*numReq)*sizeof(dadosRequisisao));
        if(requisicoes == NULL)
        {
            requisicoes = *enderecoRequisicoes;
            printf("\nErro a reservar memoria para as requisicoes ao carregar os dados do ficheiros.\nOs dados carregados podem estar corrompidos.\n");
        }
        else
        {
            fread(requisicoes, sizeof(dadosAvaria), *numAvarias, file);
        }
        fclose(file);
        *enderecoAvarias = avarias;
        *enderecoRequisicoes = requisicoes;
        printf("\nDados do ficheiro carregados com sucesso.\n");
    }
}


void gravarFicheiroBinario_Log(dadosPortatil portateis[MAX_PORTATEIS], dadosAvaria avarias[], dadosRequisisao requisicoes[], int numPortateis, int numPortateisDisp, int numReq, int numReqAtivas, int numAvarias)
{
    int i;
    gravarFicheiroBinario(portateis, avarias, requisicoes, numPortateis, numPortateisDisp, numReq, numReqAtivas, numAvarias);
    if(numPortateis!=0)
    {
        FILE *file;

        file = fopen("Data_Log.txt", "w");
        if(file == NULL)
        {
            printf( "\nErro ao tentar abrir ficheiro \"Data_Log\"! Nao foi possivel criar um registo da informacao.\n");
        }
        else
        {
            int i,n,num; //i percorre portateis; n percorre avarias e requisicoes; num é o numero da avaria ou requisicao
            for(i=0;i<numPortateis;i++)
            {
                fprintf(file, "\n\n\t_______Portatil n%d_______\n"
                       "Numero de identificacao: %d\n"
                       "Numero de serie: %s\n"
                       "Processador(CPU): Intel i%i\n"
                       "Memoria(RAM): %d GB\n"
                       "Localizacao atual: %s\n"
                       "Data de aquisicao: %02d/%02d/%4d\n"
                       "Valor do portatil(atualmente): %.2f Euros\n",
                       i+1, portateis[i].dataPortatil.nIdentif, portateis[i].dataPortatil.SerialNum, portateis[i].dataPortatil.CPU, portateis[i].dataPortatil.RAM,
                       portateis[i].dataPortatil.localizacao, portateis[i].dataPortatil.dataAquisicao.dia, portateis[i].dataPortatil.dataAquisicao.mes, portateis[i].dataPortatil.dataAquisicao.ano,
                       portateis[i].dataPortatil.valor);
                fprintf(file, "\nEncontra-se avariado: ");
                if(portateis[i].estado.estado==1)
                {
                    fprintf(file, "Sim\nTipo de avaria: ");
                    switch(portateis[i].estado.avaria)
                    {
                        case 0:
                            fprintf(file, "Temporaria\n");
                            break;
                        case 1:
                            fprintf(file, "Permanente\n");
                    }
                }
                else
                {
                    fprintf(file, "Nao\n");
                }
                fprintf(file, "Numero total de avarias: %d\n", portateis[i].numAvarias);
                if(portateis[i].numAvarias!=0)
                {
                    fprintf(file, "\nTodas as avarias:\n");
                    num=1;
                    for(n=0;n<numAvarias;n++)
                    {
                        if(avarias[n].dataPortatil.nIdentif==portateis[i].dataPortatil.nIdentif)
                        {
                            fprintf(file, "\n\t\t___Avaria n%03d___\n\tTipo de avaria: ", num);
                            switch(avarias[n].avaria.avaria)
                            {
                                case 0:
                                    fprintf(file, "Temporaria\n");
                                    break;
                                case 1:
                                    fprintf(file, "Permanente\n");
                            }
                            num++;
                            fprintf(file, "\tDados do computador no comeco da avaria:\n"
                                   "\tNumero de identificacao: %d\n"
                                   "\tNumero de serie: %s\n"
                                   "\tProcessador(CPU): Intel i%i\n"
                                   "\tMemoria(RAM): %d GB\n"
                                   "\tLocalizacao atual: %s\n"
                                   "\tData de aquisicao: %02d/%02d/%4d\n"
                                   "\tValor do portatil: %.2f Euros\n"
                                   "\tA avaria comecou a %02d/%02d/%4d, ficando avariado durante %d dia(s)\n",
                                   avarias[n].dataPortatil.nIdentif, avarias[n].dataPortatil.SerialNum, avarias[n].dataPortatil.CPU, avarias[n].dataPortatil.RAM,
                                   avarias[n].dataPortatil.localizacao, avarias[n].dataPortatil.dataAquisicao.dia, avarias[n].dataPortatil.dataAquisicao.mes, avarias[n].dataPortatil.dataAquisicao.ano,
                                   avarias[n].dataPortatil.valor, avarias[n].dataAvaria.dia, avarias[n].dataAvaria.mes, avarias[n].dataAvaria.ano, avarias[n].diasAvariado);
                        }
                    }

                }
                fprintf(file, "\nEncontra-se requisitado: ");
                if(portateis[i].estado.estado==-1)
                {
                    fprintf(file, "Sim\nTipo de utente: ");
                    for(n=0;n<numReq;n++)
                    {
                        if(requisicoes[n].nIdentif==portateis[i].dataPortatil.nIdentif && requisicoes[n].estado==1)
                        {
                            fprintf(file, "%s\n", requisicoes[n].tipoUtente);
                            n=numReq;
                        }
                    }
                }
                else
                {
                    fprintf(file, "Nao\n");
                }
                fprintf(file, "Numero total de requisicoes: %d\n", portateis[i].numRequisicoes);
                if(portateis[i].numRequisicoes!=0)
                {
                    fprintf(file, "\nTodas as requisicoes:\n");
                    num=1;
                    for(n=0;n<numReq;n++)
                    {
                        if(requisicoes[n].nIdentif==portateis[i].dataPortatil.nIdentif)
                        {
                            fprintf(file, "\n\t\t___Requisicao n%03d___\n"
                                          "\tCodigo: %s\n"
                                          "\tUtente: %s\n"
                                          "\tNome do utente: %s\n"
                                          "\tData de requisicao: %02d/%02d/%4d\n",
                                           num , requisicoes[n].codigo, requisicoes[n].tipoUtente, requisicoes[n].nomeUtente,
                                           requisicoes[n].dataRequisicao.dia, requisicoes[n].dataRequisicao.mes, requisicoes[n].dataRequisicao.ano);
                            if(requisicoes[n].estado==0)
                            {
                                printf("\tData de devolucao: %02d/%02d/%4d\n"
                                       "\tMulta: %.2f Euros\n",
                                       requisicoes[n].dataDevolucao.dia, requisicoes[n].dataDevolucao.mes, requisicoes[n].dataDevolucao.ano, requisicoes[n].multa);
                            }
                            switch(requisicoes[n].estado)
                            {
                            case 0:
                                fprintf(file, "\tEstado: Devolvido\n");
                                break;
                            case 1:
                                fprintf(file, "\tEstado: Requisitado\n");
                            }
                        }
                    }
                }
            }
        }
        printf("\nFicheiro log criado com sucesso\n");
    }
}
