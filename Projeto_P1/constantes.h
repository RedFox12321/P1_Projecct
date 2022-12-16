#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define MIN_ANO 2010
#define MAX_ANO 2025
#define MAX_STRING 50
//constantes para funcoes_portateis
#define MAX_PORTATEIS 30
#define MAX_CPU_MODEL 10
#define MAX_SERIAL_NUMBER 16
#define MIN_RAM 1
#define MAX_RAM 64
#define MAX_LOCALIZACAO 12
#define MAX_ESTADO 9
#define ESTADO_R "reparado"
#define ESTADO_A "avariado"
//constantes para funcoes_reservas
#define MAX_NAME_CHARACTERS 80
#define MAX_CODIGO 10

typedef struct{
    int dia;
    int mes;
    int ano;
} data;

typedef struct{
    int nIdentif; //numero de indentificacao do portatil
    char codigo[MAX_CODIGO]; //codigo da requisicao
    char nomeUtente[MAX_NAME_CHARACTERS]; //nome do utente que fez a requisicao
    int tipoUtente; //tipo de utente
    data dataRequisicao; //data da requisicao
    data dataDevolucao; //data da devolucao
    int estado; //concluida = 0; ativa = 1;

} dadosRequisisao;

typedef struct{
    int estado; //disponivel = 0; avariado = 1; requisitado = -1
    int avaria; //temporaria = 0; permanente = 1;
} estadoPortatil;

typedef struct{
    int nIdentif; //numero de indentificacao do portatil
    char SerialNum[MAX_SERIAL_NUMBER]; // designacao do computador, como numero de serie
    char CPU[MAX_CPU_MODEL]; //nome do processador
    int RAM; //memória total do portatil(valor entre 1GB e 64GB)
    estadoPortatil estado; //estado do portatil, como tambem o tipo de avaria;
    char localizacao[MAX_LOCALIZACAO]; //localizacao onde foi adicionado
    data dataAquisicao; //data de aquisicao do portatil
    float multa; //valor da multa a pagar
} dadosPortatil;

#endif // CONSTANTES_H_INCLUDED
