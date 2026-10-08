#ifndef LISTADETRANSACOES_H
#define LISTADETRANSACOES_H

#include "transacaoBancaria.h"

#define MAX_TRANSACOES 100

typedef struct ListaDeTransacoes {
    TransacaoBancaria transacoes[MAX_TRANSACOES];
    int quantidadeElementos;   
} ListaTransacoes;

void inicializaLista(ListaTransacoes* lista);

int insereTransacao(ListaTransacoes* lista, TransacaoBancaria transacao);

int removeTransacao(ListaTransacoes* lista, int identificador);

void imprimeLista(ListaTransacoes* lista);

#endif