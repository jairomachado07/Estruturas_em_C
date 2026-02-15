#include <stdio.h>
#include <stdlib.h> 
    // Contantes
#define MAX 5
    // Estrutura para representar uma pessoa
typedef struct {
    int nome[30];
    int idade;
} Pessoa;

typedef struct {
    Pessoa itens[MAX];
    int topo;
} Pilha;

    // Protótipos das funções
int inicializarPilha(Pilha* pilha);
int pilhaVazia(Pilha* pilha);
int pilhaCheia(Pilha* pilha);
void push(Pilha *pilha, Pessoa novaPessoa);
void pop(Pilha *pilha, Pessoa pessoaRemovida);
void peek(Pilha *pilha, Pessoa pessoaVisualizada);
void mostrarPilha(Pilha *pilha);

int main(){
    Pilha pilha;
    inicializarPilha(&pilha);

    Pessoa pessoa1 = {"Alice", 30};
    Pessoa pessoa2 = {"Bob", 25};
    Pessoa pessoa3 = {"Charlie", 35};   

    push(&pilha, pessoa1);
    push(&pilha, pessoa2);
    push(&pilha, pessoa3);

    mostrarPilha(&pilha);  
    Pessoa pessoaRemovida;
    pop(&pilha, &pessoaRemovida);
    printf("Pessoa removida: Nome: %s, Idade: %d\n", pessoaRemovida.nome, pessoaRemovida.idade);
    
    mostrarPilha(&pilha);

    Pessoa topo;
    peek(&pilha, &topo);
    printf("Pessoa no topo: Nome: %s, Idade: %d\n", topo.nome, topo.idade);

    return 0;
}

int inicializarPilha(Pilha* pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha* pilha) {
    return pilha->topo == -1;
}

int pilhaCheia(Pilha* pilha) {
    return pilha->topo == MAX - 1;
}

void push(Pilha *pilha, Pessoa novaPessoa) {
    if (pilhaCheia(pilha)) {
        printf("Pilha cheia! Não é possível adicionar mais pessoas.\n");
        return;
    }
    pilha->topo++;
    pilha->itens[pilha->topo] = novaPessoa;
}

void pop(Pilha *pilha, Pessoa pessoaRemovida) {
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia! Não é possível remover pessoas.\n");
        return;
    }
    *pessoaRemovida = pilha->itens[pilha->topo];
    pilha->topo--;
}

void peek(Pilha *pilha, Pessoa pessoaVisualizada) {
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia! Não há pessoas para mostrar.\n");
        return;
    }
    *pessoaVisualizada = pilha->itens[pilha->topo];
}

void mostrarPilha(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia! Não há pessoas para mostrar.\n");
        return;
    }
    printf("Pessoas na pilha:\n");
    for (int i = pilha->topo; i >= 0; i--) {
        printf("Nome: %s, Idade: %d\n", pilha->itens[i].nome, pilha->itens[i].idade);
    }
}