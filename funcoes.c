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

// 1. Novo cliente.
int add_cliente(conta clientes[], int *pos){
    printf("\n\nCadastro de novo Cliente\n");

    if (*pos > Tamanho_clientes){
        return Max_clientes_Erro;
    }

    char cpf[Max_CPF];
    printf("Digite seu CPF: ");
    fgets(cpf, Max_CPF, stdin);

    cpf[strcspn(cpf, "\n")] = '\0';

    for (int i = 0; i < *pos; i++){
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

// 2. Excluir conta.


// 3. Listar clientes.
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

// 4. Débito.


// 5. Depósito.


// 6. Extrato.


// 7. Transferência entre contas
int transferencia(conta clientes[], int *pos){
    printf("\n\nTransferência de valores.\n");


    char cpf_origem[Max_CPF];
    printf("Digite seu CPF: ");
    fgets(cpf_origem, Max_CPF, stdin);

    cpf_origem[strcspn(cpf_origem, "\n")] = '\0';
    int pos_origem;
    int verifi;
    for (pos_origem = 0; pos_origem < *pos; pos_origem++){
        if (strcmp(cpf_origem, clientes[pos_origem].cpf) == 0){
            int verifi = 1;
            break;
        }
    }
    if (verifi != 1)
        return CPF_nao_cadastrado;


    char senha[Max_senha];
    printf("Digite a sua senha: ");
    fgets(senha, Max_senha, stdin);

    if (strcmp(senha, clientes[pos_origem].senha) != 0){
        return Senha_incorreta;
    };


    char cpf_destino[Max_CPF];
    printf("Digite o CPF cadastrado na conta de destino: ");
    fgets(cpf_destino, Max_CPF, stdin);

    cpf_destino[strcspn(cpf_destino, "\n")] = '\0';
    int pos_destino;
    verifi = 0;
    for (pos_destino = 0; pos_destino < *pos; pos_destino++){
        if (strcmp(pos_destino, clientes[pos_destino].cpf) == 0){
            int verifi = 1;
            break;
        }
    }
    if (verifi != 1)
        return CPF_nao_cadastrado;

    // Criar uma função para procurar a posição de um CPF digitado
    // Será usado muitas vezes durante o programa
}


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}