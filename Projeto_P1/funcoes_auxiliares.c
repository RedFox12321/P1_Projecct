#include "constantes.h"

//procura item ativo no arrayAvarias a partir do numero de identificacao de um portatil
int procuraAvaria(dadosAvaria arrayAvarias[], int numAvarias, int numIdentif)
{
    int i, pos;
    for(i=0;i<numAvarias;i++)
    {
        if(arrayAvarias[i].dataPortatil.nIdentif==numIdentif && arrayAvarias[i].avaria.estado==1)
        {
           pos=i;
           i=numAvarias;
        }
    }
    return pos;
}

//pede e retorna a posicao de um portatil
int pedirPosicao(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis)
{
    int pos;
    mostrarDadosPortateis(arrayPortateis, numPortateis);
    do
    {
        pos = lerInteiro("\nIndique o numero do portatil", 1, numPortateis);
        pos = procuraPortatil(arrayPortateis, numPortateis, pos);
        if(pos==-1)
        {
            printf("Nao existe portatil com esse numero de identificacao.\n");
        }
    }
    while(pos==-1);
    return pos;
}

//procura um portatil a partir do numero de identificacao
int procuraPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis, int numIdentif)
{
    int i, pos=-1;
    for(i=0;i<numPortateis;i++)
    {
        if(arrayPortateis[i].dataPortatil.nIdentif == numIdentif)
        {
           pos=i;
           i=numPortateis;
        }
    }
    return pos;
}

//transforma uma string em tudo maiuscula ou minuscula
void toUpperLower(char string[], int upper1_lower0) //upper = 1; lower = 0
{
    int i;
    if(upper1_lower0 == 1)
    {
        for(i=0;i<strlen(string);i++)
        {
                string[i] = toupper(string[i]);
        }
    }
    else
    {
        for(i=0;i<strlen(string);i++)
        {
                string[i] = toupper(string[i]);
        }
    }
}

//conta os dias entre duas datas
int contarData(data dataInicial, data dataFinal, int somaDias)
{
    int totalDias, totalDiasI, totalDiasF; //dias totais da data inicial(totalDiasI) e da data final(totalDIasF) desde a data juliana modificada em constantes.h;
                    //ano atual-ano considerado * 365 dias    // - um ano se for mes 1 ou 2 // + um ano por cada ano bissesto             // + dias * meses do ano    // + dias passados -1 (o mes começa no dia 1 não no dia 0)
    totalDiasI = dataInicial.dia + somaDias - 2483618 + 1461*( dataInicial.ano + 4800 + ( dataInicial.mes - 14 ) / 12 ) / 4 + 367*( dataInicial.mes - 2 - ( dataInicial.mes - 14 ) / 12 * 12 ) / 12 - 3*( ( dataInicial.ano + 4900 + ( dataInicial.mes - 14 ) / 12 ) / 100 ) / 4;
    totalDiasF = dataFinal.dia - 2483618 + 1461*( dataFinal.ano + 4800 + ( dataFinal.mes - 14 ) / 12 ) / 4 + 367*( dataFinal.mes - 2 - ( dataFinal.mes - 14 ) / 12 * 12 ) / 12 - 3*( ( dataFinal.ano + 4900 + ( dataFinal.mes - 14 ) / 12 ) / 100 ) / 4;
    totalDias = totalDiasF-totalDiasI;
    return totalDias;
}

