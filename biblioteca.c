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
    int disponivel; // 1 para disponível, 0 para não disponível
};

struct Emprestimo {
    int idLivro;
    char nomeUsuario[TAM_STRING];
};


//Funções auxiliares
void limparBuffer();
void exibirMenu(int *opcao);
void realizarEmprestimo(struct Livro *biblioteca, struct Emprestimo *emprestimos, int totalLivros, int *totalEmprestimos);
void listarEmprestimos(struct Emprestimo *emprestimos, int totalEmprestimos, struct Livro *biblioteca);
void adicionarLivros(struct Livro *biblioteca, int *totalLivros);
void listarLivros(struct Livro *biblioteca, int totalLivros);

int main() {
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;
    
    //iniciamos com Calloc para a memória ser zerada
    biblioteca = (struct Livro*) calloc(MAX_LIVROS, sizeof(struct Livro));
    //usamos malloc normalmente para o array de empréstimos
    emprestimos = (struct Emprestimo*) malloc(MAX_LIVROS * sizeof(struct Emprestimo));

    //verificações de alocação
    if(biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1; //retorna 1 para indicar um erro.
    }
    
    int totalLivros = 0;
    int opcao = 0;
    int totalEmprestimos = 0;

    do {
        exibirMenu(&opcao);

        switch (opcao){
            case 1: // Adicionar livro
                adicionarLivros(biblioteca, &totalLivros);
                break;
            case 2: // Listar livros
                listarLivros(biblioteca, totalLivros);
                break;
            case 3: // Realizar empréstimo
                realizarEmprestimo(biblioteca, emprestimos, totalLivros, &totalEmprestimos);
                break;
            case 4: // Listar empréstimos
                listarEmprestimos(emprestimos, totalEmprestimos, biblioteca);
                break;

            case 0: // Sair
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);

    // Liberar memória alocada
    free(biblioteca);
    free(emprestimos);

    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibirMenu(int *opcao) {
    printf("===== Menu da Biblioteca =====\n");
    printf("1. Adicionar livro\n");
    printf("2. Listar livros\n");
    printf("3. Realizar empréstimo\n");
    printf("4. Listar empréstimos\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", opcao);
    limparBuffer();
}

void realizarEmprestimo(struct Livro *biblioteca, struct Emprestimo *emprestimos, int totalLivros, int *totalEmprestimos) {
    // Implementação da função de empréstimo
    if (totalLivros == 0) {
                    printf("Nenhum livro disponível para empréstimo.\n");
    } else {
        int idLivro;
        printf("Digite o ID do livro para empréstimo (1 a %d): ", totalLivros);
        scanf("%d", &idLivro);
        limparBuffer();

        if (idLivro < 1 || idLivro > totalLivros) {
            printf("ID de livro inválido!\n");
        } else if (biblioteca[idLivro - 1].disponivel == 0) {
            printf("Livro não está disponível para empréstimo.\n");
        } else {
            printf("Digite o nome do usuário: ");
            fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
            emprestimos[*totalEmprestimos].nomeUsuario[strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")] = 0;

            emprestimos[*totalEmprestimos].idLivro = idLivro - 1;
            biblioteca[idLivro - 1].disponivel = 0; // Marca como não disponível
            (*totalEmprestimos)++;

            printf("Empréstimo realizado com sucesso!\n");
        }
    }
}
    
void listarEmprestimos(struct Emprestimo *emprestimos, int totalEmprestimos, struct Livro *biblioteca) {

    // Implementação da função para listar empréstimos
    printf("Lista de empréstimos realizados:\n");
    if (totalEmprestimos == 0) {
        printf("Nenhum empréstimo realizado.\n");
    } else {
        for (int i = 0; i < totalEmprestimos; i++) {
            printf("Empréstimo %d:\n", i + 1);
            printf("Nome do usuário: %s\n", emprestimos[i].nomeUsuario);
            printf("Livro: %s\n", biblioteca[emprestimos[i].idLivro].nome);
            printf("------------------------\n");
        }
    }
}

void adicionarLivros(struct Livro *biblioteca, int *totalLivros) {
    int i = *totalLivros; // Usamos uma variável local para facilitar a leitura do código
    // Implementação da função para adicionar livros
    if (*totalLivros < MAX_LIVROS) {
        printf("Digite o nome do livro: ");
        fgets(biblioteca[i].nome, TAM_STRING, stdin);
        biblioteca[i].nome[strcspn(biblioteca[i].nome, "\n")] = 0;
        printf("Digite o autor do livro: ");
        fgets(biblioteca[i].autor, TAM_STRING, stdin);
        biblioteca[i].autor[strcspn(biblioteca[i].autor, "\n")] = 0;
        printf("Digite a editora do livro: ");
        fgets(biblioteca[i].editora, TAM_STRING, stdin);
        biblioteca[i].editora[strcspn(biblioteca[i].editora, "\n")] = 0;        
        
        printf("Digite a edição do livro: ");  
        scanf("%d", &biblioteca[i].edicao);
        limparBuffer();

        biblioteca[i].disponivel = 1; // CORREÇÃO: Marcar como disponível ao criar
        (*totalLivros)++; // CORREÇÃO: Incremento correto do valor apontado

        printf("Livro adicionado com sucesso!\n");
    } else {
        printf("Capacidade máxima de livros atingida!\n");
    }
}

void listarLivros(struct Livro *biblioteca, int totalLivros) {
    // Implementação da função para listar livros
    printf("Lista de livros cadastrados:\n");
                
    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado.\n");
    } else {
        for (int i = 0; i < totalLivros; i++) {
            printf("Livro %d:\n", i + 1);
            printf("Nome: %s\n", biblioteca[i].nome);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Editora: %s\n", biblioteca[i].editora);
            printf("Edição: %d\n\n", biblioteca[i].edicao);
        }
        printf("------------------------\n");
    }
}





