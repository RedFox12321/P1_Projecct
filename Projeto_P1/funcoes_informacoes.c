#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_portateis.h"
#include "funcoes_informacoes.h"

void utenteRequisitacoes(dadosRequisicao arrayRequisicoes[], int numRequisicoes)
{
    int i, utenteNum[NUM_UTENTES]={0}, min, max;
    for(i=0;i<numRequisicoes;i++)
    {
        if(strcmp(arrayRequisicoes[i].tipoUtente, "Estudante")==0)
        {
           utenteNum[0]++;
        }
        if(strcmp(arrayRequisicoes[i].tipoUtente, "Docente")==0)
        {
           utenteNum[1]++;
        }
        if(strcmp(arrayRequisicoes[i].tipoUtente, "Tecnico administrativo")==0)
        {
           utenteNum[2]++;
        }
    }
    min = utenteNum[0];
    max = utenteNum[0];
    for(i=1;i<NUM_UTENTES;i++)
    {
        if(utenteNum[i]<min)
        {
            min=utenteNum[i];
        }
        if(utenteNum[i]>max)
        {
            max=utenteNum[i];
        }
    }
    printf("\nUtente(s) com menos requisicoes: \n");
    for(i=0;i<NUM_UTENTES;i++)
    {
        if(utenteNum[i]==min)
        {
            switch(i)
            {
            case 0:
                printf("-> Estudante\n");
                break;
            case 1:
                printf("-> Docente\n");
                break;
            case 2:
                printf("-> Tecnico administrativo\n");
            }
        }
    }
    printf("\nUtente(s) com mais requisicoes: \n");
    for(i=0;i<NUM_UTENTES;i++)
    {
        if(utenteNum[i]==max)
        {
            switch(i)
            {
            case 0:
                printf("-> Estudante\n");
                break;
            case 1:
                printf("-> Docente\n");
                break;
            case 2:
                printf("-> Tecnico administrativo\n");
            }
        }
    }
    printf("\nRequisicoes por utente:\n"
           "Estudante: %d\n"
           "Docente: %d\n"
           "Tecnico administrativo: %d\n",
           utenteNum[0], utenteNum[1], utenteNum[2]);
}

void mostrarDevolucaoRecente(dadosRequisicao arrayRequisicoes[], int numRequisicoes)
{
    int pos;
    pos = procuraDevolucao(arrayRequisicoes, numRequisicoes);
    printf("\n\t___Requisicao mais recente___\n"
              "Codigo: %s\n"
              "Utente: %s\n"
              "Nome do utente: %s\n"
              "Data de requisicao: %02d/%02d/%4d\n",
               arrayRequisicoes[pos].codigo, arrayRequisicoes[pos].tipoUtente, arrayRequisicoes[pos].nomeUtente,
               arrayRequisicoes[pos].dataRequisicao.dia, arrayRequisicoes[pos].dataRequisicao.mes, arrayRequisicoes[pos].dataRequisicao.ano);
    if(arrayRequisicoes[pos].estado==0)
    {
        printf("Data de devolucao: %02d/%02d/%4d\n"
               "Multa: %.2f Euros\n",
               arrayRequisicoes[pos].dataDevolucao.dia, arrayRequisicoes[pos].dataDevolucao.mes, arrayRequisicoes[pos].dataDevolucao.ano, arrayRequisicoes[pos].multa);
    }
    switch(arrayRequisicoes[pos].estado)
    {
    case 0:
        printf("Estado: Devolvido\n");
        break;
    case 1:
        printf("Estado: Requisitado\n");
    }
}

void mostraProcessadores(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis)
{
    int i,n;
    int processNum[NUM_CPU]={0};
    float percent;
    for(n=1;n<=NUM_CPU;n++)
    {
        for(i=0;i<numPortateis;i++)
        {
            if(arrayPortateis[i].dataPortatil.CPU==1+2*n)
            {
                processNum[n-1]++;
            }
        }
    }
    printf("\nProcessador(CPU)\tQuantidade\tQuantidade(%%)\n");
    for(i=1;i<=NUM_CPU;i++)
    {
        percent = processNum[i-1]/(float)numPortateis*100;  //numPortateis nunca й zero porque a funзгo sу й chamada qunado existe pelo menos 1 portatil
        printf("    Intel i%i\t\t  %3d    \t   %3.1f %%\n", 1+2*i, processNum[i-1], percent);
    }
    printf("\n          Total: \t  %3d    \t   100.0 %%\n", numPortateis);
}

