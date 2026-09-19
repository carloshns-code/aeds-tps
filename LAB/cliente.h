#ifndef CLIENTE_H
#define CLIENTE_H

#include "clienteBancaria.h"

typedef struct {
    char nome_cliente[50];
    char cpf[12];
    contaBancaria conta; //struct aninhada com uma struct de outra TAD 
} S_cliente;

void inicializa_cliente(S_cliente *cliente); // recebe um ponteiro para a struct onde sera cadastrado o cliente
void imprime_cliente(S_cliente cliente);       // receb apenas uma copia da struct cliente ja criada
//void get_nome_tipo(S_cliente cliente);  // como eh obtencao, ele recebe somente uma copia ca struct
//void set_nome_tipo(S_cliente *cliente); // como vai ter que setar, recebe um ponteiro para a struct
//void saque(S_cliente *cliente);
//void deposito(S_cliente *cliente);
//void avalia_credito(S_cliente cliente);
void set_nome_cliente(S_cliente *cliente, char* nome);
void set_cpf_cliente(S_cliente *cliente, char* cpf);
char* get_nome(S_cliente* cliente);
char* get_cpf(S_cliente* cliente);






#endif