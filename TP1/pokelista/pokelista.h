#ifndef POKELISTA_H
#define POKELISTA_H

#include<stdlib.h>
#include "../pokemon/pokemon.h"

typedef struct pokelista* Apontador;      //Apontador = struct Pokelista, ou seja, é um ponteiro para a estrutura pokelista, que representa uma celula da lista  
typedef struct pokelista {      //estrutura que representa uma celula da lista
    Pokemon pokemon;               //objeto do tipo Pokemon que sera armazenado na celula da lista
    struct pokelista *prox;      //esse ponteiro para a proxima celula quarda o endereco da proxima celula da lista
} Pokelista;


typedef struct {
    Apontador primeiro;           //ponteiro para a primeira celula da lista
    Apontador ultimo;              //ponteiro para a ultima celula da lista
    int tamanho;                 //quantidade de elementos na lista
} TLista;

Pokelista* pl_init();

Pokelista* pl_insere(Pokelista *pl, Pokemon p);

Pokelista* pl_remove(Pokelista *pl, Pokemon p);

Pokelista* pl_busca(Pokelista *pl, Pokemon p);

void pl_imprime(Pokelista *pl);

int pl_vazia(Pokelista *pl);

void pl_libera(Pokelista *pl);

int pl_tamanho(Pokelista *pl);

#endif
