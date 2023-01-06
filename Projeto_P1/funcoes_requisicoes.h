#ifndef FUNCOES_PORTATEIS_H_INCLUDED
#define FUNCOES_PORTATEIS_H_INCLUDED
#include "constantes.h"

void escolherTipoUtente(char tipo[MAX_TIPOUTENTE]);
void mostrarDadosRequisicao(dadosRequisicao arrayRequisicao[MAX_PORTATEIS], int numRequisicoes);
int ProcurarRequisicaoAtiva(dadosRequisicao arrayRequisicao[MAX_PORTATEIS], int numRequisicoesAtivas, int numRequisicoes);
int RenovarRequisicao(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis);
char menuCampo();
dadosRequisicao REQUISITAR(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis);

#include "funcoes_requisicoes.c"
#endif // FUNCOES_PORTATEIS_H_INCLUDED
