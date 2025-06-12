#include <stdio.h>
#include <stdlib.h>

#define N 1000

struct elemento {
    int info;
    struct elemento *prox;
};
typedef struct elemento Elemento;

Elemento *lista_cria(void) {
    return NULL;
}

Elemento *lista_insere(Elemento *lista, int val) {
    Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
    if (novo == NULL) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    novo->info = val;
    novo->prox = lista;
    return novo;
}

void lista_imprime(Elemento *lista) {
    for (Elemento *p = lista; p != NULL; p = p->prox) {
        printf("%d - ", p->info);
    }
    printf("\n");
}

Elemento *lista_copia(Elemento *orig) {
    Elemento *nova = NULL;
    Elemento *p = orig;
    Elemento *fim = NULL;

    while (p != NULL) {
        Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
        novo->info = p->info;
        novo->prox = NULL;

        if (nova == NULL) {
            nova = novo;
            fim = novo;
        } else {
            fim->prox = novo;
            fim = novo;
        }
        p = p->prox;
    }
    return nova;
}

void imprimirPrimeirosEUltimos(Elemento *lista) {
    int cont = 0;
    Elemento *p = lista;

    while (p != NULL) {
        cont++;
        p = p->prox;
    }

    printf("Primeiros 20 valores:\n");
    p = lista;
    for (int i = 0; i < 20 && p != NULL; i++, p = p->prox) {
        printf("%d ", p->info);
    }

    int *ultimos = malloc(20 * sizeof(int));
    p = lista;
    int i = 0;
    while (p != NULL) {
        if (i >= cont - 20) {
            ultimos[i - (cont - 20)] = p->info;
        }
        i++;
        p = p->prox;
    }

    printf("\n\nÚltimos 20 valores:\n");
    int limite = cont < 20 ? cont : 20;
    for (i = 0; i < limite; i++) {
        printf("%d ", ultimos[i]);
    }
    printf("\n");

    free(ultimos);
}

void bubbleSort(Elemento *lista, int ordem) {
    int trocado;
    Elemento *p;
    do {
        trocado = 0;
        p = lista;
        while (p != NULL && p->prox != NULL) {
            int cond = (ordem == 1 && p->info > p->prox->info) || (ordem == 0 && p->info < p->prox->info);
            if (cond) {
                int temp = p->info;
                p->info = p->prox->info;
                p->prox->info = temp;
                trocado = 1;
            }
            p = p->prox;
        }
    } while (trocado);
}


void selectionSort(Elemento *lista, int ordem) {
    for (Elemento *i = lista; i != NULL; i = i->prox) {
        Elemento *minmax = i;
        for (Elemento *j = i->prox; j != NULL; j = j->prox) {
            if ((ordem == 1 && j->info < minmax->info) || (ordem == 0 && j->info > minmax->info)) {
                minmax = j;
            }
        }
        if (minmax != i) {
            int temp = i->info;
            i->info = minmax->info;
            minmax->info = temp;
        }
    }
}

int main(void) {
    Elemento *listaOriginal = lista_cria();

    srand(1234);
    for (int i = 0; i < N; i++) {
        listaOriginal = lista_insere(listaOriginal, rand() % 10000);
    }

    printf("*** Lista original:\n");
    lista_imprime(listaOriginal);

    Elemento *listaAux = lista_copia(listaOriginal);
    bubbleSort(listaAux, 1);
    printf("\n*** Bubble Sort - Ordem crescente:\n");
    imprimirPrimeirosEUltimos(listaAux);

    free(listaAux);
    listaAux = lista_copia(listaOriginal);
    bubbleSort(listaAux, 0);
    printf("\n*** Bubble Sort - Ordem decrescente:\n");
    imprimirPrimeirosEUltimos(listaAux);

    free(listaAux);
    listaAux = lista_copia(listaOriginal);
    selectionSort(listaAux, 1);
    printf("\n*** Selection Sort - Ordem crescente:\n");
    imprimirPrimeirosEUltimos(listaAux);

    free(listaAux);
    listaAux = lista_copia(listaOriginal);
    selectionSort(listaAux, 0);
    printf("\n*** Selection Sort - Ordem decrescente:\n");
    imprimirPrimeirosEUltimos(listaAux);

    return 0;
}
