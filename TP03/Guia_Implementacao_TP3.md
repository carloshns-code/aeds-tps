# TP3 — Guia de implementação e defesa técnica

## 1. Do enunciado à solução

O TP3 exige Pokémon, Centro de Pesquisa e PokeLista vetorial, duas operações de ordenação no Centro, ordenação crescente por poder e depois número da Pokédex, comparações, movimentações e tempo exclusivamente da ordenação com cinco casas decimais, saída em arquivo e comparação para N=100, 1000 e 10000. N=50000 é complementar. Referências: TP3CCF211-26.pdf pp. 1–3; Aula9-ORDSimples-2026.pdf slides 17, 19 e 20; Aula11-ORDQuickSort-2026.pdf slides 6–8 e 11–13. Os quatro volumes de estudo do TP2 orientam a organização modular, mas não são o enunciado do TP3.

A estrutura adotada preserva os prefixos p_, pl_, cp_ e cm_ do código do TP2. Adaptamos pokemon.c/h, pokelista.c/h, centroDePesquisa.c/h, controleDaMissao.c/h, utils.h, main.c e Makefile. Não copiamos treinador, coordenada, selecao ou equipe, pois não há captura, coordenadas, limite de energia nem escolha de subconjuntos. A versão do TP2 nos slides usa Equipe e vetor; os fontes enviados usam Selecao e lista. Nenhuma dessas duas versões do algoritmo de força bruta entra neste projeto.

## 2. Organização e estratégia

Crie TP3_Pokemon, os 11 arquivos da raiz na ordem abaixo, as pastas testes e saidas. Copie os quatro arquivos de entrada originais para testes. Não altere TP2. Abra a pasta como projeto C no editor. O ZIP já contém tudo montado. Em um projeto vazio, copie cada bloco abaixo para o arquivo indicado, sem as cercas de Markdown. Os comentários do código explicam operações locais; as referências de linhas abaixo contam a primeira linha do bloco como linha 1. Chaves abrem e fecham blocos; ponto e vírgula encerra instrução; linhas vazias só organizam a leitura.

Fluxo: main -> controle -> centro -> pokelista -> pokemon. utils.h fornece constantes. O centro contém uma Pokelista, que contém vetor, tamanho e capacidade. A lista tem capacidade exatamente N, lido do cabeçalho. A cópia é profunda: aloca outro vetor e copia cada Pokemon inteiro. Não faça `quick = selection`, pois os ponteiros seriam compartilhados, levando a comparação injusta e dupla liberação. Não há remoção no TP3. Os índices começam em 0, não correspondem à Pokédex. Espécies repetidas são registros distintos e não podem ser descartadas.

Regra de comparação: (poder, numPokedex). Se a primeira chave empatar, consulta-se a segunda. As duas chaves iguais significam equivalência para ordenação; não há terceiro critério. Nome e tipo viajam com a struct inteira.

Métricas: uma comparação lógica entre duas chaves compostas (uma chamada a compara), inclusive o teste falso de cada varredura do QuickSort. Não contamos condições de índices ou a verificação externa. A aula 9 conta três atribuições de registros por troca, inclusive autotrocas; usamos a mesma convenção nos dois algoritmos e contamos também a cópia do pivô (uma atribuição de registro). Se a professora preferir contar somente escritas no vetor, a definição muda: duas por troca e zero por pivô. Não misture definições. Se exigir comparações primitivas de campos, instrumente cada teste em p_compara e reexecute ambos; os valores deste guia são comparações de chaves compostas.

## 3. Construção arquivo por arquivo

### Passo 1 — `utils.h`

Constantes e proteção contra inclusão repetida.

```c
#ifndef UTILS_H
#define UTILS_H

#define MAX_TAM_STRING 50  /* 49 caracteres mais o terminador '\0'. */
#define ZERO 0             /* Valor inicial de contadores e indices. */
#define SUCESSO 0          /* Codigo de retorno sem erro. */
#define ERRO 1             /* Codigo de retorno com erro. */
#define NUM_CAMPOS 4        /* Pokedex, nome, tipo e poder. */
#define MOV_TROCA 3         /* Tres atribuicoes de Pokemon por troca. */
#define MOV_PIVO 1          /* Uma copia do Pokemon para o pivo. */
#define NUM_ARGUMENTOS 4    /* Executavel, entrada, duas saidas. */

#endif
```

