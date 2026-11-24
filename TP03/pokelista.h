#ifndef POKELISTA_H
#define POKELISTA_H

#include "pokemon.h"

typedef struct {
    Pokemon *vetor; /* Endereco da memoria que contem os registros. */
    int tamanho;    /* Quantidade de posicoes efetivamente ocupadas. */
    int capacidade; /* Quantidade de posicoes alocadas. */
} Pokelista;

Pokelista pl_init(int capacidade);
void pl_insere(Pokelista *pl, Pokemon p);
void pl_imprime(const Pokelista *pl, FILE *saida);
int pl_tamanho(const Pokelista *pl);
Pokemon *pl_get_vetor(Pokelista *pl);
Pokelista pl_copia(const Pokelista *origem);
int pl_ordenada(const Pokelista *pl);
void pl_libera(Pokelista *pl);

#endif
