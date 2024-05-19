# Quem Poupa Tem
Desenvolvimento de uma interface de um banco com as seguintes funcionalidades: criação de uma nova conta, exclusão de uma conta existente, listagem de todas as conta, débito, depósito, extrato, transferência, salvamento dos dados em um arquivo binário e carregamento dos dados de um arquivo binário.

Criação de Conta: Ao selecionar a opção 1, o programa solicitará ao usuário que insira as informações do contato a ser criado, incluindo nome, cpf, senha e o valor do depósito inicial. Estas informações serão então armazenadas.

Exclusão de Contatos: Ao escolher a opção 2, o programa pedirá ao usuário que insira cpf da conta a ser removida, e em seguida apagará sua conta.

Listagem de Contas: Se a opção 3 for selecionada, o programa exibirá todos os contas atualmente salvas. Caso não haja nenhuma conta registrada, o programa retornará ao menu principal.

Débito: A função de débito permite ao usuário retirar uma quantia de uma conta existente. O programa solicitará o CPF e a senha da conta e a quantia a ser debitada. Em seguida, verificará se há saldo suficiente e, caso positivo, deduzirá o valor do saldo da conta, dependendo de que tipo de conta ela é(comum/plus).

Depósito: A função de depósito permite ao usuário adicionar uma quantia a uma conta existente. O programa solicitará o CPF da conta e a quantia a ser depositada. Em seguida, atualizará o saldo da conta com o valor informado.

Extrato: A função de extrato exibe todas as transações realizadas em uma conta específica. O programa solicitará o CPF e exibirá todas as transações (débitos e depósitos) realizadas nessa conta, bem como o saldo atual.

Transferência: A função de transferência permite ao usuário transferir uma quantia de uma conta para outra. O programa solicitará o CPF e a senha da conta de origem, o CPF da conta de destino e a quantia a ser transferida. Em seguida, verificará se há saldo suficiente na conta de origem e, caso positivo, deduzirá o valor do saldo da conta de origem e adicionará à conta de destino.

Salvamento em Arquivo Binário: Ao encerrar o programa, todos os dados mantidos durante a execução do programa serão armazenados em um arquivo binário.

Carregamento de Arquivo Binário: Ao iniciar o programa, todos os dados previamente salvos, serão carregados de um arquivo binário.

Para compilar o programa, o usuário deve instalar o GNU Compiler Collection, abrir a pasta do projeto em sua IDE preferida e utilizar o comando "gcc *.c" no terminal do seu computador.

Para executar o programa, o usuário deve usar o comando "./a.out" (Linux) ou ".\a.exe" (Windows) dentro da IDE com o projeto aberto e já compilado.