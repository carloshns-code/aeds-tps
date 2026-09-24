#ifndef POKELISTA_H
#define POKELISTA_H

#include "../pokemon/pokemon.h"

typedef struct Celula *Apontador;
typedef struct Celula
{
    Pokemon pokemon;
    struct Celula *prox;
} TCelula;

typedef struct
{
    Apontador pPrimeiro;
    Apontador pUltimo;
} Pokelista;

void pl_init(Pokelista *pl);

int pl_vazia(Pokelista *pl);

int pl_insere(Pokelista *pl, Pokemon p);

int pl_remove(Pokelista *pl, Pokemon p);

Apontador pl_busca(Pokelista *pl, Pokemon p);

void pl_imprime(Pokelista *pl);

void pl_libera(Pokelista *pl);

int pl_tamanho(Pokelista *pl);

#endif
