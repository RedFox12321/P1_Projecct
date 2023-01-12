#ifndef FUNCOES_REQUISICOES_H_INCLUDED
#define FUNCOES_REQUISICOES_H_INCLUDED
#include "constantes.h"

void escolherTipoUtente(char tipo[MAX_UTENTE]);
void mostrarDadosRequisicao(dadosRequisicao arrayRequisicao[], int numRequisicoes);
void renovarRequisicao(dadosRequisicao arrayRequisicao[], int numRequisicoes);
void efetuarDevolucao(dadosRequisicao arrayRequisicoes[], dadosPortatil arrayPortateis[MAX_PORTATEIS], int numRequisicoes, int numPortateis);
int procurarRequisicaoAtiva(dadosRequisicao arrayRequisicoes[], int numRequisicoes);
int pesquisarRequisicao(dadosRequisicao arrayRequisicoes[], dadosPortatil arrayPortateis[MAX_PORTATEIS], int numRequisicoes, int numPortateis);
dadosRequisicao *efetuarRequisicao(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis, dadosRequisicao arrayRequisicao[], int *numRequisicoes, int *numPD, int *numRA);

#endif // FUNCOES_REQUISICOES_H_INCLUDED
