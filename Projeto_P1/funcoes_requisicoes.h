#ifndef FUNCOES_REQUISICOES_H_INCLUDED
#define FUNCOES_REQUISICOES_H_INCLUDED
#include "constantes.h"

void escolherTipoUtente(char tipo[MAX_UTENTE]);
void mostrarDadosRequisicao(dadosRequisisao arrayRequisicao[], int numRequisicoes);
void RenovarRequisicao(dadosRequisisao arrayRequisicao[], int numRequisicoes);
int ProcurarRequisicaoAtiva(dadosRequisisao arrayRequisicao[], int numRequisicoes);
dadosRequisisao *efetuarRequisicao(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis, dadosRequisisao arrayRequisicao[], int *numRequisicoes, int *numPD, int *numRA);

#endif // FUNCOES_REQUISICOES_H_INCLUDED
