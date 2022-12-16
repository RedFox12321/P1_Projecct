#include <stdio.h>
#include <string.h>
#include "funcoes_auxiliares.c"
#include "funcoes_portateis.h"

void adicionarPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], int *numPortateis, int *numTPE)
{
    if(*numPortateis == MAX_PORTATEIS)
    {
        printf("Chegou ao limite maximo de portatateis.\n");
    }
    else
    {
        arrayPortateis[*numPortateis].nIdentif = *numTPE+1;
        lerString("Indique o numero de serie(designacao) do portatil: ", arrayPortateis[*numPortateis].SerialNum, MAX_SERIAL_NUMBER);
        lerString("Indique o processador(CPU) do portatil: ", arrayPortateis[*numPortateis].CPU, MAX_CPU_MODEL);
        toUpperLower(arrayPortateis[*numPortateis].CPU, 1);
        arrayPortateis[*numPortateis].RAM = lerInteiro("Indique o tamanho da memoria do portatil(RAM) em GB", 1, 64);
        escolherLocalizacao(arrayPortateis[*numPortateis].localizacao);
        arrayPortateis[*numPortateis].dataAquisicao = pedirData("Indique a data de aquisicao deste portatil.");
        arrayPortateis[*numPortateis].estado.estado = 0;
        arrayPortateis[*numPortateis].estado.avaria = 0;
        arrayPortateis[*numPortateis].multa = 0.0;
        (*numPortateis)++;
        (*numTPE)++;
    }
}

void escolherLocalizacao(char local[MAX_LOCALIZACAO])
{
    printf("Indique a localizacao deste portatil.\n\n"
           "1 - Residencias\n"
           "2 - Campus1\n"
           "3 - Campus2\n"
           "4 - Campus5\n");
    switch(lerInteiro("\tOpcao", 1, 4))
    {
    case 1:
        strcpy(local, "Residencias");
        break;
    case 2:
        strcpy(local, "Campus1");
        break;
    case 3:
        strcpy(local, "Campus2");
        break;
    case 4:
        strcpy(local, "Campus5");
    }
}

void mostrarDadosPortateis(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis)
{
    int i;
    printf("\nNumero Ident.\tNumero de serie\t\tProcessador(CPU)\tMemoria(RAM)\tLocalizacao\tData de aquisicao:\tDia/Mes/Ano \tEstado do portatil\tValor da multa\n");
    for(i=0;i<numPortateis;i++)
    {
        printf("%11i\t%-15s\t\t %-14s\t\t%8i GB\t%11s\t\t\t\t %02d/%02d/%4d \t", arrayPortateis[i].nIdentif, arrayPortateis[i].SerialNum, arrayPortateis[i].CPU, arrayPortateis[i].RAM, arrayPortateis[i].localizacao, arrayPortateis[i].dataAquisicao.dia, arrayPortateis[i].dataAquisicao.mes, arrayPortateis[i].dataAquisicao.ano);
        switch(arrayPortateis[i].estado.estado)
        {
        case -1:
            printf("       requisitado\t");
            break;
        case 0:
            printf("        disponivel\t");
            break;
        case 1:
            printf("          avariado\t");
        }
        printf("%7.2f Euros\n", arrayPortateis[i].multa);
    }
    printf("\n");
}