**Leitura comentada por linhas**
- L1–2: Abre a proteção do cabeçalho; o pré-processador inclui o conteúdo apenas uma vez.
- L4–11: Define respectivamente limite de string, zero, retorno de sucesso, erro, quantidade de campos, custo da troca, custo do pivô e argc esperado. A constante 4 inclui o nome do programa.
- L13: Fecha a proteção.

### Passo 2 — `pokemon.h`

TAD Pokémon: contrato público.

```c
#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>  /* Define FILE. */
#include "utils.h"  /* Constantes compartilhadas. */

typedef struct {
    int numPokedex;             /* Chave secundaria. */
    char nome[MAX_TAM_STRING];  /* Nome do Pokemon. */
    char tipo[MAX_TAM_STRING];  /* Tipo do Pokemon. */
    int poder;                  /* Chave principal. */
} Pokemon;

/* Interface adaptada do TP2: somente os atributos do TP3. */
Pokemon p_init(int numPokedex, const char nome[], const char tipo[], int poder);
int p_get_numPokedex(const Pokemon *p);
const char *p_get_nome(const Pokemon *p);
const char *p_get_tipo(const Pokemon *p);
int p_get_poder(const Pokemon *p);
void p_set_numPokedex(Pokemon *p, int numPokedex);
void p_set_nome(Pokemon *p, const char nome[]);
void p_set_tipo(Pokemon *p, const char tipo[]);
void p_set_poder(Pokemon *p, int poder);
int p_compara(const Pokemon *a, const Pokemon *b);
void p_imprime(const Pokemon *p, FILE *saida);

#endif
```

**Leitura comentada por linhas**
- L1–5: Proteção e inclusão de FILE e constantes.
- L7–12: typedef struct cria o tipo Pokemon com quatro atributos; arrays de caracteres pertencem ao registro, não são ponteiros para textos externos.
- L14–25: Protótipos: inicialização recebe quatro atributos e devolve uma struct; getters consultam por ponteiro const; setters recebem ponteiro modificável; comparação devolve sinal; impressão recebe FILE*.
- L27: Fim da proteção.

### Passo 3 — `pokemon.c`

Implementação do registro e regra de ordenação.

```c
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
```

**Leitura comentada por linhas**
- L1–2: Importa strncpy e as declarações.
- L4–11: p_init cria p com campos inicializados, chama cada setter com &p e retorna a struct por valor. & extrai o endereço; por isso os setters modificam a variável local.
- L13–16: Cada getter devolve um atributo com ->, operador de acesso ao campo de uma struct apontada. const impede alteração através desse parâmetro.
- L18–19: Setters numéricos atribuem diretamente os valores aos campos.
- L21–29: Setters de strings copiam até 49 caracteres com strncpy e garantem o terminador nulo na posição 49.
- L31–39: p_compara examina poder primeiro. Se menor, retorna -1; se maior, 1. Só no empate examina a Pokédex. Se ambas iguais, retorna 0. Não subtraímos inteiros para evitar estouro em valores extremos.
- L41–45: Imprime quatro campos na ordem de entrada em um FILE*, seguido de quebra de linha. O nome e o tipo continuam associados ao Pokémon.

### Passo 4 — `pokelista.h`

Nova representação vetorial.

```c
#ifndef POKELISTA_H
#define POKELISTA_H

#include "pokemon.h"

typedef struct {
    Pokemon *vetor; /* Endereco da memoria que contem os registros. */
    int tamanho;    /* Quantidade de posicoes efetivamente ocupadas. */
    int capacidade; /* Quantidade de posicoes alocadas. */
} Pokelista;

Pokelista pl_init(int capacidade);
void pl_insere(Pokelista *pl, Pokemon p);
void pl_imprime(const Pokelista *pl, FILE *saida);
int pl_tamanho(const Pokelista *pl);
Pokemon *pl_get_vetor(Pokelista *pl);
Pokelista pl_copia(const Pokelista *origem);
int pl_ordenada(const Pokelista *pl);
void pl_libera(Pokelista *pl);

#endif
```

**Leitura comentada por linhas**
- L1–4: Proteção e acesso à definição Pokemon.
- L6–10: A struct guarda ponteiro para área dinâmica, quantidade ocupada e capacidade total.
- L12–19: Declara inicialização, inserção, impressão, tamanho, acesso ao vetor, cópia, verificação e liberação. As funções que apenas leem recebem const.
- L21: Fim da proteção.

