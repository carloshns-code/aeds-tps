#ifndef CONTA_BANCARIA_H
#define CONTA_BANCARIA_H

typedef struct
{
    int numero_conta;
    char nome_conta[50];
    int cpf[11];
    char tipo_conta;
    int ano_abertura;
    float saldo;
} S_conta; // Struct conta




void inicializacao_conta(S_conta *conta); // recebe um ponteiro para a struct onde sera cadastrado o conta
void imprimir(_contaS_conta conta);       // receb apenas uma copia da struct conta ja criada
void get_nome_tipo(S_conta conta);  // como eh obtencao, ele recebe somente uma copia ca struct
void set_nome_tipo(S_conta *conta); // como vai ter que setar, recebe um ponteiro para a struct
void saque(S_conta *conta);
void deposito(S_conta *conta);
void avalia_credito(S_conta conta);

#endif