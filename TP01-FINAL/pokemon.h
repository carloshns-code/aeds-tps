#ifndef POKEMON_H
#define POKEMON_H

#include "utils.h"
#include "coordenada.h"

typedef struct {
    int id;
    int numPokedex;
    char nome[MAX_TAM_STRING];
    char tipo[MAX_TAM_STRING];
    Coordenada localizacao;
} Pokemon;

//Inicializacao de um pokemon:
Pokemon p_init(int id, int numPokedex, char nome[], char tipo[], Coordenada localizacao);

//funcao de impressao do pokemon
void p_imprime(Pokemon *p);


/* GETTERS */
//getter do id do pokemon (fornece)
int p_get_id(Pokemon *p);
//getter do numPokedex (fornece)
int p_get_numPokedex(Pokemon *p);

//cont: impede alteracoes no endereço retornado para o escopo da estrutura
const char* p_get_nome(Pokemon *p);
const char* p_get_tipo(Pokemon *p);
Coordenada p_get_localizacao(Pokemon *p);


/* SETTERS */
void p_set_id(Pokemon *p, int id);
void p_set_numPokedex(Pokemon *p, int numPokedex);   //chama a struct Pokemon e já vem com o novo numero
void p_set_nome(Pokemon *p, char nome[]);   //já leva o novo nome
void p_set_tipo(Pokemon *p, char tipo[]);  //ja envia o novo tipo que sera adicionado
void p_set_localizacao(Pokemon *p, Coordenada l);   //a funcao recebe o poquemon e a nova coordenada


#endif