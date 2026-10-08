#ifndef CENTRODEPESQUISA_H
#define CENTRODEPESQUISA_H

#include <stdio.h>   //por causa do FILE -> biblioteca padrao de entrada e saida
#include "utils.h"
#include "treinador.h"   //ja vem pokelista e coordenada juntos

typedef struct{
    Treinador treinadores[NUM_TREINADORES];
    Pokelista pl_fugitivos;
    Pokelista pl_recuperados;
    Coordenada localizacao;
} CentroDePesquisa;

//inicializacao do centro de pesquisa
CentroDePesquisa cp_init;

//inserção dos registros
void cp_insere_registros(CentroDePesquisa *cp, FILE* inputFile);

void cp_remove_fugitivos(CentroDePesquisa *cp);

void cp_imprime_fugitivos(CentroDePesquisa *cp);

void cp_recebe_pokemons(CentroDePesquisa *cp, int id);    //entrega os pokemons para a lista de recuperados e esvazia a lista do treinador desse id

int cp_recarrega_pokebolas(CentroDePesquisa *cp, int id);

void cp_init_treinador(CentroDePesquisa *cp, Treinador t, int id);

//getters
Treinador* cp_get_treinador(CentroDePesquisa *cp, int id);
Pokelista* cp_get_pl_fugitivos(CentroDePesquisa *cp);
Pokelista* cp_get_pl_recuperados(CentroDePesquisa *cp);
Coordenada cp_get_localizacao(CentroDePesquisa *cp);

//setters
void cp_set_treinador(CentroDePesquisa *cp, char nome[], int numPokebolas, int id);
void cp_set_pl_fugitivos(CentroDePesquisa *cp, Pokelista pl);
void cp_set_pl_recuperados(CentroDePesquisa *cp, Pokelista pl);
void cp_set_localizacao(CentroDePesquisa *cp, Coordenada l);

#endif