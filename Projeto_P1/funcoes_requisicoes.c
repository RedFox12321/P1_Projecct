#include "constantes.h"
#include "funcoes_auxiliares.h"

dadosRequisicao REQUISITAR(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numPortateis)
{
    dadosRequisicao arrayRequisicao[MAX_PORTATEIS];
    int posicao;
    do
    {
        posicao = pedirPosicao(arrayPortateis,numPortateis);
        if(arrayPortateis[posicao].estado.estado==-1)
        {
            printf("\nEste portatil ja se encontra requisitado por outro utente!\n");
        }
    }
    while(arrayPortateis[posicao].estado.estado==-1);

    arrayPortateis[posicao].estado.estado = -1;
    arrayRequisicao[posicao].estado=1;
    arrayRequisicao[posicao].nIdentif=arrayPortateis[posicao].nIdentif;
    lerString("\nCodigo da Requisicao: ",arrayRequisicao[posicao].codigo,MAX_CODIGO);
    lerString("\nNome do Utente Requisitante: ",arrayRequisicao[posicao].nomeUtente,MAX_NAME_CHARACTERS);
    escolherTipoUtente(arrayRequisicao[posicao].tipoUtente);
    arrayRequisicao[posicao].dataRequisicao=pedirData("\nData do Início da Requisicao:");
    //arrayRequisicao[posicao].dataDevolucao=pedirData("\nPrazo da Requisicao:");
    arrayRequisicao[posicao].prazo=lerInteiro("Por quantos dias sera requisitado?",1,30);
    return arrayRequisicao[posicao];

}

void mostrarDadosRequisicao(dadosRequisicao arrayRequisicao[MAX_PORTATEIS], int numRequisicoes)
{
    int i;
    printf("\nCod. Requisicao\t Numero\tRequisitante\tTipo Utente\tData de Requisicao:\t\tDias Requisitados: \tEstado:\n");
    for(i=0; i<numRequisicoes; i++)
    {

        printf("\n%15s\t %5i\t%14s\t%8s\t%02d/%02d/%4d\t\t%02d dias \t", arrayRequisicao[i].codigo, arrayRequisicao[i].nIdentif, arrayRequisicao[i].nomeUtente,
               arrayRequisicao[i].tipoUtente, arrayRequisicao[i].dataRequisicao.dia,arrayRequisicao[i].dataRequisicao.mes,arrayRequisicao[i].dataRequisicao.ano,
               arrayRequisicao[i].dataDevolucao.dia, arrayRequisicao[i].prazo);
        switch(arrayRequisicao[i].estado)
        {
        case 0:
            printf("        Concluida\t\n");
            break;
        case 1:
            printf("          Ativa\t\n");
        }
    }
}

int RenovarRequisicao(dadosPortatil arrayPortateis[MAX_PORTATEIS], int numRequisicoesAtivas)
{
    int posicao, renovacao;

    posicao=ProcurarRequisicaoAtiva(arrayRequisicao,numRequisicoesAtivas);

    if(posicao>-1)
    {
        renovacao=lerInteiro("Por quanto tempo pretende renovar a requisicao?",1,7);
        return arrayRequisicao[posicao].prazo;
    }
    else
    {
        printf("\nNao foi possivel continuar a operacao.\nTente Novamente!");
    }
}

int ProcurarRequisicaoAtiva(dadosRequisicao arrayRequisicao[MAX_PORTATEIS], int numRequisicoesAtivas, int numRequisicoes)
{
    char pesquisa[MAX_CODIGO];
    int i,posicao,renovacao;

    mostrarDadosRequisicao(arrayRequisicao,numRequisicoes);

    posicao=-1;
    lerString("\nDigite o Codigo da Requisicao: ",pesquisa,MAX_CODIGO);
    for(i=0; i<numRequisicoesAtivas; i++)
    {
        if(strcmp(pesquisa,arrayRequisicao[i].codigo)==0 && arrayRequisicao[i].estado==0)
        {
            posicao=i;
            i=numRequisicoesAtivas;
        }
    }
    if(posicao==-1) //Nao encontrou nenhuma requisicao com o codigo correto e ainda ativa.
    {
        printf("\nNao existe nenhuma requisicao ativa com este codigo.\n");
    }
    return posicao;
}

void escolherTipoUtente(char tipo[MAX_TIPOUTENTE])
{
    printf("\nIndique o tipo de utente.\n\n"
           "1 - Estudante\n"
           "2 - Docente\n"
           "3 - Tecnico Administrativo\n");
    switch(lerInteiro("\tOpcao", 1, 3))
    {
    case 1:
        strcpy(tipo, "Estudante");
        break;
    case 2:
        strcpy(tipo, "Docente");
        break;
    case 3:
        strcpy(tipo, "Tecnico Administrativo");

    }
}