### Passo 5 — `pokelista.c`

Gerenciamento do vetor.

```c
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
```

**Leitura comentada por linhas**
- L1–2: Importa malloc, free, exit e a interface.
- L4–21: Inicializa ponteiro nulo, tamanho zero e capacidade. Rejeita capacidade negativa ou multiplicação que não caiba em size_t; aloca somente se capacidade positiva, testa falha e devolve a estrutura. sizeof informa bytes por Pokémon; malloc devolve endereço.
- L23–30: Insere na posição tamanho, após verificar espaço; incrementa tamanho. Atribuição de struct copia todos os campos de uma vez.
- L32–33: Retorna tamanho em O(1) e endereço inicial do vetor, respectivamente.
- L35–40: Imprime N e percorre as N posições, delegando a impressão individual ao TAD Pokemon.
- L42–48: Aloca outra lista, percorre origem, insere registros por valor e devolve a cópia. Os vetores não compartilham memória.
- L50–55: Verifica os pares consecutivos. Se anterior maior que atual, retorna falso; caso contrário retorna verdadeiro depois de examinar todos.
- L57–62: free libera o vetor; zera a estrutura para não manter endereço inválido.

### Passo 6 — `centroDePesquisa.h`

Interface de ordenação exigida pelo enunciado.

```c
#ifndef CENTRODEPESQUISA_H
#define CENTRODEPESQUISA_H

#include "pokelista.h"

typedef struct {
    unsigned long long comparacoes;  /* Numero de consultas a chave composta. */
    unsigned long long movimentacoes; /* Copias de registros no algoritmo. */
    double tempoSegundos;             /* Tempo de CPU em segundos. */
} Metricas;

typedef struct {
    Pokelista pl_recuperados; /* Lista vetorial dos Pokemon recuperados. */
} CentroDePesquisa;

CentroDePesquisa cp_init(int capacidade);
Pokelista *cp_get_pl_recuperados(CentroDePesquisa *cp);
void cp_insere_registros(CentroDePesquisa *cp, FILE *entrada);
CentroDePesquisa cp_copia(const CentroDePesquisa *origem);
Metricas cp_selectionSort(CentroDePesquisa *cp);
Metricas cp_quickSort(CentroDePesquisa *cp);
void cp_libera(CentroDePesquisa *cp);

#endif
```

**Leitura comentada por linhas**
- L1–4: Proteção e importação da lista.
- L6–10: Metricas agrupa comparações, movimentações e tempo; unsigned long long evita limite de 32 bits para contagens grandes.
- L12–14: CentroDePesquisa contém a PokeLista de recuperados.
- L16–22: Declara inicialização, getter, leitura, cópia, duas operações de ordenação e liberação. Cada ordenação retorna as métricas daquela execução.
- L24: Fim da proteção.

### Passo 7 — `centroDePesquisa.c`

Núcleo do trabalho: leitura, ordenação e medição.

```c
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
```

**Leitura comentada por linhas**
- L1–3: Importa exit, relógio da biblioteca padrão e a interface.
- L5–9: Cria centro, inicializa lista com capacidade e devolve centro por valor.
- L11–13: Retorna endereço da lista interna, permitindo modificar a original.
- L15–27: Laço executa N vezes. Declara campos; fscanf lê quatro valores, %49s limita o texto, & passa endereços de inteiros. Valida número de campos e valores não negativos; cria Pokemon e insere. Espera arquivo com formato válido e números representáveis em int.
- L29–33: Cria outro centro e usa pl_copia para alocar vetor independente.
- L35–39: static restringe auxiliar ao módulo; incrementa comparação uma vez, mesmo se o resultado for falso no while; delega regra de chaves.
- L41–46: Recebe endereços de dois registros. aux salva *a, *a recebe *b, *b recebe aux; soma três cópias de registros. Inclui autotroca para reproduzir a aula.
- L48–60: SelectionSort: i é posição a fixar, min começa em i, j percorre i+1 até n-1, compara candidato contra menor conhecido, atualiza min quando candidato menor, troca registros inteiros ao final de cada iteração. Não troca a cada comparação.
- L62–77: Partição: i e j são ponteiros para índices do chamador. Inicializa extremos, copia registro central, contabiliza pivô; do inicia varredura. Enquanto pivô maior que v[*i], i avança; enquanto pivô menor que v[*j], j recua. Se ainda não cruzaram, troca e move ambos, inclusive em empate. Repete até cruzarem. O pivô é uma cópia, não uma referência à posição que pode mudar.
- L79–84: ordena chama particao com &i e &j; recursão só ocorre em intervalos com mais de um item. A parte esquerda vai de esq a j; a direita vai de i a dir. Não se presume que o pivô esteja em posição final.
- L86–96: Inicializa métricas com zeros, obtém vetor e tamanho antes do relógio. Inicia clock, ordena, encerra clock, converte ticks em segundos com cast double e devolve métricas.
- L98–108: Mesmo procedimento para QuickSort; guarda n > 1 antes da primeira partição para impedir acessar vetor vazio. Intervalo inicial 0..n-1.
- L110–112: Delega a liberação ao TAD lista.

