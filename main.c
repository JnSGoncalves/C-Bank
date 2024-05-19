#include <stdio.h>
#include "funcoes.h"

int main() {
    printf("Banco - Quem Poupa Tem!\n");

    conta clientes[Tamanho_clientes];
    // Define o padrão do pos_extrato como -1 para verificar se possui extrato cadastrado
    for (int i = 0; i < Tamanho_clientes; i++){
        clientes[i].pos_extrato = -1;
    }
    int pos;
    int erro = carregar(clientes, &pos);
    if (erro == Erro_abrir){
        pos = 0;
    }

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
                erro = add_cliente(clientes, &pos);
                break;
            case 2: {
                erro = deletar_conta(clientes, &pos);
                break;
            }
            case 3:
                erro = listar_clientes(clientes, &pos);
                break;
            case 4:
                erro = debito(clientes, &pos);
                break;
            case 5:
                erro = deposito(clientes, &pos);
                break;
            case 6:
                erro = ver_extrato(clientes, &pos);
                break;
            case 7:
                erro = transferencia(clientes, &pos);
                break;
            case 0:
                erro = salvar(clientes, &pos);
                break;
            default:
                printf("Opção inválida!\n");
        }
        trat_erros(erro);
    } while (opcao != 0);

    printf("Saindo...\n");
    return 0;
}
