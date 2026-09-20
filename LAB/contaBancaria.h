#ifndef CONTA_BANCARIA_H
#define CONTA_BANCARIA_H

typedef struct {
    int numero_conta;
    char tipo_conta;
    int ano_abertura;
    float saldo;
} S_conta;

void inicializacao_conta(S_conta *conta);

void imprimir_conta(S_conta conta);

char get_tipo(S_conta conta);

void set_tipo(S_conta *conta, char novo_tipo);

float get_saldo(S_conta conta);

void saque(S_conta *conta, float valor_saque);

void deposito(S_conta *conta, float valor_deposito);

int avalia_credito(S_conta conta, int ano_atual);

#endif