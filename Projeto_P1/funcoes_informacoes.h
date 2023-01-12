#ifndef FUNCOES_INFORMACOES_H_INCLUDED
#define FUNCOES_INFORMACOES_H_INCLUDED
#include "constantes.h"

void utenteRequisitacoes(dadosRequisicao arrayRequisicoes[], int numRequisicoes);
void mostrarDevolucaoRecente(dadosRequisicao arrayRequisicoes[], int numRequisicoes);
void mediaMulta(dadosRequisicao arrayRequisicoes[], int numRequisicoes);
void mostraProcessadores(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis);
void mostrarPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], dadosAvaria arrayAvarias[], dadosRequisicao arrayRequisicoes[], int numPortateis, int numAvarias, int numRequisicoes);
void mostrarTudo(dadosPortatil arrayPortateis[MAX_PORTATEIS], dadosAvaria arrayAvarias[], dadosRequisicao arrayRequisicoes[], int numPortateis, int numAvarias, int numRequisicoes);

#endif // FUNCOES_INFORMACOES_H_INCLUDED
