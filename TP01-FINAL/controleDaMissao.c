#include <stdio.h>
#include "controleDaMissao.h"

// inicializa as estruturas da missão
// a criação dessa função visa a preservação da modularidade
// e encapsulamento dos tipos de dados
CentroDePesquisa cm_init() { 
    return cp_init;
}

// caso o arquivo a ser lido não seja especificado nos args,
// a função é invocada para realizar a leitura do no caminho
// desejado para execução
void cm_input(char inputFileName[]) { 
    printf("Digite o caminho do arquivo de entrada: "); 
    scanf("%s", inputFileName);}

// faz a abertura do arquivo e chama a função de inserção de regsitros
// do centro de pesquisa
void cm_registro(CentroDePesquisa *cp, char inputFileName[]) { 
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) { 
        printf("Erro: Nao foi possivel abrir o arquivo '%s'.\n", inputFileName); 
        return; 
    }

    cp_insere_registros(cp, inputFile);

    fclose(inputFile);
}

// função responsável pela lógica de captura dos pokemons fugitivos
void cm_captura(CentroDePesquisa *cp) { 
    int idEscolhido, numFugitivos = pl_tamanho(cp_get_pl_fugitivos(cp)); 
    float distanciaT1, distanciaT2 ;

    Treinador *tEscolhido; 
    Pokemon p;

    printf("========================================\n"); 
    printf("             INICIO DA MISSAO           \n"); 
    printf("========================================\n\n");

    t_imprime(cp_get_treinador(cp, TREINADOR1));
    t_imprime(cp_get_treinador(cp, TREINADOR2));

    printf("\nPokemons fugitivos a serem resgatados: %d\n\n", numFugitivos);

    // a lógica de captura dos pokemons é executada 1 vez para cada pokemon fugitivo
    for (int i = 0; i < numFugitivos; i++) {
        // o pokemon a ser resgatado é sempre o primeiro pokemon da lista 
        // quando um pokemon é resgatado no loop anterior, ele é removido da lista 
        // e o antigo segundo pokemon da lista se torna o primeiro, tornando desnecessaria 
        // a busca do pokemon na lista de fugitivos 
        p = pl_get_p(cp_get_pl_fugitivos(cp));

    // calculo da distancia dos treinadores ate o pokemon a ser resgatado

    distanciaT1 = c_distancia(p_get_localizacao(&p), t_get_localizacao(cp_get_treinador(cp, TREINADOR1)));
    distanciaT2 = c_distancia(p_get_localizacao(&p), t_get_localizacao(cp_get_treinador(cp, TREINADOR2)));

    // o treinador designado para a função é o treinador mais próximo do pokemon 
    // com preferência para o de menor id em caso de distâncias iguais 
    idEscolhido = (distanciaT1 <= distanciaT2) ? TREINADOR1 : TREINADOR2;

    // o treinador escolhido é salvo em tEscolhido de forma a facilitar 
    // as impressões das informações e chamadas de funções relacionadas 
    // ao treinador escolhido, evitando o uso repetitivo de: // cp_get_treinador(cp, idEscolhido) a cada impressão ou chamada de função 
    tEscolhido = cp_get_treinador(cp, idEscolhido);

    printf("----------------------------------------\n"); 
    printf("Pokemon Alvo: %s\n", p_get_nome(&p)); 
    printf("Localizacao: (%.1f,%.1f)\n\n", c_get_localizacao_x(p_get_localizacao(&p)), 
    c_get_localizacao_y(p_get_localizacao(&p)));

    printf("Distancia Treinador(a) %s: %.2f\n", t_get_nome(cp_get_treinador(cp, TREINADOR1)), distanciaT1); 
    
    printf("Distancia Treinador(a) %s: %.2f\n\n", t_get_nome(cp_get_treinador(cp, TREINADOR2)), distanciaT2); 
    
    printf("Missao atribuida ao Treinador(a) %s\n\n", t_get_nome(tEscolhido));

    // verifica se o treinador possui pokebolas antes de sair do centro de pesquisa 
    if (t_get_numPokebolas(tEscolhido) == 0) { 
        printf("========================================\n"); 
        printf(" Treinador(a) %s SEM POKEBOLAS \n", t_get_nome(tEscolhido)); 
        printf("========================================\n\n");

        printf("Recarregando Pokebolas do treinador\n\n");


        printf("Treinador(a) %s recebeu %d Pokebolas\n\n", t_get_nome(tEscolhido), cp_recarrega_pokebolas(cp, idEscolhido));

        printf("----------------------------------------\n\n");
    }

    printf("Treinador(a) %s se movimentou para (%.1f,%.1f)\n", t_get_nome(tEscolhido), 
    c_get_localizacao_x(p_get_localizacao(&p)), c_get_localizacao_y(p_get_localizacao(&p)));

    // move o treinador para a posição do pokemon 
    t_move(tEscolhido, p_get_localizacao(&p));

    // captura o pokemon 
    t_captura(tEscolhido, p);

    // remove o pokemon da lista de fugitivos 
    // assim que o pokemon é capturado 
    cp_remove_fugitivo(cp);

    printf("%s capturado com sucesso!\n\n", p_get_nome(&p)); 
    printf("Pokebolas restantes para o Treinador(a) %s: %d\n\n", t_get_nome(tEscolhido), t_get_numPokebolas(tEscolhido));

    // caso o treinador fique sem pokebolas quando o ultimo pokemon é capturado 
    // o treinador não recebe novas pokebolas, já que todos os pokemons ja foram 
    // capturados, tornando desnecessária a recarga das pokebolas
    if (t_get_numPokebolas(tEscolhido) == 0 && i != numFugitivos - 1) { 
        printf("========================================\n"); 
        printf(" Treinador(a) %s SEM POKEBOLAS \n", t_get_nome(tEscolhido)); 
        printf("========================================\n\n");

    

    printf("Treinador(a) %s retorna ao Centro de Pesquisa\n\n", t_get_nome(tEscolhido));

    printf("Entregando Pokemons ao Centro de Pesquisa\n\n");

    // ao retornar para o centro de pesquisa o treinador esvazia sua 
    // pokelista e insere os pokemons na pokelista de pokemons recuperados 
    cp_recebe_pokemons(cp, idEscolhido);

    printf("Treinador(a) %s recebeu %d Pokebolas\n\n", t_get_nome(tEscolhido), cp_recarrega_pokebolas(cp, idEscolhido)); 

    printf("Entregando Pokemons ao Centro de Pesquisa\n\n"); 
    
    // ao retornar para o centro de pesquisa o treinador esvazia sua 
    // pokelista e insere os pokemons na pokelista de pokemons recuperados 
    cp_recebe_pokemons(cp, idEscolhido); 
    
    printf("Treinador(a) %s recebeu %d Pokebolas\n\n", t_get_nome(tEscolhido), cp_recarrega_pokebolas(cp, idEscolhido));
    } 
}
    


printf("========================================\n"); 
printf(" Todos Pokemons foram resgatados \n"); 
printf("========================================\n\n");

}

