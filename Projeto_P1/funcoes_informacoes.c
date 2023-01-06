#include "constantes.h"
#include "funcoes_auxiliares.h"

void mostraProcessadores(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis)
{
    partesPortatil processadores[MAX_PORTATEIS]; //array de partesPortatil para usar nomes de processadores
    int processNum[MAX_PORTATEIS] = {0}, numTotalProcess=0, //array com a quantidade de cada processador; numero Total de processadores
    i,n;
    float percent;
    strcpy(processadores[0].CPU, arrayPortateis[0].dataPortatil.CPU);
    for(i=0;i<numPortateis;i++)
    {
        if(numTotalProcess!=0)
        {
            for(n=i;n<numPortateis;n++)
            {
                if(strcmp(arrayPortateis[n].dataPortatil.CPU, processadores[i-1].CPU)!=0)
                {
                    strcpy(processadores[i].CPU, arrayPortateis[n].dataPortatil.CPU);
                    n=numPortateis;
                }
            }
        }
        for(n=0;n<numPortateis;n++)
        {
            if(strcmp(arrayPortateis[n].dataPortatil.CPU, processadores[i].CPU)==0)
            {
                processNum[numTotalProcess]++;
            }
        }
        if(processNum[numTotalProcess]!=0)
        {
            numTotalProcess++;
        }
    }
    printf("\nProcessador(CPU)\tQuantidade\tQuantidade(%%)\n");
    for(i=0;i<numTotalProcess;i++)
    {
        percent = processNum[i]/(float)numPortateis*100;
        printf("%15s\t\t  %3d    \t   %3.1f %%\n", processadores[i].CPU, processNum[i], percent);
    }
    printf("\n          Total: \t  %3d    \t   100.0 %%\n", numPortateis);
}

void mediaMulta(dadosRequisisao arrayRequisicoes[], int numRequisicoes)
{
    int i;
    float valor=0,
    max = arrayRequisicoes[0].multa,
    min = arrayRequisicoes[0].multa;
    for(i=0;i<numRequisicoes;i++)
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
    else
    {
        valor = 0;
    }
    printf("\nExiste(m) %d multa(s).\n"
           "A media das multas pagas e: %.2f Euros\n"
           "O valor mais alto e: %.2f Euros\n"
           "O valor mais baixo e: %.2f Euros\n",
            numRequisicoes, valor, max, min);
}

void mostrarPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], dadosAvaria arrayAvarias[], dadosRequisisao arrayRequisicoes[], int numPortateis, int numAvarias, int numRequisicoes)
{
    int i,num,pos;
    pos = pedirPosicao(arrayPortateis, numPortateis);
    printf("\n\n\t_______Dados do Portatil_______\n"
               "Numero de identificacao: %d\n"
               "Numero de serie: %s\n"
               "Processador(CPU): %s\n"
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
                printf("    temporaria\n");
                break;
            case 1:
                printf("    permanente\n");
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
                       "\tProcessador(CPU): %s\n"
                       "\tMemoria(RAM): %d GB\n"
                       "\tLocalizacao atual: %s\n"
                       "\tData de aquisicao: %02d/%02d/%4d\n"
                       "\tValor do portatil(atualmente): %.2f Euros\n",
                       arrayAvarias[i].dataPortatil.nIdentif, arrayAvarias[i].dataPortatil.SerialNum, arrayAvarias[i].dataPortatil.CPU, arrayAvarias[i].dataPortatil.RAM,
                       arrayAvarias[i].dataPortatil.localizacao, arrayAvarias[i].dataPortatil.dataAquisicao.dia, arrayAvarias[i].dataPortatil.dataAquisicao.mes, arrayAvarias[i].dataPortatil.dataAquisicao.ano,
                       arrayAvarias[i].dataPortatil.valor);
                printf("\tA avaria comecou a %02d/%02d/%4, ficando avariado durante %d dia(s)\n", arrayAvarias[i].dataAvaria.dia, arrayAvarias[i].dataAvaria.mes, arrayAvarias[i].dataAvaria.ano, arrayAvarias[i].diasAvariado);
            }
        }
    }
}
void mostrarTudo(dadosPortatil arrayPortateis[MAX_PORTATEIS], dadosAvaria arrayAvarias[], dadosRequisisao arrayRequisicoes[], int numPortateis, int numAvarias, int numRequisicoes)
{
    int i,n,num; //i percorre arrayPortateis; n percorre arrayAvarias; num é o numero da avaria ou requisicao
    partesPortatil diferencas;
    for(i=0;i<numPortateis;i++)
    {
        printf("\n\n\t_______Portatil n%d_______\n"
               "Numero de identificacao: %d\n"
               "Numero de serie: %s\n"
               "Processador(CPU): %s\n"
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
                    printf("    temporaria\n");
                    break;
                case 1:
                    printf("    permanente\n");
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
                           "\tProcessador(CPU): %s\n"
                           "\tMemoria(RAM): %d GB\n"
                           "\tLocalizacao atual: %s\n"
                           "\tData de aquisicao: %02d/%02d/%4d\n"
                           "\tValor do portatil(atualmente): %.2f Euros\n",
                           arrayAvarias[n].dataPortatil.nIdentif, arrayAvarias[n].dataPortatil.SerialNum, arrayAvarias[n].dataPortatil.CPU, arrayAvarias[n].dataPortatil.RAM,
                           arrayAvarias[n].dataPortatil.localizacao, arrayAvarias[n].dataPortatil.dataAquisicao.dia, arrayAvarias[n].dataPortatil.dataAquisicao.mes, arrayAvarias[n].dataPortatil.dataAquisicao.ano,
                           arrayAvarias[n].dataPortatil.valor);
                    printf("\tA avaria comecou a %02d/%02d/%4, ficando avariado durante %d dia(s)\n", arrayAvarias[n].dataAvaria.dia, arrayAvarias[n].dataAvaria.mes, arrayAvarias[n].dataAvaria.ano, arrayAvarias[n].diasAvariado);
                }
            }
        }

        printf("\nEncontra-se requisitado: ");
        if(arrayPortateis[i].estado.estado==-1)
        {
            printf("Sim\nTipo de utente: ...\n");
        }
        else
        {
            printf("Nao\n");
        }
        printf("Numero total de requisicoes: %d\n", arrayPortateis[i].numRequisicoes);
    }
}
