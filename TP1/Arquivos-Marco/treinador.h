#ifndef TREINADOR_H
#define TREINADOR_H

#include "../coordenada/coordenada.h"
#include "../pokelista/pokelista.h"

typedef struct {
  int id;
  char nome[MAX_TAM_STRING];
  Coordenada localizacao;
  Pokelista *pokelista;
  int numPokebolas;
} Treinador;

void t_init(Treinador *t, int id, char nome[], int numPokebolas);

void t_move(Treinador *t, Coordenada newLocalizacao);

Pokemon t_captura(Treinador *t, Pokemon p);

void t_retira_pokemon(Treinador *t, Pokemon p);

void t_imprime(Treinador *t);

int t_get_id(Treinador *t);

char* t_get_nome(Treinador *t);

Coordenada t_get_localizacao(Treinador *t);

int t_get_localizacao_x(Treinador *t);

int t_get_localizacao_y(Treinador *t);

Pokelista* t_get_pl(Treinador *t);

int t_get_numPokebolas(Treinador *t);

void t_set_id(Treinador *t, int id);

void t_set_nome(Treinador *t, char nome[]);

void t_set_localizacao(Treinador *t, Coordenada l);

void t_set_pl(Treinador *t, Pokelista *pl);

void t_set_numPokebolas(Treinador *t, int numPokebolas);

#endif