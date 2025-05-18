#include <stdio.h>
#include <stdlib.h>
#define N 1000 //declaração da constante

void bubbleSort(int vetor[], int tamanho, int ordem) { //função bubble sort
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - 1 - i; j++) {
            int troca = 0;
            if (ordem == 1 && vetor[j] > vetor[j + 1]) {
                troca = 1;
            } else if (ordem == 0 && vetor[j] < vetor[j + 1]) {
                troca = 1;
            }
            if (troca) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int vetor[], int tamanho, int ordem) { //função selection sort
    for (int i = 0; i < tamanho - 1; i++) {
        int pos = i;
        for (int j = i + 1; j < tamanho; j++) {
            if ((ordem == 1 && vetor[j] < vetor[pos]) || (ordem == 0 && vetor[j] > vetor[pos])) {
                pos = j;
            }
        }
        if (pos != i) {
            int temp = vetor[i];
            vetor[i] = vetor[pos];
            vetor[pos] = temp;
        }
    }
}
void imprimirPrimeirosEUltimos(int vetor[], int tamanho) {//função para imprimir os 20 primeiros e ultimos
    int i;

    printf("Primeiros 20 valores:\n");
    for (i = 0; i < 20 && i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n\nÚltimos 20 valores:\n");
    int inicio = tamanho - 20;
    if (inicio < 0) inicio = 0; // caso o vetor tenha menos de 20 elementos
    for (i = inicio; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");
}


void imprimirVetor(int vetor[], int tamanho) { //função para imprimir o vetor inteiro
    for (int i = 0; i < tamanho; i++) {
        printf("%d - ", vetor[i]);
    }
    printf("\n");
}

void copiaVetor(int origem[], int destino[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

int main() {
    int vetorOriginal[N];
    int vetorAux[N];
    srand(1234);
    
    for (int i = 0; i < N; i++) {
        vetorOriginal[i] = rand() % 10000;
    }
    
    printf("***Vetor original:\n");
    imprimirVetor(vetorOriginal, N);

    // Bubble Sort crescente
    copiaVetor(vetorOriginal, vetorAux, N);
    bubbleSort(vetorAux, N, 1);
    printf("\n***Bubble Sort - Ordem crescente:\n");
    imprimirPrimeirosEUltimos(vetorAux, N);


    // Bubble Sort decrescente
    copiaVetor(vetorOriginal, vetorAux, N);
    bubbleSort(vetorAux, N, 0);
    printf("\n***Bubble Sort - Ordem decrescente:\n");
    imprimirPrimeirosEUltimos(vetorAux, N);


    // Selection Sort crescente
    copiaVetor(vetorOriginal, vetorAux, N);
    selectionSort(vetorAux, N, 1);
    printf("\n***Selection Sort - Ordem crescente:\n");
    imprimirPrimeirosEUltimos(vetorAux, N);


    // Selection Sort decrescente
    copiaVetor(vetorOriginal, vetorAux, N);
    selectionSort(vetorAux, N, 0);
    printf("\n***Selection Sort - Ordem decrescente:\n");
    imprimirPrimeirosEUltimos(vetorAux, N);


    return 0;
}
