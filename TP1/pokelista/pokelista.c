#include "pokelista.h"
#include <stdio.h>


/* CRIANDO A CABEÇA DA LISTA ENCADEADA */

Pokelista* pl_init(TLista *pl) {     //esse TLista contem o typecast que define o tipo de ponteiro Apontador, que aponta para a estrutura Pokelista

    pl->primeiro = (Apontador) malloc(sizeof(Pokelista)); //aloca memoria para a cabeça da lista
    pl->primeiro = pl->ultimo;  //Apontador = struct Pokelista*
    pl->primeiro->prox = NULL; //inicializa o ponteiro para a proxima celula como NULL
}

/* INSERINDO UM NOVO ELEMENTO NA LISTA */

Pokelista* pl_insere(Pokelista *pl, Pokemon p){
    Pokelista *novo;
    Pokelista *atual;

    pl->ultimo->prox = (Apontador) malloc(sizeof(Pokelista)); //aloca memoria para a nova celula da lista
    pl->ultimo = pl->ultimo->prox; //atualiza o ponteiro para a ultima celula da lista
    pl->ultimo->pokemon = *p; //atribui o pokemon a nova celula da lista
    pl->ultimo->prox = NULL; //inicializa o ponteiro para a proxima celula como NULL
    
    novo = (Pokelista*) malloc(sizeof(Pokelista)); //aloca memoria para a nova celula da lista
    if (novo == NULL) {
        printf("Erro ao alocar memoria para a nova celula da lista.\n");
        return pl;  
    }

    novo->pokemon = p; //atribui o pokemon a nova celula da lista
    novo->prox = NULL; //inicializa o ponteiro para a proxima celula como NULL

    if(pl==NULL){
        return novo; //se a lista estiver vazia, retorna a nova celula como a primeira celula da lista
    }
}