#include <stdlib.h>
#include "centroDePesquisa.h"

CentroDePesquisa cp_init() {
    CentroDePesquisa cp;

    // inicializa os treinador com valores default
    // a pokelista é inicializada uma única vez para evitar vazamento de memória
    cp_init_treinador(&cp, t_init(TREINADOR1, VAZIO, ZERO), TREINADOR1);
    cp_init_treinador(&cp, t_init(TREINADOR2, VAZIO, ZERO), TREINADOR2);

    // inicialização das pokelistas
    cp_set_pl_fugitivos(&cp, pl_init());
    cp_set_pl_recuperados(&cp, pl_init());

    // inicialização da localização do centro de pesquisa
    cp_set_localizacao(&cp, c_init(ORIGEM, ORIGEM));

    return cp;
}


void cp_insere_registros(CentroDePesquisa *cp, FILE *inputFile) {
    // leitura dos treinadores
    int numPokebolasT1 = ZERO, numPokebolasT2 = ZERO;
    char nomeT1[MAX_TAM_STRING], nomeT2[MAX_TAM_STRING];

    // leitura dos pokemons
    int numPokemons = ZERO, numPokedexP = ZERO;
    float localizacaoX = ORIGEM, localizacaoY = ORIGEM;
    char nomeP[MAX_TAM_STRING], tipoP[MAX_TAM_STRING];

    // leitura das informações dos treinadores em variáveis auxiliares
    fscanf(inputFile, "%s %d", nomeT1, &numPokebolasT1);
    fscanf(inputFile, "%s %d", nomeT2, &numPokebolasT2);

    // atualização do nome e do número de pokebolas dos treinadores
    // a pokelista não é atualizada (evita vazamento de memória)
    cp_set_treinador(cp, nomeT1, numPokebolasT1, TREINADOR1);
    cp_set_treinador(cp, nomeT2, numPokebolasT2, TREINADOR2);

    fscanf(inputFile, "%d", &numPokemons);

    // loop responsável pela leitura das informações dos pokemons e inserção na lista de fugitivos
    for (int i = 0; i < numPokemons; i++) {
        fscanf(inputFile, "%d %s %s %f %f", &numPokedexP, nomeP, tipoP, &localizacaoX, &localizacaoY);
        Coordenada localizacaoP = c_init(localizacaoX, localizacaoY);
        pl_insere(cp_get_pl_fugitivos(cp), p_init(i, numPokedexP, nomeP, tipoP, localizacaoP));   //insere o pokemon na lista de fugitivos
    }
}

// remove o primeiro pokemon fugitivo da lista
void cp_remove_fugitivo(CentroDePesquisa *cp) {
    pl_remove(cp_get_pl_fugitivos(cp));
}

// imprime a lista de fugitivos
void cp_imprime_fugitivos(CentroDePesquisa *cp) {
    pl_imprime(cp_get_pl_fugitivos(cp), stdout);
}

// recebimento dos pokemons das pokelistas dos treinadores
void cp_recebe_pokemons(CentroDePesquisa *cp, int id) {
    Treinador *t = cp_get_treinador(cp, id);

    // utiliza um ponteiro auxiliar para "percorrer" a pokelista
    Pokelista *recebidos = t_get_pl(t);
    Pokemon p;

    // move o treinador para a localização do centro de pesquisa
    t_move(t, cp_get_localizacao(cp));

    // enquanto a pokelista do treinador ainda possui pokemons os pokemons do 
    // treinador são inseridos na pokelista de recuperados e removidos da 
    // pokelista do treinador, com essa implementação não é necessário percorrer 
    // a pokelista acessando diretamente a estrutura interna da pokelista

    while (!pl_vazia(recebidos)) {
        p = pl_get_p(recebidos);
        pl_insere(cp_get_pl_recuperados(cp), p);
        t_retira_pokemon(t);
    }
}

// recarrega as pokebolas do treinador
int cp_recarrega_pokebolas(CentroDePesquisa *cp, int id) {
    int newPokebolas = (rand() % MAX_POKEBOLAS) + MIN_POKEBOLAS;
    t_set_numPokebolas(cp_get_treinador(cp, id), newPokebolas);

    // retorna a quantidad de pokebolas recarregadas 
    return newPokebolas;
}

// inicializa os treinadores com um treinador default
void cp_init_treinador(CentroDePesquisa *cp, Treinador t, int id) {
    cp->treinadores[id] = t;
}

Treinador* cp_get_treinador(CentroDePesquisa *cp, int id) {
    return &cp->treinadores[id];
}

Pokelista* cp_get_pl_fugitivos(CentroDePesquisa *cp) {
    return &cp->pl_fugitivos;
}

Pokelista* cp_get_pl_recuperados(CentroDePesquisa *cp) {
    return &cp->pl_recuperados;
}

Coordenada cp_get_localizacao(CentroDePesquisa *cp) { 
    return cp->localizacao;
}

// função usada para alterar apenas nome e número de pokebolas do treinador,
// mantendo a pokelista intacta
void cp_set_treinador(CentroDePesquisa *cp, char nome[], int numPokebolas, int id) {
    t_set_nome(cp_get_treinador(cp, id), nome);
    t_set_numPokebolas(cp_get_treinador(cp, id), numPokebolas);
}

void cp_set_pl_fugitivos(CentroDePesquisa *cp, Pokelista pl) {
    cp->pl_fugitivos = pl;
}

void cp_set_pl_recuperados(CentroDePesquisa *cp, Pokelista pl) { 
    cp->pl_recuperados = pl;
}

void cp_set_localizacao(CentroDePesquisa *cp, Coordenada l) { 
    cp->localizacao = l;
}