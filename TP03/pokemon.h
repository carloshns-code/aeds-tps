#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>  /* Define FILE. */
#include "utils.h"  /* Constantes compartilhadas. */

typedef struct {
    int numPokedex;             /* Chave secundaria. */
    char nome[MAX_TAM_STRING];  /* Nome do Pokemon. */
    char tipo[MAX_TAM_STRING];  /* Tipo do Pokemon. */
    int poder;                  /* Chave principal. */
} Pokemon;

/* Interface adaptada do TP2: somente os atributos do TP3. */
Pokemon p_init(int numPokedex, const char nome[], const char tipo[], int poder);
int p_get_numPokedex(const Pokemon *p);
const char *p_get_nome(const Pokemon *p);
const char *p_get_tipo(const Pokemon *p);
int p_get_poder(const Pokemon *p);
void p_set_numPokedex(Pokemon *p, int numPokedex);
void p_set_nome(Pokemon *p, const char nome[]);
void p_set_tipo(Pokemon *p, const char tipo[]);
void p_set_poder(Pokemon *p, int poder);
int p_compara(const Pokemon *a, const Pokemon *b);
void p_imprime(const Pokemon *p, FILE *saida);

#endif
