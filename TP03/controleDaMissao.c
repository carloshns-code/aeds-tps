#include <stdlib.h>
#include "controleDaMissao.h"

CentroDePesquisa cm_registro(const char *caminho) {
    FILE *entrada = fopen(caminho, "r"); /* Abre o arquivo para leitura. */
    int n;
    if (entrada == NULL) {
        fprintf(stderr, "Nao foi possivel abrir %s.\n", caminho);
        exit(ERRO);
    }
    if (fscanf(entrada, "%d", &n) != 1 || n < ZERO) {
        fprintf(stderr, "Quantidade de Pokemon invalida.\n");
        fclose(entrada);
        exit(ERRO);
    }
    CentroDePesquisa cp = cp_init(n); /* Aloca exatamente n registros. */
    cp_insere_registros(&cp, entrada); /* Le os n Pokemon. */
    fclose(entrada);                 /* Fecha o arquivo antes de ordenar. */
    return cp;
}

void cm_imprime(const char *algoritmo, Metricas m, int n) {
    printf("\n=== %s ===\n", algoritmo);
    printf("Quantidade: %d\n", n);
    printf("Comparacoes: %llu\n", m.comparacoes);
    printf("Movimentacoes: %llu\n", m.movimentacoes);
    printf("Tempo de CPU: %.5f segundos\n", m.tempoSegundos);
}

void cm_salva(CentroDePesquisa *cp, const char *caminho) {
    FILE *saida = fopen(caminho, "w"); /* Cria ou sobrescreve o arquivo. */
    if (saida == NULL) {
        fprintf(stderr, "Nao foi possivel criar %s.\n", caminho);
        exit(ERRO);
    }
    pl_imprime(cp_get_pl_recuperados(cp), saida);
    if (fclose(saida) != ZERO) { /* Verifica erro ao finalizar a gravacao. */
        fprintf(stderr, "Erro ao gravar %s.\n", caminho);
        exit(ERRO);
    }
}

void cm_libera(CentroDePesquisa *cp) { cp_libera(cp); }
