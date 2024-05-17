#include <stdio.h>
#include "funcoes.h"

int main() {
    printf("Banco - Quem Poupa Tem!\n");

    conta clientes[Tamanho_clientes];
    int pos = 0;

    int opcao;
    do {
        printf("\nMenu\n\n");

        printf("1. Novo cliente.\n");
        printf("2. Excluir conta.\n");
        printf("3. Listar clientes.\n");
        printf("4. Débito.\n");
        printf("5. Depósito.\n");
        printf("6. Extrato.\n");
        printf("7. Transferência entre contas.\n");
        printf("0. Sair\n");

        printf("\nDigite o número da operação desejada: ");
        scanf("%d", &opcao);
        clearBuffer();

        switch (opcao) {
            case 1:
                add_cliente(clientes, &pos);
                break;
            case 2: {
                char cpf[Max_CPF];
                printf("Digite o CPF da conta a ser excluída: ");
                fgets(cpf, Max_CPF, stdin);
                cpf[strcspn(cpf, "\n")] = '\0';
                deletar_conta(clientes, &pos, cpf);
                break;
            }
            case 3:
                listar_clientes(clientes, pos);
                break;
            case 4:
                printf("Débito.\n");
                break;
            case 5:
                printf("Depósito.\n");
                break;
            case 6:
                printf("Extrato.\n");
                break;
            case 7:
                printf("Transferência entre contas.\n");
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    printf("Saindo...\n");
    return 0;
}
