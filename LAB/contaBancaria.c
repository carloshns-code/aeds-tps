#include <stdio.h>
#include "contaBancaria.h"

void inicializacao_conta(S_conta *conta) {
    printf("Digite o numero da conta: ");
    scanf("%d", &conta->numero_conta);

    printf("Digite o tipo da conta (Corrente - C ou Poupanca - P): ");
    scanf(" %c", &conta->tipo_conta);

    printf("Digite o ano de abertura da conta: ");
    scanf("%d", &conta->ano_abertura);

    printf("Digite o saldo da conta: ");
    scanf("%f", &conta->saldo);
}

void imprimir_conta(S_conta conta) {
    printf("\nCONTA BANCARIA\n");
    printf("Numero da conta: %d\n", conta.numero_conta);
    printf("Tipo da conta: %c\n", conta.tipo_conta);
    printf("Ano de abertura da conta: %d\n", conta.ano_abertura);
    printf("Saldo da conta: %.2f\n", conta.saldo);
}

char get_tipo(S_conta conta) {
    return conta.tipo_conta;
}

void set_tipo(S_conta *conta, char novo_tipo) {
    conta->tipo_conta = novo_tipo;
}

float get_saldo(S_conta conta) {
    return conta.saldo;
}

void saque(S_conta *conta, float valor_saque) {
    if (valor_saque <= 0) {
        printf("Valor de saque invalido.\n");
    } else if (valor_saque > conta->saldo) {
        printf("Saldo insuficiente.\n");
    } else {
        conta->saldo -= valor_saque;
        printf("Saque realizado com sucesso.\n");
    }
}

void deposito(S_conta *conta, float valor_deposito) {
    if (valor_deposito <= 0) {
        printf("Valor de deposito invalido.\n");
        return;
    }

    conta->saldo += valor_deposito;
    printf("Deposito realizado com sucesso.\n");
}

int avalia_credito(S_conta conta, int ano_atual) {
    return (ano_atual - conta.ano_abertura) >= 2;
}