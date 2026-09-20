#include <stdio.h>
#include <string.h>
#include "cliente.h"

void inicializa_cliente(S_cliente *cliente) {
    char nome[50];
    char cpf[12];

    printf("Digite o nome do cliente: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite o CPF do cliente: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    set_nome_cliente(cliente, nome);
    set_cpf_cliente(cliente, cpf);
}

void imprime_cliente(S_cliente cliente) {
    printf("\nCLIENTE\n");
    printf("Nome do cliente: %s\n", cliente.nome_cliente);
    printf("CPF do cliente: %s\n", cliente.cpf);
}

void set_nome_cliente(S_cliente *cliente, const char *nome) {
    strcpy(cliente->nome_cliente, nome);
}

void set_cpf_cliente(S_cliente *cliente, const char *cpf) {
    strcpy(cliente->cpf, cpf);
}

char* get_nome(S_cliente *cliente) {
    return cliente->nome_cliente;
}

char* get_cpf(S_cliente *cliente) {
    return cliente->cpf;
}