//pede uma data ao utilizador e devolve uma estrutura "data"
data pedirData(char mensagem[MAX_STRING], int min_ano, int min_mes, int min_dia)
{
    int max_dias=31;
    data dataPedida;
    printf("%s\n", mensagem);
    dataPedida.ano = lerInteiro("Ano", min_ano, MAX_ANO); //pede ano
    if(dataPedida.ano == min_ano)
    {
        dataPedida.mes = lerInteiro("Mes", min_mes, 12); //pede mes com min_mes
    }
    else
    {
        dataPedida.mes = lerInteiro("Mes", 1, 12); //pede mes sem min_mes
    }
    switch(dataPedida.mes)
    {
        case 2:
            if(dataPedida.ano%400==0 || (dataPedida.ano%4==0 && dataPedida.ano%100!=0))
            {
            max_dias = 29;
            }
            else
            {
            max_dias = 28;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            max_dias = 30;
    }
    if(dataPedida.mes == min_mes && dataPedida.ano == min_ano)
    {
        dataPedida.dia = lerInteiro("Dia", min_dia, max_dias); //pede o dia consuante o mes/ano com min_dia
    }
    else
    {
        dataPedida.dia = lerInteiro("Dia", 1, max_dias); //pede o dia consuante o mes/ano sem min_dia
    }

    return dataPedida; //Retorna a estrutura data obtida
}


//pede ao utilizador um numero inteiro dentro do valor minimo e valor maximo e devolve um inteiro
int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo)
{
    int numero, controlo;
    do
    {
        printf("%s (%d a %d) :", mensagem, minimo, maximo);
        controlo = scanf ("%d", &numero);
        limpaBufferStdin();

        if (controlo == 0) // utilizador nao colocou um inteiro ou devolveu mais do que numeros
        {
            printf("Devera inserir um numero inteiro.\n");
        }
        else
        {

            if(numero<minimo || numero>maximo) // verifica se o numero se encontra dentro do intervalo defenido
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero; //Retorna o inteiro obtido
}

//pede ao utilizador um numero decimal dentro do valor minimo e valor maximo e devolve um float
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo)
{
    float numero;
    int controlo;
    do
    {
        printf("%s (%.2f a %.2f) :", mensagem, minimo, maximo);
        controlo = scanf ("%f", &numero);
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Devera inserir um numero decimal (float) \n"); // utilizador nao colocou um decimal ou devolveu mais do que numeros
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n"); // verifica se o numero se encontra dentro do intervalo defenido
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero; //Retorna o float obtido
}

//pede ao utilizador uma string dentro do maximo de caracteres e devolve uma string
void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres)
{
    int tamanhoString;

    do
    {
        printf("%s", mensagem);
        fgets(vetorCaracteres, maximoCaracteres, stdin);

        tamanhoString = strlen(vetorCaracteres);

        if (tamanhoString == 1) // utilizador só carregou no enter
        {
            printf("Nao foram introduzidos caracteres! Apenas carregou no ENTER. \n\n");
        }

    }
    while (tamanhoString == 1);

    if(vetorCaracteres[tamanhoString-1] != '\n')
    {
        limpaBufferStdin();
    }
    else
    {
        vetorCaracteres[tamanhoString-1] = '\0';
    }
    //retorna o valor obtido por argumento
}

//pede ao utilizador um caracter e devolve um caracter
char lerChar(char mensagem[MAX_STRING])
{
    char vetorCaracter[2];
    int tamanhoString;

    do
    {
        printf("%s", mensagem);
        fgets(vetorCaracter, 3, stdin);

        tamanhoString = strlen(vetorCaracter);

        if (vetorCaracter[0] == '\n') // utilizador só carregou no enter
        {
            printf("Nao foi introduzido caracter! Apenas carregou no ENTER. \n\n");
        }
        if (vetorCaracter[1] != '\n' && vetorCaracter[0] != '\n') // o utilizador deu mais do que um caracter
        {
            printf("Foi intruduzido mais do que um caracter!\n\n");
            limpaBufferStdin();
        }
    }
    while (vetorCaracter[0] == '\n' || (vetorCaracter[1] != '\n' && vetorCaracter[0] != '\n'));
    vetorCaracter[1] = '\0';
    return vetorCaracter[0]; //Retorna o caracter obtido
}

//limpa o buffer stdin
void limpaBufferStdin(void)
{
    char chr;
    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}
