#include <stdio.h>
#include <string.h>
#include "pokemon.h"


Pokemon p_init(int id, int numPokedex, char nome[], char tipo[], Coordenada localizacao){
    /*
    Pokemon p;  //p é um objeto
    p.id = id;
    p.numPokedex = numPokedex;
    strncpy(p.nome, nome, MAX_TAM_STRING - 1);
    p.nome[MAX_TAM_STRING - 1] = '\0';
    strncpy(p.tipo, tipo, MAX_TAM_STRING - 1);
    p.tipo[MAX_TAM_STRING - 1] = '\0';
    
    ou:

    Pokemon pokemon;
    Pokemon *p = &pokemon;    //p é um ponteiro
    p->id = id;
    p->numPokedex = numPokedex;
    strncpy(p->nome, nome, MAX_TAM_STRING - 1);
    p->nome[MAX_TAM_STRING - 1] = '\0';
    strncpy(p->tipo, tipo, MAX_TAM_STRING - 1);
    p->tipo[MAX_TAM_STRING - 1] = '\0';
    
    */
    Pokemon p;
    p_set_id(&p, id);
    p_set_numPokedex(&p, numPokedex);
    p_set_nome(&p, nome);
    p_set_tipo(&p, tipo);
    p_set_localizacao(&p, localizacao);

    //retorna o pokemon criado
    return p;
}

void p_imprime(Pokemon *p){
    printf("%d %s\n", p_get_numPokedex(&p), p_get_nome(&p))
}

/*GETTERS - FORNECE*/

int p_get_id(Pokemon *p){
    return p->id;
}

int p_get_numPokedex(Pokemon *p){
    return p->numPokedex;
}

const char* p_get_nome(Pokemon *p){
    return p->nome;
}

const char* p_get_tipo(Pokemon *p){
    return p->tipo;
}

Coordenada p_get_localizacao(Pokemon *p){
    return p->localizacao;
}

float p_get_localizacao_x(Pokemon *p){
    return p->localizacao.x;
}

float p_get_localizacao_y(Pokemon *p){
    return p->localizacao.y;
}


/*SETTERS - ALTERA*/
void p_set_id(Pokemon *p, int id){
    p->id = id;
}

void p_set_numPokedex(Pokemon *p, int numPokedex){
    p->numPokedex=numPokedex;
}

void p_set_nome(Pokemon *p, char nome[]){
    strcpy(p->nome, nome);
}

void p_set_tipo(Pokemon *p, char tipo[]){
    strcpy(p->tipo, tipo);
}

void p_set_localizacao(Pokemon *p, Coordenada l){
    p->localizacao = l;
}