### Passo 8 — `controleDaMissao.h`

Interface de entrada, saída e liberação.

```c
#ifndef CONTROLEDAMISSAO_H
#define CONTROLEDAMISSAO_H

#include "centroDePesquisa.h"

CentroDePesquisa cm_registro(const char *caminho);
void cm_imprime(const char *algoritmo, Metricas m, int n);
void cm_salva(CentroDePesquisa *cp, const char *caminho);
void cm_libera(CentroDePesquisa *cp);

#endif
```

**Leitura comentada por linhas**
- L1–4: Proteção e inclusão do Centro.
- L6–9: Declara leitura de arquivo por caminho, impressão de métricas, gravação do vetor e liberação do centro.
- L11: Fim da proteção.

### Passo 9 — `controleDaMissao.c`

Operações de arquivo.

```c
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
```

**Leitura comentada por linhas**
- L1–2: Importa exit e interface.
- L4–20: fopen r abre entrada; verifica NULL, lê N com fscanf, valida N, inicializa centro, carrega registros, fecha e devolve centro. Nenhuma dessas operações entra na medição.
- L22–28: Imprime nome, N, contadores %llu e tempo %.5f, em segundos. Não confundir precisão exibida com precisão física.
- L30–41: fopen w cria/sobrescreve saída, verifica erro, imprime lista e verifica fclose. Use caminhos distintos e pasta existente.
- L43: Delega liberação ao Centro.

### Passo 10 — `main.c`

Fluxo completo e integração.

```c
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
```

**Leitura comentada por linhas**
- L1–2: Importa strcmp e o controle.
- L4–8: argc conta argumentos incluindo executável; exige quatro, informa sintaxe caso contrário.
- L9–13: strcmp igual a zero significa texto igual; evita reutilização literal do mesmo caminho. Use arquivos realmente distintos, sem aliases.
- L14–16: Carrega entrada e cria cópia independente antes de ordenar. Obtém N da lista.
- L18–19: Executa cada algoritmo sobre seu próprio centro e guarda os resultados.
- L21–27: Verifica ambos os vetores fora do cronômetro. Se falhar, libera os dois e retorna erro.
- L28–32: Exibe métricas, salva os dois arquivos e informa sucesso.
- L33–36: Libera cada vetor exatamente uma vez e retorna sucesso.

### Passo 11 — `Makefile`

Automação da compilação.

```makefile
# Linux: make ; Windows (MinGW/MSYS2 com GCC e make): make
# No MinGW que oferece mingw32-make, use mingw32-make.
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2
OBJ = main.o pokemon.o pokelista.o centroDePesquisa.o controleDaMissao.o
ifeq ($(OS),Windows_NT)
    ALVO = tp3.exe
else
    ALVO = tp3
endif

all: $(ALVO)

$(ALVO): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(ALVO)

main.o: main.c controleDaMissao.h centroDePesquisa.h pokelista.h pokemon.h utils.h
pokemon.o: pokemon.c pokemon.h utils.h
pokelista.o: pokelista.c pokelista.h pokemon.h utils.h
centroDePesquisa.o: centroDePesquisa.c centroDePesquisa.h pokelista.h pokemon.h utils.h
controleDaMissao.o: controleDaMissao.c controleDaMissao.h centroDePesquisa.h pokelista.h pokemon.h utils.h

.PHONY: all
```