// após o resgate de todos os pokemons ambos os treinadores retornam
// ao centro de pesquisa e devolvem os pokemons

void cm_retorno(CentroDePesquisa *cp) { 
    printf("Ambos treinadores retornam ao Centro de Pesquisa\n\n"); 
    
    printf("Treinador(a) %s devolve os Pokemons\n\n", t_get_nome(cp_get_treinador(cp, TREINADOR1))); 
    cp_recebe_pokemons(cp, TREINADOR1); 
    printf("Treinador(a) %s devolve os Pokemons\n\n", t_get_nome(cp_get_treinador(cp, TREINADOR2))); 
    cp_recebe_pokemons(cp, TREINADOR2); 
    printf("========================================\n"); 
    printf("           MISSAO CONCLUIDA             \n"); 
    printf("========================================\n");}

// gera o relatório de saída invocando a função responsável pela escrita 
// do relatório, pl_imprime evita o acesso direto à estrutura
// interna da lista e preserva o encapsulamento

void cm_imprime(CentroDePesquisa *cp) { 
    FILE *outputFile = fopen("relatorio.txt", "w"); 
    
    if (outputFile == NULL) { 
        
        printf("Erro: Nao foi possivel criar o arquivo 'relatorio.txt'.\n"); 
        return; 
    }

fprintf(outputFile, "Pokemons recuperados:\n"); 
pl_imprime(cp_get_pl_recuperados(cp), outputFile);
fclose(outputFile);}

// libera a memória alocada pelo programa ao longo da execução
void cm_libera(CentroDePesquisa *cp) { 
    pl_libera(cp_get_pl_fugitivos(cp)); 
    pl_libera(cp_get_pl_recuperados(cp)); 
    pl_libera(t_get_pl(cp_get_treinador(cp, TREINADOR1))); 
    pl_libera(t_get_pl(cp_get_treinador(cp, TREINADOR2)));

}