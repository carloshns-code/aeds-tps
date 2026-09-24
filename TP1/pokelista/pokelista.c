#include "pokelista.h"
#include <stdlib.h>

void pl_init(Pokelista *pl)
{
    if (pl == NULL)
    {
        printf("Erro: ponteiro para Pokelista é NULL.\n");
        return;
    }

    pl->pPrimeiro = (Apontador)malloc(sizeof(TCelula));

    if (pl->pPrimeiro == NULL)
    {
        pl->pUltimo = NULL;
        return;
    }

    pl->pUltimo = pl->pPrimeiro;
    pl->pPrimeiro->pProx = NULL;
}

int pl_vazia(Pokelista *pl)
{
    if (pl == NULL)
    {
        return 1; // Considera a lista vazia se o ponteiro for NULL
    }
    else
    {
        pl->pPrimeiro = pl->pUltimo; // Se o ponteiro para a primeira célula for igual ao ponteiro para a última célula, a lista está vazia
    }
}

int pl_insere(Pokelista *pl, Pokemon p)
{
    Apontador nova;

    if (pl == NULL || pl->pUltimo == NULL)
    {
        return 0; // Falha na inserção devido a ponteiro nulo
    }

    pl->pUltimo->prox = (Apontador)malloc(sizeof(TCelula));

    if (pl->pUltimo->pProx == NULL)
    {
        return 0; // Falha na alocação de memória
    }

    pl->pUltimo = pl->pUltimo->pProx;

    nova = pl->pUltimo;
    nova->pokemon = p;
    nova->pProx = NULL;

    return 1;
}

Apontador pl_busca(Pokelista *pl, Pokemon p)
{

    Apontador atual;
    int idBuscado;

    if (pl == NULL || pl->pPrimeiro == NULL)
    {
        return NULL; // Lista vazia ou ponteiro nulo
    }

    idBuscado = p_get_id(&p);
    atual = pl->pPrimeiro->pProx; // Começa a busca a partir da primeira célula válida

    while (atual != NULL)
    {
        if (p_get_id(&(atual->pokemon)) == idBuscado)
        {
            return atual; // Retorna o ponteiro para a célula encontrada
        }
        atual = atual->pProx; // Avança para a próxima célula
    }

    return NULL; // Pokémon não encontrado
}

int pl_remove(Pokelista *pl, Pokemon p)
{
    Apontador anterior, atual;
    int idBuscado;

    if (pl == NULL || pl_vazia(pl))
    {
        return 0; // Lista vazia ou ponteiro nulo
    }

    idBuscado = p_get_id(&p);     // pega o id do pokemon que quero remover
    atual = pl->pPrimeiro->pProx; // Começa a busca a partir da primeira célula válida
    anterior = pl->pPrimeiro;     // celula cabeça

    while (atual != NULL)
    {

        if (p_get_id(&(atual->pokemon)) == idBuscado)
        {
            anterior->pProx = atual->pProx; // Remove a célula. Encontrei o que eu quero, pego o anterior e aponto para onde ele aponta. Logo, a cadeia nao se quebra.

            // Se eu removi o último, preciso atualizar pUltimo
            if (atual == pl->pUltimo)
            {
                pl->pUltimo = anterior;
            }

            free(atual); // Libera a memória
            return 1;    // Remoção bem-sucedida
        }
        anterior = atual;     // Avança o ponteiro anterior -> aqui tem uma escadinha!!!
        atual = atual->pProx; // Avança o ponteiro atual
    }

    return 0; // Pokémon não encontrado
}

int pl_tamanho(Pokelista *pl)
{
    Apontador atual;
    int tamanho = 0;

    if (pl == NULL || pl->pPrimeiro == NULL)
    {
        return 0; // Lista vazia ou ponteiro nulo
    }

    atual = pl->pPrimeiro->pProx; // Começa a contagem a partir da primeira célula válida (apos a cabeça)
    while (atual != NULL)
    {
        tamanho++;
        atual = atual->pProx;
    }

    return tamanho;
}

void pl_libera(Pokelista *pl)
{
    Apontador atual, proximo;

    if (pl == NULL)
    {
        return; // Ponteiro nulo
    }

    atual = pl->pPrimeiro->pProx; // Começa a partir da cabeça primeira celula apos a cabeça

    while (atual != NULL)
    {
        proximo = atual->pProx; // Armazena o próximo ponteiro (primeira celula apos a cabeça)
        free(atual);            // Libera a célula atual
        atual = proximo;        // Avança para a próxima célula
    }

    pl->pPrimeiro = NULL; // Define os ponteiros como NULL após liberar a lista
    pl->pUltimo = NULL;
}
