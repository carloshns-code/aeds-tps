#include <stdio.h>
#include <string.h>

#include "treinador.h"

// inicializa treinador
Treinador t_init(int id, char nome[], int numPokebolas)
{
    Treinador t;
    t_set_id(&t, id);
    t_set_nome(&t, nome);
    t_set_localizacao(&t, c_init(ORIGEM, ORIGEM));
    t_set_pl(&t, pl_init());
    t_set_numPokebolas(&t, numPokebolas);
}

// move treinador para uma localizacao
void t_move(Treinador *t, Coordenada newLocalizacao)
{
    t_set_localizacao(t, newLocalizacao);
}

// captura o pokemon e remove uma pokebola
void t_captura(Treinador *t, Pokemon p)
{
    pl_insere(t_get_pl(t), p); // pega a pokelista do treinado e o pokemon q sera inserido nela

    // remove uma pokebola do treinador
    t_set_numPokebolas(t, t_get_numPokebolas(t) - 1);
}

// remove o primeiro pokemon da pokelista do treinador
void t_retira_pokemon(Treinador *t)
{
    pl_remove(t_get_pl(t)); // remove o primeiro pokemon de uma lista: da lista do treinador
}

// imprime as informações do treinador
void t_imprime(Treinador *t)
{
    printf("Treinador(a) %s: posicao (%.1f, %.1f) | Pokebolas: %d\n",
           t_get_nome(t),
           c_get_localizacao_x(t_get_localizacao(t)),
           c_get_localizacao_y(t_get_localizacao(t)),
           t_get_numPokebolas(t));
}

int t_get_id(Treinador *t)
{
    return t->id;
}

const char *t_get_nome(Treinador *t)
{
    return t->nome;
}

Coordenada t_get_localizacao(Treinador *t)
{
    return t->localizacao;
}

Pokelista *t_get_pl(Treinador *t)
{
    return &t->pokelista;
}

int t_get_numPokebolas(Treinador *t)
{
    return t->numPokebolas;
}

void t_set_id(Treinador *t, int id)
{
    t->id = id;
}

void t_set_nome(Treinador *t, char nome[])
{
    strcpy(t->nome, nome);
}

void t_set_localizacao(Treinador *t, Coordenada l)
{
    t->localizacao = l;
}

void t_set_pl(Treinador *t, Pokelista pl)
{
    t->pokelista = pl;
}

void t_set_numPokebolas(Treinador *t, int numPokebolas)
{
    t->numPokebolas = numPokebolas;
}
