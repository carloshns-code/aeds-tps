
#include <stdio.h>
#include <string.h>
#include "cliente.h"





void inicializa_cliente(S_cliente *cliente){
    // DIGIRTE O NOME DO cliente
    printf("\nDigite o nome do cliente: ");
    fgets(cliente->nome_cliente, sizeof(cliente->nome_cliente), stdin);
    cliente->nome_cliente[strcspn(cliente->nome_cliente, "\n")] = '\0';

    // DIGIRTE O CPF DO cliente
    printf("\nDigite o nome do cliente: ");
    fgets(cliente->cpf, sizeof(cliente->cpf), stdin);
    cliente->cpf[strcspn(cliente->cpf, "\n")] = '\0';


}


void imprime_cliente(S_cliente cliente){
    printf("\nNome do cliente: %s\n", cliente.nome_cliente);
    printf("\nCPF do cliente: %s\n", clietne.cpf);
}


void set_nome_cliente(S_cliente *cliente, char* nome){      //um novo nome sera digitado na main.c

}

void set_cpf_cliente(S_cliente *cliente, char* cpf){      //um novo cpf será digitado na main.c


} 


char* get_nome(S_cliente* cliente){


}

char* get_cpf(S_cliente* cliente){


}