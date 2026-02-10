//As já conhecidas funções auxiliares para a ordenação e busca
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
} 