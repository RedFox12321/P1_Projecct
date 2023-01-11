#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define MIN_ANO 2010
#define MAX_ANO 2025
#define MODIFIED_JULIAN_YEAR 2000
#define MAX_STRING 50
#define NUM_CPU 3
//constantes para funcoes_portateis
#define MAX_PORTATEIS 30
#define MAX_SERIAL_NUMBER 16
#define MIN_RAM 1
#define MAX_RAM 64
#define MAX_LOCALIZACAO 12
#define MAX_ESTADO 9
#define ESTADO_R "reparado"
#define ESTADO_A "avariado"
#define MAX_VALOR_PORTATIL 5000.00
//constantes para funcoes_requisicoes
#define MAX_NAME_CHARACTERS 80
#define MAX_CODIGO 10
#define MAX_UTENTE 23
#define NUM_UTENTES 3

typedef struct{
    int dia;
    int mes;
    int ano;
} data;

typedef struct{
    int estado; //disponivel = 0; avariado = 1; requisitado = -1
    int avaria; //temporaria = 0; permanente = 1;
} estadoPortatil;

typedef struct{
    int nIdentif; //numero de indentificacao do portatil
    char SerialNum[MAX_SERIAL_NUMBER]; // designacao do computador, como numero de serie
    int CPU; //nome do processador
    int RAM; //mem�ria total do portatil(valor entre 1GB e 64GB)
    char localizacao[MAX_LOCALIZACAO]; //localizacao onde foi adicionado
    data dataAquisicao; //data de aquisicao do portatil
    float valor; //valor do portatil
} partesPortatil;

typedef struct{
    partesPortatil dataPortatil; //data sobre o portatil
    estadoPortatil estado; //estado do portatil, como tambem o tipo de avaria;
    int numRequisicoes; //quantidade de requisicoes totais
    int numAvarias; //quantidade de avarias totais
} dadosPortatil;

typedef struct{
    partesPortatil dataPortatil; //data sobre o portatil
    estadoPortatil avaria; //estado-> ativo=1;nao ativo=0
    data dataAvaria; //data de quando aconteceu a avaria
    int diasAvariado; //Dias avariado, se temporario
} dadosAvaria;

typedef struct{
    int nIdentif; //numero de indentificacao do portatil
    char codigo[MAX_CODIGO]; //codigo da requisicao
    char nomeUtente[MAX_NAME_CHARACTERS]; //nome do utente que fez a requisicao
    char tipoUtente[MAX_UTENTE]; //tipo de utente
    data dataRequisicao; //data da requisicao
    data dataDevolucao; //data da devolucao
    int prazo; //prazo da devolucao em dias
    int estado; //concluida = 0; ativa = 1;
    float multa; //valor da multa a pagar
} dadosRequisisao;

#endif // CONSTANTES_H_INCLUDED
