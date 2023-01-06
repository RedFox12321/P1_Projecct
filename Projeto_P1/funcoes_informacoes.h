#ifndef FUNCOES_INFORMACOES_H_INCLUDED
#define FUNCOES_INFORMACOES_H_INCLUDED
#include "constantes.h"

void mediaMulta(dadosRequisisao arrayRequisicoes[], int numRequisicoes);
void mostraProcessadores(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis);
void mostrarPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], dadosAvaria arrayAvarias[], dadosRequisisao arrayRequisicoes[], int numPortateis, int numAvarias, int numRequisicoes);
void mostrarTudo(dadosPortatil arrayPortateis[MAX_PORTATEIS], dadosAvaria arrayAvarias[], dadosRequisisao arrayRequisicoes[], int numPortateis, int numAvarias, int numRequisicoes);

#include "funcoes_informacoes.c"
#endif // FUNCOES_INFORMACOES_H_INCLUDED
