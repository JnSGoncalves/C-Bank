#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

int verificarCPF(const char cpf[]) {
    if (strlen(cpf) != 11) {
        printf("False\n");
        return 0;
    }
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            printf("False\n");
            return 0;
        }
    }
    printf("True\n");
    return 1;
}

int add_cliente(conta clientes[], int *pos) {
    printf("\n\nCadastro de novo Cliente\n");

    if (*pos >= Tamanho_clientes) {
        return Max_clientes_Erro;
    }

    char cpf[Max_CPF];
    printf("Digite seu CPF: ");
    fgets(cpf, Max_CPF, stdin);

    cpf[strcspn(cpf, "\n")] = '\0';

    if (!verificarCPF(cpf)) {
        printf("CPF inválido!\n");
        return CPF_invalido;
    }

    for (int i = 0; i < *pos; i++) {
        if (strcmp(cpf, clientes[i].cpf) == 0) {
            printf("CPF já cadastrado!\n");
            return CPF_cadastrado;
        }
    }
    strcpy(clientes[*pos].cpf, cpf);

    printf("Digite seu nome: ");
    fgets(clientes[*pos].nome, Max_string, stdin);
    clientes[*pos].nome[strcspn(clientes[*pos].nome, "\n")] = '\0';

    int verif;
    int tipo_conta;
    do {
        printf("Digite o tipo de conta que deseja (0. Comum/1. Plus): ");
        verif = scanf("%d", &tipo_conta);
        clearBuffer();
        if (verif != 1 || tipo_conta > 1 || tipo_conta < 0) {
            printf("Erro! Opção inválida\n");
        }
    } while (verif != 1 || tipo_conta > 1 || tipo_conta < 0);
    clientes[*pos].tipo_conta = tipo_conta;

    float deposito;
    do {
        printf("Digite o valor do depósito inicial: ");
        verif = scanf("%f", &deposito);
        clearBuffer();
        if (verif != 1 || deposito < 0 || (int)(deposito * 100) % 1 != 0) {
            printf("Valor inválido\n");
        }
    } while (verif != 1 || deposito < 0 || (int)(deposito * 100) % 1 != 0);
    clientes[*pos].saldo = deposito;

    printf("Digite a sua senha: ");
    fgets(clientes[*pos].senha, Max_senha, stdin);
    clientes[*pos].senha[strcspn(clientes[*pos].senha, "\n")] = '\0';

    printf("Cliente Cadastrado com sucesso!\n");
    printf("%s, %s, %d, %.2f, %s\n", clientes[*pos].cpf, clientes[*pos].nome, clientes[*pos].tipo_conta, clientes[*pos].saldo, clientes[*pos].senha);

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
