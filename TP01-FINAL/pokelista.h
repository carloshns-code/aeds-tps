#include <stdio.h>
#include <stdlib.h>

#ifndef POKELISTA_H
#define POKELISTA_H

#include "pokemon.h"

typedef struct Pokecelula
{
    Pokemon pokemon;
    struct Pokecelula *prox;
} Pokecelula;

typedef struct
{
    Pokecelula *primeiro;
    Pokecelula *ultimo;
} Pokelista;

// inicializa a lista com a celula cabeca
Pokelista pl_init();

// insere um novo elemento ao final
void pl_insere(Pokelista *pl, Pokemon p);

// remove o primeiro elemento da lista
void pl_remove(Pokelista *pl);

// faz a busca linear do pokemon
Pokecelula *pl_busca(Pokelista *pl, int id);

// imprime a lista de pokemons da lista desejada
void pl_imprime(Pokelista *pl, FILE *outputFile);

// retorna 1 quando a lista esta vazia e 0 quando possui 1 ou mais elementos
int pl_vazia(Pokelista *pl);

// libera a memoria alocada durante a insercao dos pokemons
void pl_libera(Pokelista *pl);

// retorna o tamanho da lista encadeada
int pl_tamanho(Pokelista *pl);

// retorna o primeiro elemento da lista (ignora a celula cabeca)
Pokemon pl_get_p(Pokelista *pl);

#endif
