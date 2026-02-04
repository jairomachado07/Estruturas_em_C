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


//Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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
    int opcao;
    int totalEmprestimos = 0;

    do {
        printf("========================================\n");
        printf("         Biblioteca Virtual            \n");
        printf("========================================\n");
        printf("1. Adicionar livro\n");
        printf("2. Listar livros\n");
        printf("3. Realizar empréstimo\n");
        printf("4. Listar empréstimos\n");
        printf("0. Sair\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer após a leitura do inteiro

        switch (opcao){
            case 1: // Adicionar livro
                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o autor do livro: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Digite a editora do livro: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = 0;
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = 0;
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = 0;

                    printf("Digite a edição do livro: ");  
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBuffer();

                    totalLivros++;
                    //totalLivros = totalLivros + 1;

                    printf("Livro adicionado com sucesso!\n");
                } else {
                    printf("Capacidade máxima de livros atingida!\n");
                }
                break;

            case 2: // Listar livros
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
                break;
            case 3: // Realizar empréstimo
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
                        fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                        emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = 0;

                        emprestimos[totalEmprestimos].idLivro = idLivro - 1;
                        biblioteca[idLivro - 1].disponivel = 0; // Marca como não disponível
                        totalEmprestimos++;

                        printf("Empréstimo realizado com sucesso!\n");
                    }
                }
                break;
            case 4: // Listar empréstimos
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