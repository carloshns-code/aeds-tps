#include <stdlib.h> /* exit. */
#include <time.h>   /* clock, clock_t, CLOCKS_PER_SEC. */
#include "centroDePesquisa.h"

CentroDePesquisa cp_init(int capacidade) {
    CentroDePesquisa cp;
    cp.pl_recuperados = pl_init(capacidade);
    return cp;
}

Pokelista *cp_get_pl_recuperados(CentroDePesquisa *cp) {
    return &cp->pl_recuperados; /* Endereco da lista, nao uma copia. */
}

void cp_insere_registros(CentroDePesquisa *cp, FILE *entrada) {
    for (int i = ZERO; i < cp->pl_recuperados.capacidade; i++) {
        int numPokedex, poder;
        char nome[MAX_TAM_STRING], tipo[MAX_TAM_STRING];
        if (fscanf(entrada, "%d %49s %49s %d", &numPokedex, nome, tipo, &poder)
            != NUM_CAMPOS || numPokedex < ZERO || poder < ZERO) {
            fprintf(stderr, "Registro %d invalido.\n", i + 1);
            exit(ERRO);
        }
        Pokemon p = p_init(numPokedex, nome, tipo, poder);
        pl_insere(cp_get_pl_recuperados(cp), p);
    }
}

CentroDePesquisa cp_copia(const CentroDePesquisa *origem) {
    CentroDePesquisa copia;
    copia.pl_recuperados = pl_copia(&origem->pl_recuperados);
    return copia; /* A copia possui seu proprio vetor. */
}

/* static: auxiliares internos deste modulo, nao expostos no .h. */
static int compara(const Pokemon *a, const Pokemon *b, Metricas *m) {
    m->comparacoes++; /* Conta inclusive comparacoes que encerram um while. */
    return p_compara(a, b);
}

static void troca(Pokemon *a, Pokemon *b, Metricas *m) {
    Pokemon aux = *a;  /* Movimento 1: salva o primeiro registro. */
    *a = *b;           /* Movimento 2: copia o segundo sobre o primeiro. */
    *b = aux;          /* Movimento 3: restaura o primeiro no segundo. */
    m->movimentacoes += MOV_TROCA; /* Inclusive quando a e b coincidem. */
}

/* SelectionSort: estrutura do slide 17 da aula 9. */
static void selectionSort(Pokemon *v, int n, Metricas *m) {
    int i, j, min;
    for (i = ZERO; i < n - 1; i++) { /* Fixa a posicao a preencher. */
        min = i;                    /* Supoe que o primeiro seja o menor. */
        for (j = i + 1; j < n; j++) { /* Examina o trecho nao ordenado. */
            if (compara(&v[j], &v[min], m) < ZERO) {
                min = j;            /* Guarda o indice do menor encontrado. */
            }
        }
        troca(&v[min], &v[i], m); /* Troca incondicional, como na aula. */
    }
}

/* QuickSort: particao com dois indices e pivo central (aula 11). */
static void particao(int esq, int dir, int *i, int *j, Pokemon *v, Metricas *m) {
    *i = esq;  /* Posicao inicial da varredura esquerda. */
    *j = dir;  /* Posicao inicial da varredura direita. */
    Pokemon pivo = v[esq + (dir - esq) / 2]; /* Copia do item central. */
    m->movimentacoes += MOV_PIVO;
    do {
        while (compara(&pivo, &v[*i], m) > ZERO) (*i)++;
        while (compara(&pivo, &v[*j], m) < ZERO) (*j)--;
        if (*i <= *j) { /* So troca se os indices ainda nao se cruzaram. */
            troca(&v[*i], &v[*j], m);
            (*i)++; /* Avanca inclusive quando as chaves sao iguais. */
            (*j)--; /* Garante progresso da particao. */
        }
    } while (*i <= *j);
}

static void ordena(int esq, int dir, Pokemon *v, Metricas *m) {
    int i, j;
    particao(esq, dir, &i, &j, v, m); /* Recebe os limites resultantes. */
    if (esq < j) ordena(esq, j, v, m); /* Ordena a parte esquerda. */
    if (i < dir) ordena(i, dir, v, m); /* Ordena a parte direita. */
}

Metricas cp_selectionSort(CentroDePesquisa *cp) {
    Metricas m = {0}; /* Reinicia os contadores e o tempo. */
    Pokelista *pl = cp_get_pl_recuperados(cp);
    Pokemon *v = pl_get_vetor(pl);
    int n = pl_tamanho(pl);
    clock_t inicio = clock(); /* Cronometra apenas a ordenacao. */
    selectionSort(v, n, &m);
    clock_t fim = clock();
    m.tempoSegundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    return m;
}

Metricas cp_quickSort(CentroDePesquisa *cp) {
    Metricas m = {0};
    Pokelista *pl = cp_get_pl_recuperados(cp);
    Pokemon *v = pl_get_vetor(pl);
    int n = pl_tamanho(pl);
    clock_t inicio = clock();
    if (n > 1) ordena(ZERO, n - 1, v, &m); /* Nao particiona lista vazia/unitaria. */
    clock_t fim = clock();
    m.tempoSegundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    return m;
}

void cp_libera(CentroDePesquisa *cp) {
    pl_libera(cp_get_pl_recuperados(cp));
}
