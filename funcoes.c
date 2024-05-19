#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"
#include <time.h>

// Teste de verificação do tamanho do cpf digitado para não ser menor que 11 digitos e ser composto só de digitos
int verificarCPF(const char cpf[]){
    int i;
    if (strlen(cpf) != 11)
        return CPF_invalido;
    for (i = 0; i < 11; i++) {
        if (!isdigit(cpf[i]))
            return CPF_invalido;
    }
    return OK;
}

int getIndex_cpf(const conta clientes[], int *pos){
    char cpf[Max_CPF];
    fgets(cpf, Max_CPF, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';
    if (verificarCPF(cpf) != OK)
        return -1;

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
    if (verificarCPF(cpf) != OK)
        return CPF_invalido;

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
    clientes[*pos].senha[strcspn(clientes[*pos].senha, "\n")] = '\0';


    *pos = *pos + 1;

    printf("\nCliente Cadatrado com sucesso!\n");
    return OK;
}

// 2. Excluir conta.
int deletar_conta(conta clientes[], int *pos) {
    char cpf[Max_CPF];
    printf("Digite o CPF da conta a ser excluída: ");
    int index = getIndex_cpf(clientes, pos);
    if (index == -1) {
        return CPF_nao_cadastrado;
    }

    char senha[Max_senha];
    printf("Digite a sua senha: ");
    fgets(senha, Max_senha, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    if (strcmp(senha, clientes[index].senha) != 0){
        return Senha_incorreta;
    };

    for (int i = index; i < *pos - 1; i++) {
        clientes[i] = clientes[i + 1];
    }

    (*pos)--;
    printf("Conta com CPF %s deletada com sucesso.\n", cpf);
}

// 3. Listar clientes.
int listar_clientes(conta clientes[], const int *pos){
    printf("\n\nLista de Clientes\n\n");
    if (*pos == 0) {
        printf("\nNenhum cliente cadastrado.\n");
    } else {
        for (int i = 0; i < *pos; i++) {
            printf("Cliente %d:\n", i + 1);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Tipo de Conta: %s\n", clientes[i].tipo_conta == comum ? "Comum" : "Plus");
            printf("Saldo: %.2f\n", clientes[i].saldo);
            printf("\n");
        }
    }
    return OK;
}

// 4. Débito.
int debito(conta clientes[], int *pos){
    printf("\n\nDébito de valores.\n");

    printf("\nDigite seu CPF: ");
    int pos_cpf = getIndex_cpf(clientes, pos);
    if (pos_cpf == -1){
        return CPF_nao_cadastrado;
    }


    char senha[Max_senha];
    printf("Digite a sua senha: ");
    fgets(senha, Max_senha, stdin);
    senha[strcspn(senha, "\n")] = '\0';

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

    float taxa;
    if(clientes[pos_cpf].tipo_conta == comum){
        if (clientes[pos_cpf].saldo - (valor + (valor * Taxa_Comum)) < Limite_Comum){
            return Saldo_negativo_excedido;
        }else{
            taxa = valor * Taxa_Comum;
            clientes[pos_cpf].saldo -= valor + taxa;
        }
    }else{
        if (clientes[pos_cpf].saldo - (valor + (valor * Taxa_Plus)) < Limite_Plus){
            return Saldo_negativo_excedido;
        }else{
            taxa = valor * Taxa_Plus;
            clientes[pos_cpf].saldo -= valor + taxa;
        }
    }

    novo_extrato(clientes, pos_cpf, valor, Debito, '-', taxa);
    printf("Débito realizado com sucesso!\n");

    return OK;
}

// 5. Depósito.
int deposito(conta clientes[], int *pos){
    printf("\n\nDepósito de valores.\n");

    printf("Digite o CPF cadastrado na conta para depósito: ");
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

    novo_extrato(clientes, pos_cpf, valor, Deposito, '+', 0);
    printf("Depósito realizado com sucesso!\n");

    return OK;
}

// 6. Extrato.
int novo_extrato(conta clientes[], int pos_cpf, float valor, Operacoes tipo_operacao, char operador, float taxa){
    // Se a posição for menor que 100 ele adiciona ao final da posição
    if (clientes[pos_cpf].pos_extrato == -1)
        clientes[pos_cpf].pos_extrato = 0;
    if (clientes[pos_cpf].pos_extrato < Max_extrato){

        clientes[pos_cpf].extrato[clientes[pos_cpf].pos_extrato].valor = valor;
        clientes[pos_cpf].extrato[clientes[pos_cpf].pos_extrato].taxa = taxa;
        clientes[pos_cpf].extrato[clientes[pos_cpf].pos_extrato].tipo_operacao = tipo_operacao;
        clientes[pos_cpf].extrato[clientes[pos_cpf].pos_extrato].operador = operador;

        // a posição vira 100 quando está cheio
        clientes[pos_cpf].pos_extrato += 1;
    }else{ 
        // Se estiver cheio, ele exclui o mais antigo e adiciona na ultima posição
        for(int i = 0; i < clientes[pos_cpf].pos_extrato; i++){
            clientes[pos_cpf].extrato[i] = clientes[pos_cpf].extrato[i+1];
        }
        // posição fica constante em 100, mas o indice final do array é 99 
        clientes[pos_cpf].extrato[clientes[pos_cpf].pos_extrato - 1].valor = valor;
        clientes[pos_cpf].extrato[clientes[pos_cpf].pos_extrato - 1].taxa = taxa;
        clientes[pos_cpf].extrato[clientes[pos_cpf].pos_extrato - 1].tipo_operacao = tipo_operacao;
        clientes[pos_cpf].extrato[clientes[pos_cpf].pos_extrato - 1].operador = operador;
    };
};

int ver_extrato(conta clientes[], int *pos){
    printf("\nExtrato.\n\n");

    printf("Digite seu CPF: ");
    int pos_cpf = getIndex_cpf(clientes, pos);
    if (pos_cpf == -1){
        return CPF_nao_cadastrado;
    }


    char senha[Max_senha];
    printf("Digite a sua senha: ");
    fgets(senha, Max_senha, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    if (strcmp(senha, clientes[pos_cpf].senha) != 0){
        return Senha_incorreta;
    }

    if (clientes[pos_cpf].pos_extrato == -1){
        return Sem_extrato;
    }

    char nome_arquivo[Max_CPF + 10];
    sprintf(nome_arquivo, "%s.txt", clientes[pos_cpf].cpf);
    FILE *arquivo_extrato = fopen(nome_arquivo, "w");
    if (arquivo_extrato == NULL) {
        return Erro_abrir;
    }

    fprintf(arquivo_extrato, "Extrato:\n");
    fprintf(arquivo_extrato, "Nome: %s\n", clientes[pos_cpf].nome);
    fprintf(arquivo_extrato, "CPF: %s\n", clientes[pos_cpf].cpf);
    fprintf(arquivo_extrato, "Tipo de conta: %s\n", clientes[pos_cpf].tipo_conta == comum ? "Comum" : "Plus");
    fprintf(arquivo_extrato, "Saldo atual: %.2f\n\n", clientes[pos_cpf].saldo);
    fprintf(arquivo_extrato, "Transações (Mais recente abaixo):\n");

    for (int i = 0; i < clientes[pos_cpf].pos_extrato; i++) {
        switch (clientes[pos_cpf].extrato[i].tipo_operacao){
            case Debito:
                fprintf(arquivo_extrato, "Operação: Débito\n");  
                break;
            case Transferencia:
                fprintf(arquivo_extrato, "Operação: Transferência\n"); 
                break;
            case Deposito:
                fprintf(arquivo_extrato, "Operação: Depósito\n");       
        }
        fprintf(arquivo_extrato, "Valor: %c R$ %.2f\n", clientes[pos_cpf].extrato[i].operador, clientes[pos_cpf].extrato[i].valor);
        fprintf(arquivo_extrato, "Taxa: - R$ %.2f\n", clientes[pos_cpf].extrato[i].taxa);
        fprintf(arquivo_extrato, "\n");
    }

    fclose(arquivo_extrato);
    printf("Extrato gerado no arquivo \"%s\"\n", nome_arquivo);

    return OK;
}


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
    senha[strcspn(senha, "\n")] = '\0';

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

    float taxa;
    if (clientes[pos_origem].tipo_conta == comum){
        if ((clientes[pos_origem].saldo - (valor + (valor * Taxa_Comum))) < Limite_Comum){
            return Saldo_negativo_excedido;
        }else{
            int verif;
            char confirm;
            do{
                printf("Deseja confirmar a transferência de R$ %.2f (Taxa: R$ %.2f) para %s  (s/n): ", valor, (valor * Taxa_Comum), clientes[pos_destino].nome);
                verif = scanf("%s", &confirm);
                clearBuffer();
                if (verif != 1 || (confirm != 's' && confirm != 'n' && confirm != 'S' && confirm != 'N'))
                    printf("Erro! Opção inválida\n");
            }while (confirm != 's' && confirm != 'n' && confirm != 'S' && confirm != 'N');
            if (verif != 1 || confirm == 'n' || confirm == 'N')
                return Operacao_cancelada;

            taxa = valor * Taxa_Comum;
            clientes[pos_origem].saldo -= valor + taxa;
            clientes[pos_destino].saldo += valor;
        }
    }else{
        if ((clientes[pos_origem].saldo - (valor + (valor * Taxa_Plus))) < Limite_Plus){
            return Saldo_negativo_excedido;
        }else{
            int verif;
            char confirm;
            do{
                printf("Deseja confirmar a transferência de R$ %.2f (Taxa: R$ %.2f) para %s  (s/n): ", valor, (valor * Taxa_Plus), clientes[pos_destino].nome);
                verif = scanf("%s", &confirm);
                clearBuffer();
                if (verif != 1 || (confirm != 's' && confirm != 'n' && confirm != 'S' && confirm != 'N'))
                    printf("Erro! Opção inválida\n");
            }while (confirm != 's' && confirm != 'n' && confirm != 'S' && confirm != 'N');
            if (verif != 1 || confirm == 'n' || confirm == 'N')
                return Operacao_cancelada;

            taxa = valor * Taxa_Plus;
            clientes[pos_origem].saldo -= valor + taxa;
            clientes[pos_destino].saldo += valor;
        }
    }

    novo_extrato(clientes, pos_origem, valor, Transferencia, '-', taxa);
    novo_extrato(clientes, pos_destino, valor, Transferencia, '+', 0);

    printf("Tranferência realizada com sucesso!\n");
    
    return OK;
}

// Salvar em binário
int salvar(conta clientes[], int *pos){
    FILE *f = fopen("clientes.bin", "wb");
    if (f == NULL){
        return Erro_abrir;
    }

    for (int i = 0; i < *pos; i++) {
        if (fwrite(&clientes[i], sizeof(conta), 1, f) != 1) {
            fclose(f);
            return Erro_escrever;
        }
    }

    fclose(f);
    return OK;
}

// Carregar em binário
int carregar(conta clientes[], int *pos){
    FILE *f = fopen("clientes.bin", "rb");
    if (f == NULL) {
        return Erro_abrir;
    }

    conta cliente;

	int pos_load = 0;
    while (fread(&cliente, sizeof(conta), 1, f) == 1) {
        clientes[pos_load] = cliente;
        (pos_load)++;
    }

	*pos = pos_load;

    fclose(f);
    return OK;
}

void trat_erros(int erro){
    /* 
    Erros {OK, Max_clientes_Erro, CPF_cadastrado, CPF_invalido, CPF_nao_cadastrado, Senha_incorreta, 
     Valor_invalido, Saldo_negativo_excedido, Operacao_cancelada, Erro_abrir, Erro_escrever, Sem_extrato};
    */
    if (erro == OK){
        return;
    }else if (erro == Max_clientes_Erro){
        printf("Número máximo de clientes alcançado.\n");
    }else if (erro == CPF_cadastrado){
        printf("CPF já cadastrado\n");
    }else if (erro == CPF_invalido){
        printf("CPF inválido\n");
    }else if (erro == CPF_nao_cadastrado){
        printf("CPF não encontrado entre os clientes\n");
    }else if (erro == Senha_incorreta){
        printf("Senha incorreta!\n");
    }else if (erro == Valor_invalido){
        printf("Valor inválido.\n");
    }else if (erro == Saldo_negativo_excedido){
        printf("Essa operação excede o valor negativo máximo de sua conta.\n");
    }else if (erro == Operacao_cancelada){
        printf("Operação cancelada.\n");
    }else if (erro == Erro_abrir){
        printf("Erro ao abrir arquivo.\n");
    }else if (erro == Erro_escrever){
        printf("Erro ao escrever no arquivo.\n");
    }else if (erro == Sem_extrato){
        printf("A conta não possui nenhuma transação salva no histórico.\n");
    }
}


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}