void mediaMulta(dadosRequisicao arrayRequisicoes[], int numRequisicoes)
{
    int i;
    float valor=arrayRequisicoes[0].multa,
    max = arrayRequisicoes[0].multa,
    min = arrayRequisicoes[0].multa;
    for(i=1;i<numRequisicoes;i++)
    {
        if(arrayRequisicoes[i].multa>max)
        {
            max = arrayRequisicoes[i].multa;
        }
        if(arrayRequisicoes[i].multa<min)
        {
            min = arrayRequisicoes[i].multa;
        }
        valor += arrayRequisicoes[i].multa;
    }
    if(valor != 0)
    {
        valor = valor/numRequisicoes;
    }
    printf("\nExiste(m) %d multa(s).\n"
           "A media das multas pagas e: %.2f Euros\n"
           "O valor mais alto e: %.2f Euros\n"
           "O valor mais baixo e: %.2f Euros\n",
            numRequisicoes, valor, max, min);
}

void mostrarPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], dadosAvaria arrayAvarias[], dadosRequisicao arrayRequisicoes[], int numPortateis, int numAvarias, int numRequisicoes)
{
    int i,num,pos;
    mostrarDadosPortateis(arrayPortateis, numPortateis);
    pos = pedirPosicao(arrayPortateis, numPortateis);
    printf("\n\n\t_______Dados do Portatil_______\n"
               "Numero de identificacao: %d\n"
               "Numero de serie: %s\n"
               "Processador(CPU): Intel %i\n"
               "Memoria(RAM): %d GB\n"
               "Localizacao atual: %s\n"
               "Data de aquisicao: %02d/%02d/%4d\n"
               "Valor do portatil(atualmente): %.2f Euros\n",
               arrayPortateis[pos].dataPortatil.nIdentif, arrayPortateis[pos].dataPortatil.SerialNum, arrayPortateis[pos].dataPortatil.CPU, arrayPortateis[pos].dataPortatil.RAM,
               arrayPortateis[pos].dataPortatil.localizacao, arrayPortateis[pos].dataPortatil.dataAquisicao.dia, arrayPortateis[pos].dataPortatil.dataAquisicao.mes, arrayPortateis[pos].dataPortatil.dataAquisicao.ano,
               arrayPortateis[pos].dataPortatil.valor);
    printf("\nEncontra-se avariado: ");
    if(arrayPortateis[pos].estado.estado==1)
    {
        printf("Sim\nTipo de avaria: ");
        switch(arrayPortateis[pos].estado.avaria)
        {
            case 0:
                printf("Temporaria\n");
                break;
            case 1:
                printf("Permanente\n");
        }
    }
    else
    {
        printf("Nao\n");
    }
    printf("Numero total de avarias: %d\n", arrayPortateis[pos].numAvarias);
    if(arrayPortateis[pos].numAvarias!=0)
    {
        printf("\nTodas as avarias:\n");
        num=1;
        for(i=0;i<numAvarias;i++)
        {
            if(arrayAvarias[i].dataPortatil.nIdentif==arrayPortateis[pos].dataPortatil.nIdentif)
            {
                printf("\n\t\t___Avaria n%03d___\n\tTipo de avaria: ", num);
                switch(arrayAvarias[i].avaria.avaria)
                {
                    case 0:
                        printf("temporaria\n");
                        break;
                    case 1:
                        printf("permanente\n");
                }
                num++;
                printf("\tDados do computador no comeco da avaria:\n"
                       "\tNumero de identificacao: %d\n"
                       "\tNumero de serie: %s\n"
                       "\tProcessador(CPU): Intel i%i\n"
                       "\tMemoria(RAM): %d GB\n"
                       "\tLocalizacao atual: %s\n"
                       "\tData de aquisicao: %02d/%02d/%4d\n"
                       "\tValor do portatil: %.2f Euros\n",
                       arrayAvarias[i].dataPortatil.nIdentif, arrayAvarias[i].dataPortatil.SerialNum, arrayAvarias[i].dataPortatil.CPU, arrayAvarias[i].dataPortatil.RAM,
                       arrayAvarias[i].dataPortatil.localizacao, arrayAvarias[i].dataPortatil.dataAquisicao.dia, arrayAvarias[i].dataPortatil.dataAquisicao.mes, arrayAvarias[i].dataPortatil.dataAquisicao.ano,
                       arrayAvarias[i].dataPortatil.valor);
                printf("\tA avaria comecou a %02d/%02d/%4d,", arrayAvarias[i].dataAvaria.dia, arrayAvarias[i].dataAvaria.mes, arrayAvarias[i].dataAvaria.ano);
                switch(arrayAvarias[i].avaria.estado)
                {
                    case 0:
                        printf(" ficando avariado durante %d dia(s).\n", arrayAvarias[i].diasAvariado);
                        break;
                    case 1:
                        printf(" estando ainda avariado.\n");
                }
            }
        }
    }
    printf("\nEncontra-se requisitado: ");
    if(arrayPortateis[pos].estado.estado==-1)
    {
        printf("Sim\nTipo de utente: ");
        for(i=0;i<numRequisicoes;i++)
        {
            if(arrayRequisicoes[i].nIdentif==arrayPortateis[pos].dataPortatil.nIdentif && arrayRequisicoes[i].estado==1)
            {
                printf("%s\n", arrayRequisicoes[i].tipoUtente);
                i=numRequisicoes;
            }
        }
    }
    else
    {
        printf("Nao\n");
    }
    printf("Numero total de requisicoes: %d\n", arrayPortateis[pos].numRequisicoes);
    if(arrayPortateis[pos].numRequisicoes!=0)
    {
        printf("Numero total de dias requisitado: %d\n", arrayPortateis[pos].diasTotal);
        for(i=0;i<numRequisicoes;i++)
        {
            if(arrayRequisicoes[i].nIdentif==arrayPortateis[pos].dataPortatil.nIdentif)
            {
                printf("\n\t\t___Requisicao n%03d___\n"
                              "\tCodigo: %s\n\tUtente: %s\n"
                              "\tNome do utente: %s\n"
                              "\tData de requisicao: %02d/%02d/%4d\n",
                               num, arrayRequisicoes[i].codigo, arrayRequisicoes[i].tipoUtente, arrayRequisicoes[i].nomeUtente,
                               arrayRequisicoes[i].dataRequisicao.dia, arrayRequisicoes[i].dataRequisicao.mes, arrayRequisicoes[i].dataRequisicao.ano);
                num++;
                if(arrayRequisicoes[i].estado==0)
                {
                    printf("\tData de devolucao: %02d/%02d/%4d\n"
                           "\tMulta: %.2f Euros\n",
                           arrayRequisicoes[i].dataDevolucao.dia, arrayRequisicoes[i].dataDevolucao.mes, arrayRequisicoes[i].dataDevolucao.ano, arrayRequisicoes[i].multa);
                }
                switch(arrayRequisicoes[i].estado)
                {
                case 0:
                    printf("\tEstado: Devolvido\n");
                    break;
                case 1:
                    printf("\tEstado: Requisitado\n");
                }
            }
        }
    }
}

