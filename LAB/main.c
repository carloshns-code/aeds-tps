#include <stdio.h>
#include <string.h>
#include "cliente.h"

int main(void) {
    S_cliente cliente;
    int ano_atual = 2026;
    float valor;
    char novo_tipo;
    char novo_nome[50];

    inicializa_cliente(&cliente);

    inicializacao_conta(&cliente.conta);

    imprime_cliente(cliente);

    imprimir_conta(cliente.conta);

    printf("\nTipo atual da conta: %c\n", get_tipo(cliente.conta));

    printf("Digite um novo tipo para a conta: ");
    scanf(" %c", &novo_tipo);

    set_tipo(&cliente.conta, novo_tipo);

    printf("Digite o valor que deseja sacar: ");
    scanf("%f", &valor);

    saque(&cliente.conta, valor);

    printf("Digite o valor que deseja depositar: ");
    scanf("%f", &valor);

    deposito(&cliente.conta, valor);

    printf("\nSaldo atual: %.2f\n", get_saldo(cliente.conta));

    if (avalia_credito(cliente.conta, ano_atual)) {
        printf("Operacao de credito autorizada!\n");
    } else {
        printf("Operacao de credito NAO AUTORIZADA!\n");
    }

    getchar();

    printf("\nDigite um novo nome para o cliente: ");
    fgets(novo_nome, sizeof(novo_nome), stdin);

    novo_nome[strcspn(novo_nome, "\n")] = '\0';

    set_nome_cliente(&cliente, novo_nome);

    printf("\nNome atualizado: %s\n", get_nome(&cliente));
    printf("CPF cadastrado: %s\n", get_cpf(&cliente));

    return 0;
}