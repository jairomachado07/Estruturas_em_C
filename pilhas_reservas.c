#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// --- Estruturas ---
typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca itens[MAX_FILA];
    int inicio, fim, tamanho;
} FilaCircular;

typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// --- Protótipos ---
void inicializarFila(FilaCircular* f);
int inserirFila(FilaCircular* f, Peca p);
int removerFila(FilaCircular* f, Peca* p);

void inicializarPilha(Pilha* p);
void push(Pilha* p, Peca peca);
int pop(Pilha* p, Peca* peca);

Peca gerarPeca();
void exibirEstado(FilaCircular* f, Pilha* p);

int proximoId = 1;

int main() {
    srand(time(NULL));
    FilaCircular fila;
    Pilha reserva;
    int opcao;
    Peca pAux;

    inicializarFila(&fila);
    inicializarPilha(&reserva);

    // Inicializa a fila cheia
    for(int i = 0; i < MAX_FILA; i++) inserirFila(&fila, gerarPeca());

    do {
        exibirEstado(&fila, &reserva);
        printf("\n1 - Jogar peca da FILA\n");
        printf("2 - Mover da FILA para RESERVA (Pilha)\n");
        printf("3 - Jogar peca da RESERVA\n");
        printf("0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: // Jogar da Fila
                if(removerFila(&fila, &pAux)) {
                    printf("\n[!] Jogou peca %d (%c) da Fila.\n", pAux.id, pAux.tipo);
                    inserirFila(&fila, gerarPeca()); // Repõe
                }
                break;

            case 2: // Fila -> Reserva
                if(reserva.topo == MAX_PILHA - 1) {
                    printf("\n[ERRO] Reserva cheia!\n");
                } else {
                    removerFila(&fila, &pAux);
                    push(&reserva, pAux);
                    inserirFila(&fila, gerarPeca()); // Repõe na fila
                    printf("\n[!] Peca %d movida para reserva.\n", pAux.id);
                }
                break;

            case 3: // Jogar da Reserva
                if(pop(&reserva, &pAux)) {
                    printf("\n[!] Jogou peca %d (%c) da Reserva.\n", pAux.id, pAux.tipo);
                }
                break;
        }
    } while(opcao != 0);

    return 0;
}

// --- Funções de Pilha ---
void inicializarPilha(Pilha* p) { p->topo = -1; }

void push(Pilha *p, Peca e) {
    if (p->topo == MAX_PILHA - 1) {
        printf("Erro: pilha cheia. Não é possível inserir.\n");
        return;
    }
 
    p->topo++;              // Avança o topo
    p->itens[p->topo] = e;  // Insere o novo elemento
}

int pop(Pilha *p, Peca *e) {
    if (p->topo == -1) {
        printf("Erro: pilha vazia. Não há elementos para remover.\n");
        e->id = -1;  // Define um valor padrão para indicar falha
        e->tipo = '\0';
        return 0;
    }

    *e = p->itens[p->topo];  // Copia o valor do topo
    p->topo--;               // Decrementa o topo
    return 1;
}

// --- Funções de Fila e Auxiliares ---
void inicializarFila(FilaCircular* f) { f->inicio = f->fim = f->tamanho = 0; }

int inserirFila(FilaCircular* f, Peca p) {
    if(f->tamanho == MAX_FILA) return 0;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->tamanho++;
    return 1;
}

int removerFila(FilaCircular* f, Peca* p) {
    if(f->tamanho == 0) return 0;
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->tamanho--;
    return 1;
}

Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
    Peca p = {tipos[rand() % 7], proximoId++};
    return p;
}

void exibirEstado(FilaCircular* f, Pilha* p) {
    printf("\n====================================");
    printf("\nFILA (Proximas): ");
    for(int i=0; i < f->tamanho; i++) 
        printf("[%d|%c] ", f->itens[(f->inicio + i)%MAX_FILA].id, f->itens[(f->inicio + i)%MAX_FILA].tipo);
    
    printf("\nRESERVA (Topo):  ");
    if(p->topo == -1) printf("(Vazia)");
    for(int i=0; i <= p->topo; i++) 
        printf("[%d|%c] ", p->itens[i].id, p->itens[i].tipo);
    printf("\n====================================\n");
}

