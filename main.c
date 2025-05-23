#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 10
#define MAX_PRODUTOS 500
typedef struct {
    char nome[50];
    char telefone[20];
    char endereco[100];
    char email[50];
} Cliente;

typedef struct {
    char nome[50];
    char codigo[10];
}produto;

Cliente clientes[MAX_CLIENTES];
int qtd_clientes_cadastrados = 0;

produto produtos[MAX_PRODUTOS];
int qtd_prod_cadastrados = 0;

void insere_cliente() {
    char resposta[10];

    if (qtd_clientes_cadastrados >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
        return;
    }

    Cliente novo;

    printf("Nome do cliente: ");
    scanf(" %[^\n]", novo.nome);  
    printf("Telefone: ");
    scanf(" %[^\n]", novo.telefone);
    printf("Endereco: ");
    scanf(" %[^\n]", novo.endereco);
    printf("Email: ");
    scanf(" %[^\n]", novo.email);

    clientes[qtd_clientes_cadastrados++] = novo;

    printf("Deseja cadastrar mais um cliente? (sim/nao): ");
    scanf("%s", resposta);

    if (strcmp(resposta, "sim") == 0) {
        insere_cliente(); 
    } else {
        printf("*** Cadastro finalizado ***\n");
    }
}

void listar_clientes() {
    if (qtd_clientes_cadastrados == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Clientes ---\n");
    for (int i = 0; i < qtd_clientes_cadastrados; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Endereco: %s\n", clientes[i].endereco);
        printf("Email: %s\n", clientes[i].email);
        printf("-------------------------\n");
    }
}

void insere_venda(){}

void insere_produto(){
char resposta[10];

    if (qtd_prod_cadastrados >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    produto novo;

    printf("Nome do produto: ");
    scanf(" %[^\n]", novo.nome);  
    printf("codigo: ");
    scanf(" %[^\n]", novo.codigo);

    
    produtos[qtd_prod_cadastrados++] = novo;

    printf("Deseja cadastrar mais um produto? (sim/nao): ");
    scanf("%s", resposta);

    if (strcmp(resposta, "sim") == 0) {
        insere_produto(); 
    } else {
        printf("*** Cadastro finalizado ***\n");
    }
}
void excluir_clientes(){
    char cliente_exclusao[50];
    int encontrado = 0;

    if (qtd_clientes_cadastrados == 0) {
        printf("Nenhum cliente para excluir.\n");
        return;
    }

    listar_clientes();

    printf("Digite o nome do cliente a ser excluído: ");
    scanf(" %[^\n]", cliente_exclusao);

    for (int i = 0; i < qtd_clientes_cadastrados; i++) {
        if (strcmp(cliente_exclusao, clientes[i].nome) == 0) {
            for (int j = i; j < qtd_clientes_cadastrados - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            qtd_clientes_cadastrados--;
            encontrado = 1;
            printf("Cliente excluído com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente não encontrado.\n");
    }
}


}
 
}


int main() {
    int escolha;
    do {
        printf("\n*** Menu ***\n");
        printf("0 - Sair\n");
        printf("1 - Inserir Cliente\n");
        printf("2 - Listar Clientes\n");
        printf("3 - insere Venda\n");
        printf("4 - insere produto\n");
        printf("5 - Excluir clientes");

        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                insere_cliente();
                break;
            case 2:
                listar_clientes();
                break;
            case 3:
                insere_venda();
                break;
            case 4:
                insere_produto();
                break;
            case 5:
                excluir_clientes();
                break;
            case 0:
            
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (escolha != 0);

    return 0;
}
