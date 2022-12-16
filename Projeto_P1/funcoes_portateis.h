#ifndef FUNCOES_PORTATEIS_H_INCLUDED
#define FUNCOES_PORTATEIS_H_INCLUDED
#include "constantes.h"

void adicionarPortatil(dadosPortatil arrayPortateis[MAX_PORTATEIS], int *numPortateis, int *numTPE);
void escolherLocalizacao(char local[MAX_LOCALIZACAO]);
void mostrarDadosPortateis(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis);

#endif // FUNCOES_PORTATEIS_H_INCLUDED
