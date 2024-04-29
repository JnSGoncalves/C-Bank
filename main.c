#include <stdio.h>

int main(){
    printf("Banco - Quem Poupa Tem!\n");

    int opcao;
    do{
// 1. Novo cliente
// 2. Apaga cliente
// 3. Listar clientes
// 4. Débito
// 5. Depósito
// 6. Extrato
// 7. Transferência Entre Contas

        printf("\nMenu\n\n");

        printf("1. Novo cliente.\n");
        printf("2. Excluir conta.\n");
        printf("3. Listar clientes.\n");
        printf("4. Débito.\n");
        printf("5. Depósito.\n");
        printf("6. Extrato.\n");
        printf("7. Transferência entre contas.\n");

        printf("\nDigite o número da opreção desejada: ");
        scanf("%d", &opcao);
        
        switch (opcao){
            case 1:
                printf("Novo cliente\n");
                break;
            case 2:
                printf("Excluir conta\n");
                break;
            case 3:
                printf("Listar clientes.\n");
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
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    printf("Saindo...");
}