void mostrarTudo(dadosPortatil arrayPortateis[MAX_PORTATEIS], dadosAvaria arrayAvarias[], dadosRequisicao arrayRequisicoes[], int numPortateis, int numAvarias, int numRequisicoes)
{
    int i,n,num; //i percorre arrayPortateis; n percorre arrayAvarias; num й o numero da avaria ou requisicao
    for(i=0;i<numPortateis;i++)
    {
        printf("\n\n\t_______Portatil n%d_______\n"
               "Numero de identificacao: %d\n"
               "Numero de serie: %s\n"
               "Processador(CPU): Intel i%i\n"
               "Memoria(RAM): %d GB\n"
               "Localizacao atual: %s\n"
               "Data de aquisicao: %02d/%02d/%4d\n"
               "Valor do portatil(atualmente): %.2f Euros\n",
               i+1, arrayPortateis[i].dataPortatil.nIdentif, arrayPortateis[i].dataPortatil.SerialNum, arrayPortateis[i].dataPortatil.CPU, arrayPortateis[i].dataPortatil.RAM,
               arrayPortateis[i].dataPortatil.localizacao, arrayPortateis[i].dataPortatil.dataAquisicao.dia, arrayPortateis[i].dataPortatil.dataAquisicao.mes, arrayPortateis[i].dataPortatil.dataAquisicao.ano,
               arrayPortateis[i].dataPortatil.valor);
        printf("\nEncontra-se avariado: ");
        if(arrayPortateis[i].estado.estado==1)
        {
            printf("Sim\nTipo de avaria: ");
            switch(arrayPortateis[i].estado.avaria)
            {
                case 0:
                    printf("Temporaria\n");
                    break;
                case 1:
                    printf("Permanente\n");
            }
        }
        else
        {
            printf("Nao\n");
        }
        printf("Numero total de avarias: %d\n", arrayPortateis[i].numAvarias);
        if(arrayPortateis[i].numAvarias!=0)
        {
            printf("\nTodas as avarias:\n");
            num=1;
            for(n=0;n<numAvarias;n++)
            {
                if(arrayAvarias[n].dataPortatil.nIdentif==arrayPortateis[i].dataPortatil.nIdentif)
                {
                    printf("\n\t\t___Avaria n%03d___\n\tTipo de avaria: ", num);
                    switch(arrayAvarias[n].avaria.avaria)
                    {
                        case 0:
                            printf("temporaria\n");
                            break;
                        case 1:
                            printf("permanente\n");
                    }
                    num++;
                    printf("\tDados do computador no comeco da avaria:\n"
                           "\tNumero de identificacao: %d\n"
                           "\tNumero de serie: %s\n"
                           "\tProcessador(CPU): Intel i%i\n"
                           "\tMemoria(RAM): %d GB\n"
                           "\tLocalizacao atual: %s\n"
                           "\tData de aquisicao: %02d/%02d/%4d\n"
                           "\tValor do portatil: %.2f Euros\n",
                           arrayAvarias[n].dataPortatil.nIdentif, arrayAvarias[n].dataPortatil.SerialNum, arrayAvarias[n].dataPortatil.CPU, arrayAvarias[n].dataPortatil.RAM,
                           arrayAvarias[n].dataPortatil.localizacao, arrayAvarias[n].dataPortatil.dataAquisicao.dia, arrayAvarias[n].dataPortatil.dataAquisicao.mes, arrayAvarias[n].dataPortatil.dataAquisicao.ano,
                           arrayAvarias[n].dataPortatil.valor);
                    printf("\tA avaria comecou a %02d/%02d/%4d,", arrayAvarias[n].dataAvaria.dia, arrayAvarias[n].dataAvaria.mes, arrayAvarias[n].dataAvaria.ano);
                    switch(arrayAvarias[n].avaria.estado)
                    {
                        case 0:
                            printf(" ficando avariado durante %d dia(s).\n", arrayAvarias[n].diasAvariado);
                            break;
                        case 1:
                            printf(" estando ainda avariado.\n");
                    }
                }
            }
        }
        printf("\nEncontra-se requisitado: ");
        if(arrayPortateis[i].estado.estado==-1)
        {
            printf("Sim\nTipo de utente: ");
            for(n=0;n<numRequisicoes;n++)
            {
                if(arrayRequisicoes[n].nIdentif==arrayPortateis[i].dataPortatil.nIdentif && arrayRequisicoes[n].estado==1)
                {
                    printf("%s\n", arrayRequisicoes[n].tipoUtente);
                    n=numRequisicoes;
                }
            }
        }
        else
        {
            printf("Nao\n");
        }
        printf("Numero total de requisicoes: %d\n", arrayPortateis[i].numRequisicoes);
        if(arrayPortateis[i].numRequisicoes!=0)
        {
            printf("Numero total de dias requisitado: %d\n", arrayPortateis[i].diasTotal);
            printf("\nTodas as requisicoes:\n");
            num=1;
            for(n=0;n<numRequisicoes;n++)
            {
                if(arrayRequisicoes[n].nIdentif==arrayPortateis[i].dataPortatil.nIdentif)
                {
                    printf("\n\t\t___Requisicao n%03d___\n"
                                  "\tCodigo: %s\n"
                                  "\tUtente: %s\n"
                                  "\tNome do utente: %s\n"
                                  "\tData de requisicao: %02d/%02d/%4d\n",
                                   num, arrayRequisicoes[n].codigo, arrayRequisicoes[n].tipoUtente, arrayRequisicoes[n].nomeUtente,
                                   arrayRequisicoes[n].dataRequisicao.dia, arrayRequisicoes[n].dataRequisicao.mes, arrayRequisicoes[n].dataRequisicao.ano);
                    num++;
                    if(arrayRequisicoes[n].estado==0)
                    {
                        printf("\tData de devolucao: %02d/%02d/%4d\n"
                               "\tMulta: %.2f Euros\n",
                               arrayRequisicoes[n].dataDevolucao.dia, arrayRequisicoes[n].dataDevolucao.mes, arrayRequisicoes[n].dataDevolucao.ano, arrayRequisicoes[n].multa);
                    }
                    switch(arrayRequisicoes[n].estado)
                    {
                    case 0:
                        printf("\tEstado: Devolvido\n");
                        break;
                    case 1:
                        printf("\tEstado: Requisitado\n");
                    }
                }
            }
        }
    }
}
