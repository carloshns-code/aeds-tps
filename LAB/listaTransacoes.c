#include <stdio.h>
#include "listaTransacoes.h"


void inicializaLista(ListaTransacoes* lista) {
    lista->quantidadedeElementos = 0;
}

int inseretransacao(ListaTransacoes* lista, TransacaoBancaria transacao){
    if (lista->quantidadeElementos >= MAX_TRANSACOES){
        printf("Lista cheia\n");
        return 0;
    }
    lista->transacoes[lista->quantidadeElementos] = transacao;
    lista->quantidadeElementos++;

    return 1;
}

int removeTransacao(ListaTransacoes* lista, int identificador) {
    int i;
    int posicao = -1;

    for (i = 0; i < lista->quantidadeElementos; i++) {
        if (lista->transacoes[i].identificador == identificador){
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        return 0;
    }

    for (i = posicao; i < lista->quantidadeElementos - 1; i++){
        lista->transacoes[i] = lista->transacoes[i + 1];
    }

    lista->quantidadeElementos--;
     return 1;
}

void imprimeLista(ListaTransacoes* lista) {
    int i;

    for (i = 0; i < lista->quantidadeElementos; i++) {
        imprimirTransacao(&lista->transacoes[i]);
        printf("\n");
    }
}