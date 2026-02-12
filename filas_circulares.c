#include <stdio.h>
#include <string.h>
#include <stdlib.h>
    //constantes
#define MAX 5

typedef struct{
    char nome[30];
    int idade;
} Pessoa;

typedef struct{
    Pessoa itens[MAX];
    int inicio;
    int fim;
    int tamanho;
} FilaCircular;
    //Prototipos de funções
void inicializarFila(FilaCircular* fila);
int filaVazia(FilaCircular* fila);
int filaCheia(FilaCircular* fila);
int inserir(FilaCircular* fila, Pessoa p);
int remover(FilaCircular* fila, Pessoa* p);

int main(){
    FilaCircular fila;
    inicializarFila(&fila); // Inicializa a fila circular

    Pessoa p1 = {"Alice", 30};
    Pessoa p2 = {"Bob", 25};
    Pessoa p3 = {"Charlie", 35};

    inserir(&fila, p1);
    inserir(&fila, p2);
    inserir(&fila, p3);

    mostrarFila(&fila);

    Pessoa removida;
    remover(&fila, &removida);
    printf("Elemento removido: %s, %d anos\n", removida.nome, removida.idade);

    mostrarFila(&fila);

    return 0;
}

void inicializarFila(FilaCircular* fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
}

int filaVazia(FilaCircular* fila) {
    return (fila->tamanho == 0);
}

int filaCheia(FilaCircular* fila) {
    return (fila->tamanho == MAX);
}
int inserir(FilaCircular* fila, Pessoa p) {
    if (filaCheia(fila)) {
        printf("Fila cheia! Não é possível enfileirar.\n");
        return 0;
    }
    fila->itens[fila->fim] = p;
    fila->fim = (fila->fim + 1) % MAX;
    fila->tamanho++;
    return 1;
}

int remover(FilaCircular* fila, Pessoa* p) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Não é possível desenfileirar.\n");
        return 0;
    }
    *p = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;
    fila->tamanho--;
    return 1;
}

int mostrarFila(FilaCircular* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Não há elementos para mostrar.\n");
        return 0;
    }
    printf("Elementos na fila:\n");
    for (int i = 0; i < fila->tamanho; i++) {
        int index = (fila->inicio + i) % MAX;
        printf("Nome: %s, Idade: %d\n", fila->itens[index].nome, fila->itens[index].idade);
    }
    return 1;
}

