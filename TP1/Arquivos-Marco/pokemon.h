#ifndef POKEMON_H
#define POKEMON_H

#include <string.h>
#include <stdio.h>
#include "../coordenada/coordenada.h"
#define MAX_TAM_STRING 50

typedef struct {
  int id;
  int numPokedex;
  char nome[MAX_TAM_STRING];
  char tipo[MAX_TAM_STRING];
  Coordenada localizacao;
} Pokemon;

void p_init(Pokemon *p, int id, int numPokedex, char nome[], char tipo[], Coordenada localizacao);

void p_imprime(Pokemon *p);

int p_get_id(Pokemon *p);

int p_get_numPokedex(Pokemon *p);

char* p_get_nome(Pokemon *p);

char* p_get_tipo(Pokemon *p);

Coordenada p_get_localizacao(Pokemon *p);

int p_get_localizacao_x(Pokemon *p);

int p_get_localizacao_y(Pokemon *p);

void p_set_id(Pokemon *p, int id);

void p_set_numPokedex(Pokemon *p, int numPokedex);

void p_set_nome(Pokemon *p, char nome[]);

void p_set_tipo(Pokemon *p, char tipo[]);

void p_set_localizacao(Pokemon *p, Coordenada l);

#endif