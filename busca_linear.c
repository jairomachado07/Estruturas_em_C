/* int buscaLinear(int lista[], int tamanho, int valor) {
    for (int i = 0; i < tamanho; i++) {
        if (lista[i] == valor) {
            return i; // Retorna o índice onde encontrou o valor
        }
    }
    return -1; // Retorna -1 se não encontrou
} 

int buscaLinear(int lista[], int tamanho, int alvo) {
    for (int i = 0; i < tamanho; i++) {
        if (lista[i] == alvo) {
            return i;
        }
    }
    return -1; // Não encontrado
} 
---------------------------------------- */
#include <stdio.h>
#include <stdlib.h>

struct No {
    int dado;
    struct No* proximo;
};

int buscaLinearLista(struct No* inicio, int valor) {
    int pos = 0;
    struct No* atual = inicio;
    while (atual != NULL) {
        if (atual->dado == valor) {
            return pos;
        }
        atual = atual->proximo;
        pos++;
    }
    return -1;
} 