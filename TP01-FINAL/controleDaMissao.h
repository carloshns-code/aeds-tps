#ifndef CONTROLEDAMISSAO_H
#define CONTROLEDAMISSAO_H

#include "centroDePesquisa.h"

// o módulo Controle da Missão foi criado para modularizar e organizar a main,
// com essa divisão, cada etapa da execução é bem definida e de fácil entendimento,
// separando a lógica das implementações das estruturas, facilitando a manutenção do código

//inicializa as estruturas
CentroDePesquisa cm_init();

// leitura do caminho do arquivo a ser executado
void cm_input(char inputFileName[]);

// inserção dos registros a partir do arquivo de entrada
void cm_registro(CentroDePesquisa *cp, char inputFileName[]);

// fluxo de captura dos pokemons
void cm_captura(CentroDePesquisa *cp);

// retorno dos treinadores ao centro de pesquisa ao fim da missão
void cm_retorno(CentroDePesquisa *cp);

// escrita do relatório
void cm_imprime(CentroDePesquisa *cp);

// liberação da memória utilizada pelo programa
void cm_libera(CentroDePesquisa *cp);

#endif