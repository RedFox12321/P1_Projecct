#include "constantes.h"
#include "funcoes_auxiliares.h"

void gravarFicheiroBinario(dadosPortatil portateis[MAX_PORTATEIS], int numPortateis, int numTotalP)
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
            fwrite(&numTotalP, sizeof(int), 1, file);
            fwrite(&numPortateis, sizeof(int), 1, file);
            fwrite(portateis, sizeof(dadosPortatil), numPortateis, file);
            fclose(file);
            printf("\nDados guardados com sucesso.\n");
        }
    }
}

void gravarFicheiroBinario_Log(dadosPortatil portateis[MAX_PORTATEIS], int numPortateis, int numTotalP)
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
                       portateis[i].nIdentif, portateis[i].SerialNum, portateis[i].CPU, portateis[i].RAM,
                       portateis[i].localizacao, portateis[i].dataAquisicao.dia, portateis[i].dataAquisicao.mes, portateis[i].dataAquisicao.ano);
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
                fprintf(file, "\t%11.2f Euros\n", portateis[i].valor);
            }
            fclose(file);
            printf("\nRegisto dos dados criado com sucesso.");
        }
        gravarFicheiroBinario(portateis, numPortateis, numTotalP);
    }
}

void carregarFicheiroBinario(dadosPortatil portateis[MAX_PORTATEIS], int *numPortateis, int *numTotalP)
{
    FILE *file;

    file = fopen("infoPortateis.dat", "rb");
    if(file == NULL)
    {
        printf("\nErro ao tentar abrir ficheiro \"infoPortateis.dat\"! Nao foi possivel carregar a informacao.\n");
    }
    else
    {
        fread(numTotalP, sizeof(int), 1, file);
        fread(numPortateis, sizeof(int), 1, file);
        fread(portateis, sizeof(dadosPortatil), *numPortateis, file);
        fclose(file);
        printf("\nDados do ficheiro carregados com sucesso.\n");
    }
}
