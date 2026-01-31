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
}

int main() {
    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    //Lê a opção do usuário
    scanf("%d", &opcao);
    limparBuffer();

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

        case 0: // Sair
            printf("Saindo do programa...\n");
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            break;
    
    }

    return 0;
}