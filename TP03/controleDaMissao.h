#ifndef CONTROLEDAMISSAO_H
#define CONTROLEDAMISSAO_H

#include "centroDePesquisa.h"

CentroDePesquisa cm_registro(const char *caminho);
void cm_imprime(const char *algoritmo, Metricas m, int n);
void cm_salva(CentroDePesquisa *cp, const char *caminho);
void cm_libera(CentroDePesquisa *cp);

#endif
