#include <string.h>  /* strncpy. */
#include "pokemon.h"

Pokemon p_init(int numPokedex, const char nome[], const char tipo[], int poder) {
    Pokemon p = {0};              /* Cria um registro local inicializado. */
    p_set_numPokedex(&p, numPokedex);
    p_set_nome(&p, nome);         /* Copia o texto para dentro da struct. */
    p_set_tipo(&p, tipo);
    p_set_poder(&p, poder);
    return p;                     /* Devolve o registro completo por valor. */
}

int p_get_numPokedex(const Pokemon *p) { return p->numPokedex; }
const char *p_get_nome(const Pokemon *p) { return p->nome; }
const char *p_get_tipo(const Pokemon *p) { return p->tipo; }
int p_get_poder(const Pokemon *p) { return p->poder; }

void p_set_numPokedex(Pokemon *p, int numPokedex) { p->numPokedex = numPokedex; }
void p_set_poder(Pokemon *p, int poder) { p->poder = poder; }

void p_set_nome(Pokemon *p, const char nome[]) {
    strncpy(p->nome, nome, MAX_TAM_STRING - 1); /* Limita a copia. */
    p->nome[MAX_TAM_STRING - 1] = '\0';         /* Garante fim da string. */
}

void p_set_tipo(Pokemon *p, const char tipo[]) {
    strncpy(p->tipo, tipo, MAX_TAM_STRING - 1);
    p->tipo[MAX_TAM_STRING - 1] = '\0';
}

/* Uma comparacao logica entre dois registros pela chave composta. */
int p_compara(const Pokemon *a, const Pokemon *b) {
    if (p_get_poder(a) < p_get_poder(b)) return -1; /* a vem antes. */
    if (p_get_poder(a) > p_get_poder(b)) return 1;  /* a vem depois. */
    /* So chega aqui quando os poderes empatam. */
    if (p_get_numPokedex(a) < p_get_numPokedex(b)) return -1;
    if (p_get_numPokedex(a) > p_get_numPokedex(b)) return 1;
    return ZERO; /* As duas chaves sao iguais. */
}

void p_imprime(const Pokemon *p, FILE *saida) {
    /* Mesmo formato dos registros de entrada. */
    fprintf(saida, "%d %s %s %d\n", p_get_numPokedex(p),
            p_get_nome(p), p_get_tipo(p), p_get_poder(p));
}