**Leitura comentada por linhas**
- L1–2: Comentários documentam Linux e Windows com MinGW.
- L3–5: Define compilador, flags e módulos objeto. -std=c11, avisos e -O2, iguais para os dois métodos.
- L6–10: Escolhe tp3.exe no Windows e tp3 em outros ambientes.
- L12–15: Alvo padrão depende do executável; executável depende dos objetos; receita com TAB chama gcc para ligação.
- L17–21: Dependências: alterações em cabeçalhos provocam recompilação dos objetos correspondentes.
- L23: Declara all como alvo lógico, não arquivo.

## 4. Entendendo os algoritmos

### SelectionSort
Invariante: antes da iteração i, posições 0..i-1 contêm os menores elementos em ordem final. Procure o menor no resto e coloque em i. Para o vetor de chaves (poder, Pokédex) [(60,25),(15,13),(50,4),(15,10),(30,7)]:

- i=0: menor (15,10) na posição 3; troque com 0. [(15,10),(15,13),(50,4),(60,25),(30,7)].
- i=1: (15,13) já é o menor restante; autotroca.
- i=2: (30,7) é o menor restante, troque com a posição 4. [(15,10),(15,13),(30,7),(60,25),(50,4)].
- i=3: troque (60,25) com (50,4). Pronto.
- Comparações 4+3+2+1=10, movimentações 4*3=12.

C(n)=n(n-1)/2; M(n)=3(n-1), para n>=1 na versão da aula. n=0 dá zero. Comparações Theta(n²) em todos os casos, memória auxiliar O(1). Não estável. A troca condicional min != i é outra versão; não foi adotada.

### QuickSort
Exemplo da aula 11: [3,6,4,5,1,7,2]. Pivô central 5. i para em 6, j para em 2, troca: [3,2,4,5,1,7,6]. i avança até 5, j recua até 1, troca: [3,2,4,1,5,7,6]. Índices cruzam após essa troca: parte esquerda [3,2,4,1], parte direita [5,7,6]. A função ordena chama-se recursivamente nos dois intervalos, até restarem intervalos de 0/1 itens. Resultado [1,2,3,4,5,6,7]. Na implementação, cada número representa uma chave composta e cada troca movimenta a struct inteira. Igualdade interrompe as varreduras, mas os índices avançam após a troca, evitando laço infinito. Copiar o pivô é essencial, pois sua posição original pode ser sobrescrita.

Melhor e médio Theta(n log n); pior Theta(n²), quando as partições ficam sistematicamente desequilibradas. A escolha central não garante mediana. Vetor ordenado não é necessariamente pior caso com pivô central. Pilha O(log n) em partições balanceadas e O(n) no pior caso. Não estável. O risco de estouro da pilha em entradas adversariais muito grandes é uma limitação da versão recursiva clássica ensinada.

## 5. Compilar e executar

