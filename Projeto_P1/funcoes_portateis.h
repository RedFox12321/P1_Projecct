#ifndef FUNCOES_PORTATEIS_H_INCLUDED
#define FUNCOES_PORTATEIS_H_INCLUDED
#include "constantes.h"

void adicionarPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], int *numPortateis);
void alterarDadosPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis);
void mostrarDadosPortateis(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis);
void escolherLocalizacao(char local[MAX_LOCALIZACAO]);
char menuAlterar();

#include "funcoes_portateis.c"
#endif // FUNCOES_PORTATEIS_H_INCLUDED
