#include <stdio.h>

typedef struct{
  char nome[50];
  int idade;
  float media;
} Aluno;

int main() {
  Aluno aluno1 = {"João Silva", 20, 8.5};

  // Exibindo os valores dos campos da struct
  printf("Nome: %s\n", aluno1.nome);
  printf("Idade: %d\n", aluno1.idade);
  printf("Média: %.2f\n", aluno1.media);

  return 0;
}