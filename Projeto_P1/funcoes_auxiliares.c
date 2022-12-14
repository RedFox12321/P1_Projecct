#include <stdio.h>
#include <string.h>

#include "funcoes_auxiliares.h"

// Acrescentada variavel controlo para repetir insercao se ao for inserido numero int
int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo)
{
    int numero, controlo;
    do
    {
        printf("%s (%d a %d) :", mensagem, minimo, maximo);
        controlo = scanf ("%d", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Devera inserir um numero inteiro.\n");
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}

float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo)
{
    float numero;
    int controlo;
    do
    {
        printf("%s (%.2f a %.2f) :", mensagem, minimo, maximo);
        controlo = scanf ("%f", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Devera inserir um numero decimal (float) \n");
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}

void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres)
{
    int tamanhoString;

    do 			// Repete leitura caso sejam obtidas strings vazias
    {
        printf("%s", mensagem);
        fgets(vetorCaracteres, maximoCaracteres, stdin);

        tamanhoString = strlen(vetorCaracteres);

        if (tamanhoString == 1)
        {
            printf("Nao foram introduzidos caracteres! Apenas carregou no ENTER \n\n");  // apenas faz sentido limpar buffer se a ficarem caracteres
        }

    }
    while (tamanhoString == 1);

    if(vetorCaracteres[tamanhoString-1] != '\n')  // ficaram caracteres no buffer....
    {
        limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
    }
    else
    {
        vetorCaracteres[tamanhoString-1] = '\0'; 	//Elimina o \n da string armazenada em vetor
    }

}

char lerChar(char mensagem[MAX_STRING])
{
    char vetorCaracter[2];
    int tamanhoString;

    do 			// Repete leitura caso seja não seja obtido um caracter ou mais do que um
    {
        printf("%s", mensagem);
        fgets(vetorCaracter, 3, stdin);

        tamanhoString = strlen(vetorCaracter);

        if (vetorCaracter[0] == '\n')
        {
            printf("Nao foi introduzido o caracter! Apenas carregou no ENTER \n\n"); // utilizador só carregou no enter
        }
        if (vetorCaracter[1] != '\n' && vetorCaracter[0] != '\n')
        {
            printf("Foram intruduzidos mais do que um caracter!\n\n"); // limpa buffer
            limpaBufferStdin();
        }
    }
    while (vetorCaracter[0] == '\n' || (vetorCaracter[1] != '\n' && vetorCaracter[0] != '\n'));
    vetorCaracter[1] = '\0'; 	//Elimina o \n da string armazenada em vetor
    return vetorCaracter[0]; //Retorna o valor do caracter obtido
}

void limpaBufferStdin(void)
{
    char chr;
    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}
