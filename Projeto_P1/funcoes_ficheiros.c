#include "constantes.h"
#include "funcoes_auxiliares.h"

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

void carregarFicheiroBinario(dadosPortatil portateis[MAX_PORTATEIS], dadosAvaria *avarias, dadosRequisisao *requisicoes, dadosAvaria **enderecoAvarias, dadosRequisisao **enderecoRequisicoes, int *numPortateis, int *numPortateisDisp, int *numReq, int *numReqAtivas, int *numAvarias)
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
        avarias = realloc(avarias, (*numAvarias+1)*sizeof(dadosAvaria));
        if(avarias == NULL)
        {
            avarias = *enderecoAvarias;
            printf("\nErro a reservar memoria para as avarias ao carregar os dados do ficheiros.\n");
        }
        else
        {
            fread(avarias, sizeof(dadosAvaria), *numAvarias, file);
        }
        requisicoes = realloc(requisicoes, (*numReq+1)*sizeof(dadosRequisisao));
        if(requisicoes == NULL)
        {
            requisicoes = *enderecoRequisicoes;
            printf("\nErro a reservar memoria para as requisicoes ao carregar os dados do ficheiros.\n");
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


void gravarFicheiroBinario_Log(dadosPortatil portateis[MAX_PORTATEIS], int numPortateis, int numPortateisDisp)
{
    int i;
    if(numPortateis==0)
    {
        printf("\nNao existem dados para guardar/criar registo.\n");
    }
    else
    {
        FILE *file;

        file = fopen("Data_Log.txt", "w");
        if(file == NULL)
        {
            printf("\nErro ao tentar abrir ficheiro \"Data_Log\"! Nao foi possivel criar um registo da informacao.\n");
        }
        else
        {
            fprintf(file, "\nNumero\t\tNumero de serie\t\tProcessador(CPU)\tMemoria(RAM)\tLocalizacao\t\tData de aquisicao:\tDia/Mes/Ano \tEstado do portatil\t\tValor do portatil\n");
            for(i=0;i<numPortateis;i++)
            {
                fprintf(file, "%5i\t\t%15s\t\t %14s\t\t%8i GB\t\t%11s\t\t\t\t\t\t\t %02d/%02d/%4d \t",
                       portateis[i].dataPortatil.nIdentif, portateis[i].dataPortatil.SerialNum, portateis[i].dataPortatil.CPU, portateis[i].dataPortatil.RAM,
                       portateis[i].dataPortatil.localizacao, portateis[i].dataPortatil.dataAquisicao.dia, portateis[i].dataPortatil.dataAquisicao.mes, portateis[i].dataPortatil.dataAquisicao.ano);
                switch(portateis[i].estado.estado)
                {
                case -1:
                    fprintf(file, "       requisitado\t");
                    break;
                case 0:
                    fprintf(file, "        disponivel\t");
                    break;
                case 1:
                    fprintf(file, "          avariado\t");
                }
                fprintf(file, "\t%11.2f Euros\n", portateis[i].dataPortatil.valor);
            }
            fclose(file);
            printf("\nRegisto dos dados criado com sucesso.");
        }
    }
}
