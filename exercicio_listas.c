#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    //Definindo as constantes
#define MAX_STR_LEN 100
#define MAX_TAM 10

    //Definindo a estrutura da lista estática
typedef struct {
    char dados[MAX_TAM][MAX_STR_LEN]; // DEZ LINHAS E CINQUENTA COLUNAS
    int quantidade; // QUANTIDADE DE ELEMENTOS NA LISTA
} ListaEstatica;

    //Funçoes para a lista
void inicializarLista(ListaEstatica* lista);
void inserirLista(ListaEstatica* lista, const char* texto);
void removerLista(ListaEstatica* lista, const char* texto);
void listarLista(const ListaEstatica* lista);

    //O último nó tem o ponteiro proximo igual a NULL
typedef struct No {
    char* dado;
    struct No* proximo;
} No;

    //A lista é um ponterio para o nó inicial
typedef No* ListaEncadeada;

    //Funçoes para a lista encadeada
void inicializarListaEncadeada(ListaEncadeada* lista);
void inserirListaEncadeada(ListaEncadeada* lista, const char* texto);
void removerListaEncadeada(ListaEncadeada* lista, const char* texto);
void listarListaEncadeada(const ListaEncadeada* lista);
void liberarListaEncadeada(ListaEncadeada* lista);

    //Função principal
void menuListaEstatica();
void menuListaEncadeada();

int main() {
    int opcao;
    do {
        printf("---MANIPULAÇÂO DE LISTAS ---\n");
        printf("1. Lista Estatica\n");
        printf("2. Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuListaEstatica();
                break;
            case 2:
                menuListaEncadeada();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void inicializarLista(ListaEstatica* lista) {
    lista->quantidade = 0;
}

void inserirLista(ListaEstatica* lista, const char* texto) {
    if (lista->quantidade == MAX_TAM) {
        printf("Lista cheia! Nao e possivel inserir mais elementos.\n");
        return;
    }
    strncpy(lista->dados[lista->quantidade], texto, MAX_STR_LEN - 1);
    lista->dados[lista->quantidade][MAX_STR_LEN - 1] = '\0'; // Garantir terminação nula
    lista->quantidade++;
    printf("Texto \"%s\" inserido com sucesso!\n", texto);
}

void removerLista(ListaEstatica* lista, const char* texto) {
    int i, pos = -1;
    for (i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dados[i], texto) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Texto \"%s\" nao encontrado na lista.\n", texto);
        return;
    }
    for(i = pos; i < lista->quantidade - 1; i++) {
        strcpy(lista->dados[i], lista->dados[i + 1]);
    }
    lista->quantidade--;
    printf("Texto \"%s\" removido com sucesso!\n", texto);
}

void listarLista(const ListaEstatica* lista) {
    if (lista->quantidade == 0) {
        printf("A lista esta vazia.\n");
        return;
    }
    printf("Elementos na lista:\n");
    for (int i = 0; i < lista->quantidade; i++) {
        printf("%s\n", lista->dados[i]);
    }
}

void inicializarListaEncadeada(ListaEncadeada* lista) {
    *lista = NULL;
}

void inserirListaEncadeada(ListaEncadeada* lista, const char* texto) {
    No* novoNo = (No*)malloc(sizeof(No));
    
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }
        // Copia o texto para o novo nó
    novoNo->dado = (char*)malloc(strlen(texto) + 1);
        // Verifica se a alocação foi bem-sucedida
    if (novoNo->dado == NULL) {
        printf("Erro ao alocar memoria para o texto!\n");
        free(novoNo); // Libera o nó alocado
        return;
    }
        // Copia o texto para o campo do nó
    strcpy(novoNo->dado, texto);
        // Insere o novo nó no início da lista
    novoNo->proximo = *lista;
        // Atualiza o ponteiro da lista para apontar para o novo nó
    *lista = novoNo;
    printf("Texto \"%s\" inserido com sucesso!\n", texto);  
}

void removerListaEncadeada(ListaEncadeada* lista, const char* texto) {
    No* atual = *lista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dado, texto) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Texto \"%s\" nao encontrado na lista.\n", texto);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual->dado); // Libera a memória alocada para o texto
    free(atual);
    printf("Texto \"%s\" removido com sucesso!\n", texto);
}

void listarListaEncadeada(const ListaEncadeada* lista) {
    No* atual = *lista;
    if (*lista == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }
    printf("Elementos na lista:\n");
    while (atual != NULL) {
        printf("%s\n", atual->dado);
        atual = atual->proximo;
    }
}

void liberarListaEncadeada(ListaEncadeada* lista) {
    No* atual = *lista;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual->dado); // Libera a memória alocada para o texto
        free(atual); // Libera a memória alocada para o nó
        atual = proximo;
    }
    *lista = NULL;
}

void menuListaEstatica() {
    ListaEstatica lista;
    inicializarLista(&lista);
    int opcao;
    char texto[MAX_STR_LEN];

    do {
        printf("--- LISTA ESTATICA ---\n");
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Listar\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Digite o texto para inserir: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0'; // Remove a nova linha
                inserirLista(&lista, texto);
                break;
            case 2:
                printf("Digite o texto para remover: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0'; // Remove a nova linha
                removerLista(&lista, texto);
                break;
            case 3:
                listarLista(&lista);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}   

void menuListaEncadeada() {
    ListaEncadeada lista;
    inicializarListaEncadeada(&lista);
    int opcao;
    char texto[MAX_STR_LEN];

    do {
        printf("--- LISTA ENCADEADA ---\n");
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Listar\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Digite o texto para inserir: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0'; // Remove a nova linha
                inserirListaEncadeada(&lista, texto);
                break;
            case 2:
                printf("Digite o texto para remover: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0'; // Remove a nova linha
                removerListaEncadeada(&lista, texto);
                break;
            case 3:
                listarListaEncadeada(&lista);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarListaEncadeada(&lista); // Libera a memória da lista encadeada
}




