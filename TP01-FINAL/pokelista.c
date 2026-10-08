#include <stdio.h>
#include "pokelista.h"

Pokelista pl_init()
{
    Pokelista pl;

    pl.primeiro = (Pokecelula *)malloc(sizeof(Pokecelula));

    pl.ultimo = pl.primeiro;
    pl.primeiro->prox = NULL;

    return pl;
}

void pl_insere(Pokelista *pl, Pokemon p)
{
    pl->ultimo->prox = (Pokecelula *)malloc(sizeof(Pokecelula));

    pl->ultimo = pl->ultimo->prox;
    pl->ultimo->pokemon = p;
    pl->ultimo->prox = NULL;
}

void pl_remove(Pokelista *pl)
{
    if (pl_vazia)
    {
        return;
    }

    Pokecelula *aux;
    aux = pl->primeiro;
    pl->primeiro = pl->primeiro->prox;
    free(aux);
}

Pokecelula *pl_busca(Pokelista *pl, int id)
{ // ESSA FUNCAO RETORNA UM PONTEIRO QUE APONTA PARA UMA POKECELULA
    Pokecelula *aux = pl->primeiro->prox;

    while (aux != NULL)
    {
        if (aux->pokemon.id == id)
        {
            return aux;
        }

        aux = aux->prox;
    }

    return NULL;
}

void pl_imprime(Pokelista *pl, FILE *outputFile)
{
    Pokecelula *aux = pl->primeiro->prox;

    while (aux != NULL)
    {
        fprintf(outputFile, "%03d %s\n", p_get_numPokedex(&aux->pokemon), p_get_nome(&aux->pokemon));
        aux = aux->prox;
    }
}


int pl_vazia(Pokelista *pl){
    return (pl->primeiro == pl->ultimo);
}

//libera todas as celulas da lista e redefine os ponteiros para NULL
void pl_libera(Pokelista *pl){
    Pokecelula *aux = pl->primeiro;

    while (aux != NULL) {
        Pokecelula *prox = aux->prox;
        free(aux);
        aux = prox;
    }

    pl -> primeiro = NULL;
    pl -> ultimo = NULL;
}

int pl_tamanho(Pokelista *pl){
    int tam = 0;
    Pokecelula *aux = pl->primeiro->prox;
    while (aux != NULL){
        tam++;
        aux = aux->prox;
    }
    return tam;
}

//retorna o primeiro pokemon presente na lista
Pokemon pl_get_p(Pokelista *pl){
    if (!pl_vazia(pl)){                         //quando a lista esta vazia retorna 1. Aqui !1 = 0, dai nao entra no if
        return pl->primeiro->prox->pokemon;
    }
    return p_init(ZERO, ZERO, VAZIO, VAZIO, C_INIT(ORIGEM, ORIGEM));
}



