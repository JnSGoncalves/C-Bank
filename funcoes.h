#define Tamanho_clientes 1000
#define Max_senha 25
#define Max_CPF 12 // 11 digitos mais o '\0'
#define Max_string 255

typedef enum {comum, plus} Tipo_conta;
enum {OK, Max_clientes_Erro, CPF_cadastrado, CPF_invalido};

typedef struct {
    char cpf[Max_CPF];
    char nome[255];
    Tipo_conta tipo_conta; // 0 = Conta comum; 1 = Conta plus
    float saldo;
    char senha[Max_senha];
} conta;

int add_cliente(conta clientes[], int *pos);
void clearBuffer();
void listar_clientes(conta clientes[], int pos); // Declaration added

