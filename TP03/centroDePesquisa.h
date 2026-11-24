#ifndef CENTRODEPESQUISA_H
#define CENTRODEPESQUISA_H

#include "pokelista.h"

typedef struct {
    unsigned long long comparacoes;  /* Numero de consultas a chave composta. */
    unsigned long long movimentacoes; /* Copias de registros no algoritmo. */
    double tempoSegundos;             /* Tempo de CPU em segundos. */
} Metricas;

typedef struct {
    Pokelista pl_recuperados; /* Lista vetorial dos Pokemon recuperados. */
} CentroDePesquisa;

CentroDePesquisa cp_init(int capacidade);
Pokelista *cp_get_pl_recuperados(CentroDePesquisa *cp);
void cp_insere_registros(CentroDePesquisa *cp, FILE *entrada);
CentroDePesquisa cp_copia(const CentroDePesquisa *origem);
Metricas cp_selectionSort(CentroDePesquisa *cp);
Metricas cp_quickSort(CentroDePesquisa *cp);
void cp_libera(CentroDePesquisa *cp);

#endif
