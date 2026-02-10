/*
//irserir   
void inserir(Fila *f, Elemento e) {
    if (filaCheia(f)) // Impede inserção se estiver cheia
        return;
    f->itens[f->fim] = e;            // Insere no final
    f->fim = (f->fim + 1) % MAX;     // Atualiza circularmente o índice
    f->total++;                      // Incrementa a contagem de elementos
}
//Retirar
Elemento retirar(Fila *f) {
    Elemento vazio = {-1};               // Valor padrão caso a fila esteja vazia
    if (filaVazia(f)) 
        return vazio;      // Evita remoção se estiver vazia
    Elemento e = f->itens[f->inicio];    // Armazena o item a ser removido
    f->inicio = (f->inicio + 1) % MAX;   // Atualiza o índice de início
    f->total--;                          // Diminui o total
    return e;                            // Retorna o item removido
}
//verifiar sem remoção(peek)

Elemento espiar(Fila *f) {
    Elemento vazio = {-1};              // Valor padrão se a fila estiver vazia
    if (filaVazia(f))
        return vazio;     // Impede acesso indevido
    return f->itens[f->inicio];         // Retorna o elemento da frente
}
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 5
    // Estrutura para representar uma pessoa
typedef struct {
    char nome[30];
    int idade;
} Pessoa;
    // Estrutura para representar a fila
typedef struct {
    Pessoa itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;
    //prototipação das funções
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void inserir(Fila *f, Pessoa p);
void remover(Fila *f, Pessoa *p);
void mostrarFila(Fila *f);

int main() {
    Fila f;
    inicializarFila(&f);  // Inicializa a fila
 
    // Insere algumas pessoas na fila
    Pessoa p1 = {"João", 25};
    Pessoa p2 = {"Maria", 30};
    inserir(&f, p1);
    inserir(&f, p2);
 
    mostrarFila(&f);  // Mostra a fila antes da remoção
 
    // Remove uma pessoa da fila
    Pessoa removida;
    remover(&f, &removida);  // Aqui usamos a função de remoção
 
    printf("Pessoa removida: %s, %d\n", removida.nome, removida.idade);
 
    mostrarFila(&f);  // Mostra a fila após a remoção
 
    return 0;
}

    // Funções para manipular a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}
    // Verificar se a fila está cheia ou vazia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

    // Prototipação das funções de inserção, remoção e espiar
void inserir(Fila *f, Pessoa p) {
    if (f->total == MAX) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }
 
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(Fila *f, Pessoa *p) {
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return;
    }

    *p = f->itens[f->inicio];             
    f->inicio = (f->inicio + 1) % MAX;     
    f->total--;                        
}

void mostrarFila(Fila *f) {
    printf("Fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].idade);
    }
    printf("\n");
}

