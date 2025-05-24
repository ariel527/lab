#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 10
#define MAX_PRODUTOS 500
#define MAX_VENDAS 100
#define MAX_ITENS_VENDA 10

typedef struct {
    int id;
    char nome[50];
    char telefone[20];
    char endereco[100];
    char email[50];
} Cliente;

typedef struct {
    int id;
    char nome[50];
    char codigo[10];
    float preco;
} Produto;

typedef struct {
    int id_produto;
    int quantidade;
} ProdutoVenda;

typedef struct {
    int id;
    int id_cliente;
    ProdutoVenda itens[MAX_ITENS_VENDA];
    int qtd_itens;
    float valor_total;
} Venda;

Cliente clientes[MAX_CLIENTES];
int qtd_clientes = 0;

Produto produtos[MAX_PRODUTOS];
int qtd_produtos = 0;

Venda vendas[MAX_VENDAS];
int qtd_vendas = 0;

void inserir_cliente() {
    if (qtd_clientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
        return;
    }

    Cliente novo;
    novo.id = qtd_clientes + 1;

    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Telefone: ");
    scanf(" %[^\n]", novo.telefone);
    printf("Endereco: ");
    scanf(" %[^\n]", novo.endereco);
    printf("Email: ");
    scanf(" %[^\n]", novo.email);

    clientes[qtd_clientes++] = novo;
    printf("Cliente cadastrado com sucesso!\n");
}

void listar_clientes() {
    if (qtd_clientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtd_clientes; i++) {
        Cliente c = clientes[i];
        printf("ID: %d\nNome: %s\nTelefone: %s\nEndereco: %s\nEmail: %s\n\n",
               c.id, c.nome, c.telefone, c.endereco, c.email);
    }
}

void inserir_produto() {
    if (qtd_produtos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    Produto novo;
    novo.id = qtd_produtos + 1;

    printf("Nome do produto: ");
    scanf(" %[^\n]", novo.nome);
    printf("Codigo: ");
    scanf(" %[^\n]", novo.codigo);
    printf("Preco (R$): ");
    scanf("%f", &novo.preco);

    produtos[qtd_produtos++] = novo;
    printf("Produto cadastrado com sucesso!\n");
}

void listar_produtos() {
    if (qtd_produtos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtd_produtos; i++) {
        Produto p = produtos[i];
        printf("ID: %d\nNome: %s\nCodigo: %s\nPreco: R$ %.2f\n\n", p.id, p.nome, p.codigo, p.preco);
    }
}

Produto* buscar_produto_por_id(int id) {
    for (int i = 0; i < qtd_produtos; i++) {
        if (produtos[i].id == id) {
            return &produtos[i];
        }
    }
    return NULL;
}

void inserir_venda() {
    if (qtd_clientes == 0 || qtd_produtos == 0) {
        printf("Necessário pelo menos um cliente e um produto cadastrados.\n");
        return;
    }

    Venda nova;
    nova.id = qtd_vendas + 1;
    nova.qtd_itens = 0;
    nova.valor_total = 0.0;

    listar_clientes();
    printf("ID do cliente: ");
    scanf("%d", &nova.id_cliente);

    int continuar = 1;
    while (continuar && nova.qtd_itens < MAX_ITENS_VENDA) {
        listar_produtos();
        ProdutoVenda pv;
        printf("ID do produto: ");
        scanf("%d", &pv.id_produto);
        printf("Quantidade: ");
        scanf("%d", &pv.quantidade);

        Produto* prod = buscar_produto_por_id(pv.id_produto);
        if (prod) {
            nova.valor_total += prod->preco * pv.quantidade;
            nova.itens[nova.qtd_itens++] = pv;
        } else {
            printf("Produto não encontrado.\n");
        }

        printf("Adicionar mais um produto? (1 - Sim, 0 - Não): ");
        scanf("%d", &continuar);
    }

    vendas[qtd_vendas++] = nova;
    printf("Venda registrada com sucesso! Total: R$ %.2f\n", nova.valor_total);
}

void listar_vendas() {
    if (qtd_vendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    for (int i = 0; i < qtd_vendas; i++) {
        Venda v = vendas[i];
        printf("Venda ID: %d\nCliente ID: %d\nItens:\n", v.id, v.id_cliente);
        for (int j = 0; j < v.qtd_itens; j++) {
            Produto* p = buscar_produto_por_id(v.itens[j].id_produto);
            if (p) {
                printf(" - %s (x%d) R$ %.2f\n", p->nome, v.itens[j].quantidade, p->preco);
            }
        }
        printf("Total: R$ %.2f\n\n", v.valor_total);
    }
}

void excluir_cliente() {
    if (qtd_clientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    listar_clientes();

    int id;
    printf("Digite o ID do cliente a ser excluído: ");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < qtd_clientes; i++) {
        if (clientes[i].id == id) {
            encontrado = 1;

            // "Shift" os clientes seguintes uma posição à esquerda
            for (int j = i; j < qtd_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
                clientes[j].id = j + 1;  // Atualiza ID
            }

            qtd_clientes--;
            printf("Cliente excluído com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente com ID %d não encontrado.\n", id);
    }
}


int main() {
    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Listar Clientes\n");
        printf("3 - Cadastrar Produto\n");
        printf("4 - Listar Produtos\n");
        printf("5 - Registrar Venda\n");
        printf("6 - Listar Vendas\n");
        printf("7 - Excluir Cliente\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserir_cliente(); break;
            case 2: listar_clientes(); break;
            case 3: inserir_produto(); break;
            case 4: listar_produtos(); break;
            case 5: inserir_venda(); break;
            case 6: listar_vendas(); break;
            case 7: excluir_cliente(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}

