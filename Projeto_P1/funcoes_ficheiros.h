#ifndef FUNCOES_FICHEIROS_H_INCLUDED
#define FUNCOES_FICHEIROS_H_INCLUDED
#include "constantes.h"

void gravarFicheiroBinario(dadosPortatil portateis[MAX_PORTATEIS], dadosAvaria avarias[], dadosRequisisao requisicoes[], int numPortateis, int numPortateisDisp, int numReq, int numReqAtivas, int numAvarias);
void gravarFicheiroBinario_Log(dadosPortatil portateis[MAX_PORTATEIS], int numPortateis, int numTotalP);
void carregarFicheiroBinario(dadosPortatil portateis[MAX_PORTATEIS], dadosAvaria *avarias, dadosRequisisao *requisicoes, dadosAvaria **enderecoAvarias, dadosRequisisao **enderecoRequisicoes, int *numPortateis, int *numPortateisDisp, int *numReq, int *numReqAtivas, int *numAvarias);

#include "funcoes_ficheiros.c"
#endif // FUNCOES_FICHEIROS_H_INCLUDED
