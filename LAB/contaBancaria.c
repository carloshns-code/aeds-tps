#include "ContaBancaria.h"
#include "cliente.c"
#include <stdio.h>
#include <string.h>
#define ANO 2026

void inicializacao_conta(S_conta *conta)
{
    
    // DIGITE O NUMERO DA conta
    printf("Digite o numero da conta: ");
    scanf("%d", &conta->numero_conta);
    getchar(); // consome o enter

    // DIGITE O TIPO DA conta
    printf("\nDigite o tipo da conta (Corrente - C ou Poupanca - P)");
    scanf(" %c", &conta->tipo_conta);

    // DIGITE O ANO DE ABERTURA DA conta
    printf("\nDigite o ano de abertura da conta: ");
    scanf("%d", &conta->ano_abertura);

    // DIGITE O SALDO DA conta
    printf("\nDigite o saldo da conta: ");
    scanf("%f", &conta->saldo);

    inicializa_cliente;   //entra na outra struct cliente 
}

void imprimir_conta(S_conta conta)
{

    printf("\nNumero da conta: %d\n", conta.numero_conta);
    printf("\nTipo da conta: %c\n", conta.tipo_conta);
    printf("\nAno de abertura da conta: %d\n", conta.ano_abertura);
    printf("\nSaldo da conta: %.2f\n", conta.saldo);
}

void get_tipo(S_conta conta)
{
    getchar();
    printf("\nO tipo da conta eh: %c", conta.tipo_conta);
}

void set_tipo(S_conta *conta)
{
    printf("\nInsira um novo tipo para a conta: \n");
    scanf(" %c", &conta->tipo_conta);
}

void saque(S_conta *conta)
{
    float valor_saque;
    printf("\nDigite o valor que voce quer sacar: \n");
    scanf("%f", &valor_saque);

    if (valor_saque <= 0)
    {
        printf("Valor invalido.");
    }
    else if (valor_saque > conta->saldo)
    {
        printf("Saldo insuficiente.");
    }
    else
    {
        conta->saldo -= valor_saque;
    }
}

void deposito(S_conta *conta)
{
    float valor_deposito;
    printf("\nDigite o valor do deposito: \n");
    scanf("%f", &valor_deposito);
    conta->saldo += valor_deposito;
}

void avalia_credito(S_conta conta)
{
    // int apertura = conta.ano_abertura;
    if ((ANO - (conta.ano_abertura)) > 2)
    {
        printf("\nOperacao de credito autorizada! \n");
    }
    else
    {
        printf("\nOperacao de credito NAO AUTORIZADA!");
    }
}
