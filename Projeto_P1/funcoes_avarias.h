#ifndef FUNCOES_AVARIAS_H_INCLUDED
#define FUNCOES_AVARIAS_H_INCLUDED
#include "constantes.h"

dadosAvaria *trocarAvaria(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis, dadosAvaria arrayAvaria[], int *numAvarias, int *numPD);
void mostrarAvarias(dadosPortatil arrayPortateis[MAX_PORTATEIS], dadosAvaria arrayAvarias[], int numAvarias, int numPortateis);

#include "funcoes_avarias.c"
#endif // FUNCOES_AVARIAS_H_INCLUDED
