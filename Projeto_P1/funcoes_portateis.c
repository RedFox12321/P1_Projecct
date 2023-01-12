#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_portateis.h"

//funcoes principais
void adicionarPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], int *numPortateis)
{
    arrayPortateis[*numPortateis].dataPortatil.nIdentif = *numPortateis+1;
    lerString("\nIndique o numero de serie(designacao) do portatil: ", arrayPortateis[*numPortateis].dataPortatil.SerialNum, MAX_SERIAL_NUMBER);
    printf("Indique o processador(CPU) do portatil:\n");
    arrayPortateis[*numPortateis].dataPortatil.CPU = lerInteiro("1 - i3\n2 - i5\n3 - i7\nOpcao", 1, 3);
    arrayPortateis[*numPortateis].dataPortatil.CPU = 1 + 2*arrayPortateis[*numPortateis].dataPortatil.CPU;
    arrayPortateis[*numPortateis].dataPortatil.RAM = lerInteiro("Indique o tamanho da memoria do portatil(RAM) em GB", MIN_RAM, MAX_RAM);
    escolherLocalizacao(arrayPortateis[*numPortateis].dataPortatil.localizacao);
    arrayPortateis[*numPortateis].dataPortatil.dataAquisicao = pedirData("Indique a data de aquisicao deste portatil.", MIN_ANO, 1, 1);
    arrayPortateis[*numPortateis].dataPortatil.valor = lerFloat("Indique o valor do portatil", 0.0, MAX_VALOR_PORTATIL);
    arrayPortateis[*numPortateis].estado.estado = 0;
    arrayPortateis[*numPortateis].estado.avaria = 0;
    arrayPortateis[*numPortateis].numAvarias = 0;
    arrayPortateis[*numPortateis].numRequisicoes = 0;
    arrayPortateis[*numPortateis].diasTotal = 0;
    (*numPortateis)++;
}

void alterarDadosPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis)
{
    int pos;
    char campo;
    mostrarDadosPortateis(arrayPortateis, numPortateis);
    pos = pedirPosicao(arrayPortateis, numPortateis);
    switch(arrayPortateis[pos].estado.estado)
    {
    case 0:
        do
            {
                campo = menuAlterar();
                switch(campo)
                {
                case 'c':
                    lerString("\nIndique o novo numero de serie(designacao) do portatil: ", arrayPortateis[pos].dataPortatil.SerialNum, MAX_SERIAL_NUMBER);
                    break;
                case 'p':
                    printf("Indique o novo processador(CPU) do portatil:\n");
                    arrayPortateis[pos].dataPortatil.CPU = lerInteiro("1 - i3\n2 - i5\n3 - i7\nOpcao", 1, 3);
                    arrayPortateis[pos].dataPortatil.CPU = 1 + 2*arrayPortateis[pos].dataPortatil.CPU;
                    break;
                case 'r':
                    arrayPortateis[pos].dataPortatil.RAM = lerInteiro("\nIndique o tamanho da memoria do portatil(RAM) em GB", 1, 64);
                    break;
                case 'l':
                    escolherLocalizacao(arrayPortateis[pos].dataPortatil.localizacao);
                    break;
                case 'd':
                    arrayPortateis[pos].dataPortatil.dataAquisicao = pedirData("\nIndique a data de aquisicao deste portatil.", MIN_ANO, 1, 1);
                    break;
                case 'v':
                    arrayPortateis[pos].dataPortatil.valor = lerFloat("\nIndique o valor do portatil", 0.0, MAX_VALOR_PORTATIL);
                }
            }
            while(campo!='t');
            break;
        case 1:
            printf("\nNao e possivel alterar os dados de um portatil em avaria\n");
            break;
        case -1:
            printf("\nNao e possivel alterar os dados de um portatil requisitado\n");
            break;
    }
}

void mostrarDadosPortateis(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis)
{
    int i;
    printf("\nNumero   Numero de serie\tProcessador(CPU)\tMemoria(RAM)\tValor do portatil\tLocalizacao\tEstado do portatil\tData de aquisicao:\tDia/Mes/Ano\n");
    for(i=0; i<numPortateis; i++)
    {
        printf("%5i    %15s\t    Intel i%i\t\t%8i GB\t%11.2f Euros\t%11s\t",
               arrayPortateis[i].dataPortatil.nIdentif, arrayPortateis[i].dataPortatil.SerialNum, arrayPortateis[i].dataPortatil.CPU, arrayPortateis[i].dataPortatil.RAM, arrayPortateis[i].dataPortatil.valor,
               arrayPortateis[i].dataPortatil.localizacao);
        switch(arrayPortateis[i].estado.estado)
        {
        case 0:
            printf("      disponivel  \t");
            break;
        case 1:
            printf("        avariado  \t");
            break;
        case -1:
            printf("     requisitado  \t");
        }
        printf("\t\t\t %02d/%02d/%4d\n", arrayPortateis[i].dataPortatil.dataAquisicao.dia, arrayPortateis[i].dataPortatil.dataAquisicao.mes, arrayPortateis[i].dataPortatil.dataAquisicao.ano);
    }
}


//funcoes secundarias
char menuAlterar()
{
    char opcao = '\0';
    do
    {
        printf("\nIndique o dado que deseja alterar:\n"
               "\n"
               "C - Numero de Serie\n"
               "P - Processador(CPU)\n"
               "R - MEmoria(RAM)\n"
               "L - Localizacao\n"
               "D - Data de Aquisicao\n"
               "V - Valor do Portatil\n"
               "T - Terminar Alteracao\n");
        opcao = lerChar("\tOpcao -> ");
        tolower(opcao);
        if(opcao != 'c' && opcao != 'p' && opcao != 'r' && opcao != 'l' && opcao != 'd' && opcao != 'v' && opcao != 't')
        {
            printf("Nao e uma opcao valida!\n\n");
        }
    }
    while(opcao != 'c' && opcao != 'p' && opcao != 'r' && opcao != 'l' && opcao != 'd' && opcao != 'v' && opcao != 't');
    return opcao;
}

void escolherLocalizacao(char local[MAX_LOCALIZACAO])
{
    printf("Indique a localizacao deste portatil:\n"
           "1 - Residencias\n"
           "2 - Campus 1\n"
           "3 - Campus 2\n"
           "4 - Campus 5\n");
    switch(lerInteiro("\tOpcao", 1, 4))
    {
    case 1:
        strcpy(local, "Residencias");
        break;
    case 2:
        strcpy(local, "Campus 1");
        break;
    case 3:
        strcpy(local, "Campus 2");
        break;
    case 4:
        strcpy(local, "Campus 5");
    }
}
