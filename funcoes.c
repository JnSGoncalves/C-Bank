#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

// // Teste de verificação do tamanho do cpf digitado para não ser menor que 11 digitos e ser composto só de digitos
// int verificarCPF(const char cpf[]){
//     int i;
//     if (strlen(cpf) != 11)
//         printf("False");
//         return 0;
//     for (i = 0; i < 11; i++) {
//         if (!isdigit(cpf[i]))
//             printf("False 2");
//             return 0;
//     }
//     printf("True");
//     return 1;
// }

int add_cliente(conta clientes[], int *pos){
    printf("\n\nCadastro de novo Cliente\n");

    if (*pos > Tamanho_clientes){
        return Max_clientes_Erro;
    }

    char cpf[Max_CPF];
    printf("Digite seu CPF: ");
    fgets(cpf, Max_CPF, stdin);

    cpf[strcspn(cpf, "\n")] = '\0';

    for (int i = 0; i < Tamanho_clientes; i++){
        if (strcmp(cpf, clientes[i].cpf) == 0)
            return CPF_cadastrado;
    }
    strcpy(clientes[*pos].cpf, cpf);

    clearBuffer();
    
    printf("Digite seu nome: ");
    fgets(clientes[*pos].nome, Max_string, stdin);
    clientes[*pos].nome[strcspn(clientes[*pos].nome, "\n")] = '\0';


    int verif;
    int tipo_conta;
    do{
        printf("Digite o tipo de conta que deseja (0. Comum/1. Plus): ");
        verif = scanf("%d", &tipo_conta);
        clearBuffer();
        if (verif != 1 || tipo_conta > 1 || tipo_conta < 0)
            printf("Erro! Opção inválida\n");
    }while (verif != 1 || tipo_conta > 1 || tipo_conta < 0);
    clientes[*pos].tipo_conta = tipo_conta;


    verif = 0;
    float deposito;
    do{
        printf("Digite o valor do depósito inicial: ");
        verif = scanf("%f", &deposito);
        clearBuffer();
        if (verif != 1 || deposito < 0 || (int)(deposito * 1000) % 10 != 0)
            printf("Valor inválido\n");
    }while (verif != 1 || deposito < 0 || (int)(deposito * 1000) % 10 != 0); // Impede que o valor seja negativo e que contenha mais de 2 casas decimais
    clientes[*pos].saldo = deposito;


    printf("Digite a sua senha: ");
    fgets(clientes[*pos].senha, Max_senha, stdin);


    printf("Cliente Cadatrado com sucesso!\n");
    printf("%s, %s, %d, %.2f, %s", clientes[*pos].cpf, clientes[*pos].nome, clientes[*pos].tipo_conta, clientes[*pos].saldo, clientes[*pos].senha);

    *pos = *pos + 1;
    return OK;
}

void listar_clientes(conta clientes[], int pos) {
    printf("\n\nLista de Clientes\n");
    if (pos == 0) {
        printf("Nenhum cliente cadastrado.\n");
    } else {
        for (int i = 0; i < pos; i++) {
            printf("Cliente %d:\n", i + 1);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Tipo de Conta: %s\n", clientes[i].tipo_conta == comum ? "Comum" : "Plus");
            printf("Saldo: %.2f\n", clientes[i].saldo);
            printf("Senha: %s\n", clientes[i].senha);
            printf("\n");
        }
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
