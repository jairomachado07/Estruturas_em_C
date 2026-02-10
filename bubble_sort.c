#include <stdio.h>
#include <time.h>

void bubbleSort(int vetor[], int tamanho);
void trocar(int* a, int* b);

int main() {
    int vetor[] = {64, 34, 25, 12, 22, 11, 90};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    bubbleSort(vetor, tamanho);

    printf("Vetor ordenado: \n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    return 0;
}

void bubbleSort(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - 1 - i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                trocar(&vetor[j], &vetor[j + 1]);
            }
        }
    }
} 

void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