No terminal, abra a pasta TP3_Pokemon. Confira `gcc --version`. Use `make` (Linux ou MSYS2); `mingw32-make` (MinGW no Windows, se disponível). Alternativamente:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 main.c pokemon.c pokelista.c centroDePesquisa.c controleDaMissao.c -o tp3
```

No Windows substitua o final por `-o tp3.exe`. Não use gcc *.c se houver arquivos antigos com outra main. Se alterar flags, remova os .o e o executável antes de recompilar. O Makefile precisa de TAB na linha de receita.

Linux:
```sh
./tp3 testes/teste_didatico.txt saidas/selection_didatico.txt saidas/quick_didatico.txt
./tp3 testes/teste_100.txt saidas/selection_100.txt saidas/quick_100.txt
./tp3 testes/teste_1000.txt saidas/selection_1000.txt saidas/quick_1000.txt
./tp3 testes/teste_10000.txt saidas/selection_10000.txt saidas/quick_10000.txt
./tp3 testes/teste_50000.txt saidas/selection_50000.txt saidas/quick_50000.txt
```
Windows PowerShell: use `.\tp3.exe` em vez de `./tp3`. Todos os caminhos são relativos à pasta atual; use aspas se houver espaços. Os arquivos de saída são sobrescritos a cada execução. Não indique o próprio arquivo de entrada como saída.

Valide o caso didático: 5 Pokémon, Caterpie 15, Weedle 15, Squirtle 30, Charmander 50, Pikachu 60; SelectionSort C=10 M=12, QuickSort C=12 M=18. Testes vazio e unitário devem ter contagens zero. Iguais, ordenado e invertido verificam término, empates e diferentes disposições. Execute trocando o sufixo nos três caminhos. O script opcional `python verificar.py testes/teste_100.txt saidas/selection_100.txt saidas/quick_100.txt` verifica quantidade, multiconjunto completo dos registros e ordem. Python não é necessário para compilar o trabalho.

## 6. Resultados reais de uma execução de referência

Ambiente de execução: Linux x86_64, AMD EPYC 9V74 (ambiente virtualizado), GCC 14.2.0, flags -std=c11 -Wall -Wextra -Wpedantic -O2. Uma execução por tamanho; não use os tempos como se fossem medidos no computador do grupo. Refaça as medições, idealmente 5 repetições por N, usando a mediana e as mesmas flags. 0.00000 significa arredondamento/resolução, não tempo literalmente nulo. Os contadores são determinísticos para esta entrada e versão. Todos os registros dos 10 casos testados foram comparados independentemente com a entrada, inclusive duplicatas.

| N | Selection C | Selection M | Selection s | Quick C | Quick M | Quick s |
|---:|---:|---:|---:|---:|---:|---:|
|100|4950|297|0.00001|940|617|0.00001|
|1000|499500|2997|0.00119|13704|8530|0.00009|
|10000|49995000|29997|0.10749|174416|111291|0.00112|
|50000|1249975000|149997|2.84214|1042621|665019|0.00735|

O SelectionSort efetua menos movimentações nos testes, mas muito mais comparações. QuickSort é a escolha mais adequada para as entradas grandes observadas. Não afirme que é sempre melhor: há pior caso quadrático, recursão e mais movimentações. SelectionSort é interessante para entradas pequenas e registros caros de mover. Ambos são in situ em relação ao vetor ordenado; a cópia extra faz parte do experimento, não do algoritmo. A carga de dados é O(n), a cópia é O(n), impressão é O(n), e ficam fora do tempo medido.

## 7. Apresentação e defesa

1. Introdução: contextualize a missão e o novo requisito de catalogação.
2. TADs: compare lista encadeada do TP2 com lista vetorial do TP3; explique tamanho, capacidade e malloc/free.
3. Critério: demonstre o empate Caterpie/Weedle.
4. SelectionSort: mostre código, invariante e fórmulas C(n) e M(n).
5. QuickSort: mostre pivô central, partição, duas chamadas recursivas e caso-base.
6. Metodologia: mesma entrada original, contadores e cronômetro exclusivo, equipamento e flags.
7. Resultados: tabela de comparações, movimentações e tempos; use gráficos separados, preferencialmente escala log para tempos grandes e não represente zero em escala log.
8. Discussão: custo quadrático versus n log n médio; trocas, pilha, estabilidade, casos extremos.
9. Conclusão: escolha QuickSort para o catálogo com base nos dados; explique ressalvas.

Perguntas para treinar: por que não copiar só a struct do centro? Porque compartilharia o ponteiro. Por que não ordenar só o poder? Porque o desempate exige Pokédex. Por que copiar o pivô? Porque a posição pode mudar. Por que usar ponteiro para i e j? Para devolver limites ao chamador. Por que não contar i<j? Não compara chaves. Por que N=0 não chama QuickSort? Não há pivô válido. Por que Selection não melhora se já ordenado? Continua procurando o menor em todo sufixo. Os algoritmos são estáveis? Não. Qual critério de movimentos? Três por troca e um por cópia de pivô; declarar explicitamente. Como verificar se não perdeu Pokémon? Conferir multiconjunto de todos os campos, além da ordem. Por que clock em segundos? Dividir diferença por CLOCKS_PER_SEC; %.5f formata. Qual memória? Vetores O(n) e pilha recursiva variável; Selection tem memória auxiliar O(1).

## 8. Entrega

O enunciado indica documentação + código em ZIP ou TAR.GZ, Moodle, 26/11/2026; entrevistas 01/12 e 03/12. Confirme com a professora formato da documentação e apresentação. Prepare a documentação com resultados da máquina do grupo. Não entregue o executável Linux, .o ou o guia de estudo como substituto automático da documentação exigida. Revise a solução e seja capaz de explicá-la. O programa considera o formato especificado (tokens sem espaços, inteiros representáveis e N registros); não é um parser genérico de arquivos arbitrários. Arquivos extras de saída e script Python são opcionais.
