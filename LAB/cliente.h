#ifndef CLIENTE_H
#define CLIENTE_H

#include "contaBancaria.h"

typedef struct {
    char nome_cliente[50];
    char cpf[12];
    S_conta conta;
} S_cliente;

void inicializa_cliente(S_cliente *cliente);

void imprime_cliente(S_cliente cliente);

void set_nome_cliente(S_cliente *cliente, const char *nome);

void set_cpf_cliente(S_cliente *cliente, const char *cpf);

char* get_nome(S_cliente *cliente);

char* get_cpf(S_cliente *cliente);

#endif