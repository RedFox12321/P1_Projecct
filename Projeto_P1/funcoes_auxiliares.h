#ifndef FUNCOES_AUXILIARES_H_INCLUDED
#define FUNCOES_AUXILIARES_H_INCLUDED
#include "constantes.h"

void limpaBufferStdin(void);
void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres);
void toUpperLower(char string[], int upper1_lower0);
void registarRequisicao_Log(dadosRequisicao arrayRequisicoes[], dadosPortatil arrayPortateis[MAX_PORTATEIS], int numRequisicoes, int numPortateis, int posReq);
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo);
int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo);
int procuraPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis, int numIdentif);
int pedirPosicao(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis);
int procuraAvaria(dadosAvaria arrayAvarias[], int numAvarias, int numIdentif);
int procuraRequisicao(dadosRequisicao arrayRequisicoes[], int numRequisicoes, int numIdentif);
int contarData(data dataInicial, data dataFinal, int somaDias);
int procuraCodigo(dadosRequisicao arrayRequisicoes[], int numRequisicoes, char codigo[MAX_CODIGO]);
int procuraDevolucao(dadosRequisicao arrayRequisicoes[], int numRequisicoes);
char lerChar(char mensagem[MAX_STRING]);
data pedirData(char mensagem[MAX_STRING], int min_ano, int min_mes, int min_dia);

#endif // FUNCOES_AUXILIARES_H_INCLUDED
