#include <string.h> /* strcmp. */
#include "controleDaMissao.h"

int main(int argc, char *argv[]) {
    if (argc != NUM_ARGUMENTOS) { /* Exige entrada e dois caminhos de saida. */
        fprintf(stderr, "Uso: %s entrada.txt saida_selection.txt saida_quick.txt\n", argv[0]);
        return ERRO;
    }
    if (strcmp(argv[1], argv[2]) == ZERO || strcmp(argv[1], argv[3]) == ZERO ||
        strcmp(argv[2], argv[3]) == ZERO) {
        fprintf(stderr, "Use tres caminhos distintos.\n");
        return ERRO;
    }
    CentroDePesquisa selection = cm_registro(argv[1]); /* Le a entrada uma vez. */
    CentroDePesquisa quick = cp_copia(&selection); /* Copia ANTES de ordenar. */
    int n = pl_tamanho(cp_get_pl_recuperados(&selection));

    Metricas ms = cp_selectionSort(&selection); /* Ordena o primeiro vetor. */
    Metricas mq = cp_quickSort(&quick);          /* Ordena o segundo vetor. */

    if (!pl_ordenada(cp_get_pl_recuperados(&selection)) ||
        !pl_ordenada(cp_get_pl_recuperados(&quick))) { /* Fora do cronometro. */
        fprintf(stderr, "Falha na ordenacao.\n");
        cm_libera(&selection);
        cm_libera(&quick);
        return ERRO;
    }
    cm_imprime("SelectionSort", ms, n);
    cm_imprime("QuickSort", mq, n);
    cm_salva(&selection, argv[2]); /* Arquivos separados permitem conferir ambos. */
    cm_salva(&quick, argv[3]);
    printf("\nOrdenacao verificada. Saidas: %s e %s\n", argv[2], argv[3]);
    cm_libera(&selection); /* Cada centro libera apenas o seu vetor. */
    cm_libera(&quick);
    return SUCESSO;
}
