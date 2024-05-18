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

int getIndex_cpf(const conta clientes[], int *pos){
    char cpf[Max_CPF];
    fgets(cpf, Max_CPF, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    int index;
    for (index = 0; index < *pos; index++){
        if (strcmp(cpf, clientes[index].cpf) == 0){
            return index;
            break;
        }
    }
    return -1;
}

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
void deletar_conta(conta clientes[], int *pos) {
    char cpf[Max_CPF];
    printf("Digite o CPF da conta a ser excluída: ");
    fgets(cpf, Max_CPF, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';
    
    int index = -1;
    for (int i = 0; i < *pos; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("CPF não encontrado.\n");
        return;
    }

    for (int i = index; i < *pos - 1; i++) {
        clientes[i] = clientes[i + 1];
    }

    (*pos)--;
    printf("Conta com CPF %s deletada com sucesso.\n", cpf);
}

// 3. Listar clientes.
void listar_clientes(conta clientes[], const int *pos){
    printf("\n\nLista de Clientes\n");
    if (*pos == 0) {
        printf("Nenhum cliente cadastrado.\n");
    } else {
        for (int i = 0; i < *pos; i++) {
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
int debito(conta clientes[], int *pos){
    printf("\n\nDébito de valores.\n");

    printf("Digite seu CPF: ");
    int pos_cpf = getIndex_cpf(clientes, pos);
    if (pos_cpf == -1){
        return CPF_nao_cadastrado;
    }


    char senha[Max_senha];
    printf("Digite a sua senha: ");
    fgets(senha, Max_senha, stdin);

    if (strcmp(senha, clientes[pos_cpf].senha) != 0){
        return Senha_incorreta;
    };

    float valor;
    printf("Digite o valor que deseja debitar: ");
    int verif = scanf("%f", &valor);
    clearBuffer();
    if (verif != 1 || valor < 0 || (int)(valor * 1000) % 10 != 0){
        return Valor_invalido;
    }

    if(clientes[pos_cpf].tipo_conta == comum){
        if (clientes[pos_cpf].saldo - valor <= Limite_Comum){
            return Saldo_negativo_excedido;
        }else{
            clientes[pos_cpf].saldo -= valor + (valor * Taxa_Comum);
            printf("Débito realizado com sucesso!\n");
            return OK;
        }
    }else{
        if (clientes[pos_cpf].saldo - valor <= Limite_Plus){
            return Saldo_negativo_excedido;
        }else{
            clientes[pos_cpf].saldo -= valor + (valor * Taxa_Plus);
            printf("Débito realizado com sucesso!\n");
            return OK;
        }
    }
}

// 5. Depósito.
int deposito(conta clientes[], int *pos){
    printf("\n\nDepósito de valores.\n");

    printf("Digite seu CPF: ");
    int pos_cpf = getIndex_cpf(clientes, pos);
    if (pos_cpf == -1){
        return CPF_nao_cadastrado;
    }


    float valor;
    printf("Digite o valor que deseja depositar: ");
    int verif = scanf("%f", &valor);
    clearBuffer();
    if (verif != 1 || valor < 0 || (int)(valor * 1000) % 10 != 0){
        return Valor_invalido;
    }

    clientes[pos_cpf].saldo += valor;
    printf("Depósito realizado com sucesso!\n");
    return OK;
}

// 6. Extrato.


// 7. Transferência entre contas
int transferencia(conta clientes[], int *pos){
    printf("\n\nTransferência de valores.\n");


    printf("Digite seu CPF: ");
    int pos_origem = getIndex_cpf(clientes, pos);
    if (pos_origem == -1){
        return CPF_nao_cadastrado;
    }


    char senha[Max_senha];
    printf("Digite a sua senha: ");
    fgets(senha, Max_senha, stdin);

    if (strcmp(senha, clientes[pos_origem].senha) != 0){
        return Senha_incorreta;
    };

    
    printf("Digite o CPF cadastrado na conta de destino: ");
    int pos_destino = getIndex_cpf(clientes, pos);
    if (pos_destino == -1){
        return CPF_nao_cadastrado;
    }

    float valor;
    printf("Digite o valor que deseja transferir para %s: ", clientes[pos_destino].nome);
    int verif = scanf("%f", &valor);
    clearBuffer();
    if (verif != 1 || valor < 0 || (int)(valor * 1000) % 10 != 0){
        return Valor_invalido;
    }

    if (clientes[pos_origem].tipo_conta == comum){
        if ((clientes[pos_origem].saldo - valor) <= Limite_Comum){
            return Saldo_negativo_excedido;
        }else{
            int verif;
            char confirm;
            do{
                printf("Deseja confirmar a transferência de R$ %.2f - Taxa de R$ %.2f, para %s  (s/n): ", valor, (valor * Taxa_Comum), clientes[pos_destino].nome);
                verif = scanf("%s", &confirm);
                clearBuffer();
                if (verif != 1 || (confirm != 's' && confirm != 'n' && confirm != 'S' && confirm != 'N'))
                    printf("Erro! Opção inválida\n");
            }while (confirm != 's' && confirm != 'n' && confirm != 'S' && confirm != 'N');
            if (verif != 1 || confirm == 'n' || confirm == 'N')
                return Operacao_cancelada;

            clientes[pos_origem].saldo -= valor;
            valor -= valor * Taxa_Comum;
            clientes[pos_destino].saldo += valor;
        }
    }else{
        if ((clientes[pos_origem].saldo - valor) <= Limite_Plus){
            return Saldo_negativo_excedido;
        }else{
            int verif;
            char confirm;
            do{
                printf("Deseja confirmar a transferência de R$ %.2f - Taxa de R$ %.2f, para %s  (s/n): ", valor, (valor * Taxa_Plus), clientes[pos_destino].nome);
                verif = scanf("%s", &confirm);
                clearBuffer();
                if (verif != 1 || (confirm != 's' && confirm != 'n' && confirm != 'S' && confirm != 'N'))
                    printf("Erro! Opção inválida\n");
            }while (confirm != 's' && confirm != 'n' && confirm != 'S' && confirm != 'N');
            if (verif != 1 || confirm == 'n' || confirm == 'N')
                return Operacao_cancelada;

            clientes[pos_origem].saldo -= valor;
            valor -= valor * Taxa_Plus;
            clientes[pos_destino].saldo += valor;
        }
    }
}



void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}