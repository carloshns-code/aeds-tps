#include "contaBancaria.h"
#include "cliente.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    S_conta conta; // dei o nome conta para minha struct
    S_cliente cliente; //dei o nome clietne para minha struct

    inicializacao_conta(&conta); // recebe um ponteiro para a struct onde sera cadastrado o conta
    imprimir_conta(conta);       // receb apenas uma copia da struct conta ja criada
    get_tipo(conta);  // como eh obtencao, ele recebe somente uma copia ca struct
    set_tipo(&conta); // como vai ter que setar, recebe um ponteiro para a struct
    saque(&conta);
    deposito(&conta);
    avalia_credito(conta);

    char cliente_nomenovo[50];
    ptintf("\nDigite o novo nome para o cliente: \n");
    scanf(&cliente_nomenovo);
    set_nome_cliente(&cliente, cliente_nomenovo[]);

    return 0;
}