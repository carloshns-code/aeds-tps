#ifndef CENTRODEPESQUISA_H
#define CENTRODEPESQUISA_H

#include "stdlib.h"
#include "time.h"
#include "../treinador/treinador.h"
#define SUCESSO 0
#define TREINADOR1 0
#define TREINADOR2 1
#define NUM_TREINADORES 2

typedef struct {
  Treinador treinadores[NUM_TREINADORES];
  Pokelista *pl_fugitivos;
  Pokelista *pl_recuperados;
  Coordenada localizacao;
} CentroDePesquisa;

void cp_init(CentroDePesquisa *cp);

void cp_insere_registros(CentroDePesquisa *cp, FILE* inputFile);

void cp_remove_fugitivo(CentroDePesquisa *cp, Pokemon p);

void cp_imprime_fugitivos(CentroDePesquisa *cp);

void cp_recebe_pokemons(CentroDePesquisa *cp, int id);

int cp_recarrega_pokebolas(CentroDePesquisa *cp, int id);

Treinador* cp_get_treinador(CentroDePesquisa *cp, int id);

Pokelista* cp_get_pl_fugitivos(CentroDePesquisa *cp);

Pokelista* cp_get_pl_recuperados(CentroDePesquisa *cp);

Coordenada cp_get_localizacao(CentroDePesquisa *cp);

void cp_set_treinador(CentroDePesquisa *cp, Treinador t, int id);

void cp_set_pl_fugitivos(CentroDePesquisa *cp, Pokelista *pl);

void cp_set_pl_recuperados(CentroDePesquisa *cp, Pokelista *pl);

void cp_set_localizacao(CentroDePesquisa *cp, Coordenada l);

#endif