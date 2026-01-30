#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definições de constantes
#define MAX_LIVROS 50
#define TAM_STRING 100

// Definição da struct Livro
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

//Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);