#include <stdlib.h> /* malloc, free, exit. */
#include "pokelista.h"

Pokelista pl_init(int capacidade) {
    Pokelista pl;          /* Estrutura que administra o vetor. */
    pl.vetor = NULL;       /* Nao ha memoria alocada inicialmente. */
    pl.tamanho = ZERO;    /* Nenhum registro foi inserido. */
    pl.capacidade = capacidade;
    if (capacidade < ZERO || (size_t)capacidade > (size_t)-1 / sizeof(Pokemon)) {
        fprintf(stderr, "Capacidade invalida.\n");
        exit(ERRO);
    }
    if (capacidade > ZERO) {
        pl.vetor = malloc((size_t)capacidade * sizeof(Pokemon));
        if (pl.vetor == NULL) { /* malloc pode falhar. */
            fprintf(stderr, "Memoria insuficiente.\n");
            exit(ERRO);
        }
    }
    return pl; /* Transfere a administracao do vetor ao chamador. */
}

void pl_insere(Pokelista *pl, Pokemon p) {
    if (pl->tamanho >= pl->capacidade) { /* Evita escrita fora do vetor. */
        fprintf(stderr, "PokeLista cheia.\n");
        exit(ERRO);
    }
    pl->vetor[pl->tamanho] = p; /* Copia o Pokemon inteiro na posicao livre. */
    pl->tamanho++;             /* A proxima posicao passa a estar livre. */
}

int pl_tamanho(const Pokelista *pl) { return pl->tamanho; }
Pokemon *pl_get_vetor(Pokelista *pl) { return pl->vetor; }

void pl_imprime(const Pokelista *pl, FILE *saida) {
    fprintf(saida, "%d\n", pl->tamanho); /* Cabecalho reutilizavel como entrada. */
    for (int i = ZERO; i < pl->tamanho; i++) {
        p_imprime(&pl->vetor[i], saida); /* Imprime um registro completo. */
    }
}

Pokelista pl_copia(const Pokelista *origem) {
    Pokelista copia = pl_init(origem->tamanho); /* Novo vetor independente. */
    for (int i = ZERO; i < origem->tamanho; i++) {
        pl_insere(&copia, origem->vetor[i]); /* Copia cada registro por valor. */
    }
    return copia;
}

int pl_ordenada(const Pokelista *pl) {
    for (int i = 1; i < pl->tamanho; i++) {
        if (p_compara(&pl->vetor[i - 1], &pl->vetor[i]) > ZERO) return ZERO;
    }
    return 1; /* Nenhum par de vizinhos esta invertido. */
}

void pl_libera(Pokelista *pl) {
    free(pl->vetor);       /* Devolve a memoria dinamica ao sistema. */
    pl->vetor = NULL;     /* Evita manter um endereco invalido. */
    pl->tamanho = ZERO;
    pl->capacidade = ZERO;
}
