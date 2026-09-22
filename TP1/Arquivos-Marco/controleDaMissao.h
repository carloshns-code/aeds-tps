#ifndef CONTROLEDAMISSAO_H
#define CONTROLEDAMISSAO_H

#include "../centroDePesquisa/centroDePesquisa.h"

void cm_init(CentroDePesquisa *cp);

void cm_input(char inputFileName[]);

void cm_registro(CentroDePesquisa *cp, char inputFileName[]);

void cm_captura(CentroDePesquisa *cp);

void cm_retorno(CentroDePesquisa *cp);

void cm_relatorio(CentroDePesquisa *cp);

void cm_libera(CentroDePesquisa *cp);

#endif