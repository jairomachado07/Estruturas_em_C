#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    //Fazendo a estrutura de uma lista de compras

    //Definindo as funções para a lista de compras(listas binárias)
int buscaSequencialIterativa(const char* lista[], int tamanhoDaLista, const char* item);
int buscaSequencialRecursiva(const char* lista[], int tamanhoDaLista, const char* item);
int buscaSequencialRecursivaAux(const char* lista[], int tamanhoDaLista, const char* item, int indice);
    //Definindo as funções para a lista de compras(listas lineares)
int buscaBinariaIterativa(const char* lista[], int tamanhoDaLista, const char* item);
int buscaBinariaRecursiva(const char* lista[], int inicio, int fim, const char* item);
int buscaBinariaRecursivaAux(const char* lista[], int inicio, int fim, const char* item);

    //Função auxiliar para a busca sequencial recursiva
void imprimirResultado(const char* tipoBusca, const char* item, int resultado);

    //Função principal
int main() {
        //Lista de compras já organizada
    const char* listaDeCompras[] = {
        "arroz",
        "batata",
        "cebola",
        "detergente",
        "feijão",
        "leite",
        "macarrão",
        "óleo",
        "sal",
        "tomate"
    };

        //Cauculando o tamanho da lista
    int tamanhoDaLista = sizeof(listaDeCompras) / sizeof(listaDeCompras[0]);
        //Valor a ser buscado
    const char* itemExistente = "feijão";
    const char* itemInexistente = "chocolate";

    printf("Demonstrando as buscas na lista de compras:\n");
    printf("Lista utilizada: [arroz, batata, cebola, detergente, feijão, leite, macarrão, óleo, sal, tomate]\n");
    printf("----------------------------------------------\n");

        //Testando a busca sequencial
    printf("Busca Sequencial Iterativa:\n");
        // a) Versão Iterativa
    int res1 = buscaSequencialIterativa(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Sequencial Iterativa", itemExistente, res1);

    int res2 = buscaSequencialIterativa(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Sequencial Iterativa", itemInexistente, res2);
    printf("\n");

        // b) Versão Recursiva
    int res3 = buscaSequencialRecursiva(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Sequencial Recursiva", itemExistente, res3);

    int res4 = buscaSequencialRecursiva(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Sequencial Recursiva", itemInexistente, res4);
    printf("\n");

        //Testando a busca binária
    printf("Busca Binária (requer que a lista esteja organizada):\n");
        // a) Versão Iterativa
    int res5 = buscaBinariaIterativa(listaDeCompras, tamanhoDaLista, itemExistente);
    imprimirResultado("Binária Iterativa", itemExistente, res5);

    int res6 = buscaBinariaIterativa(listaDeCompras, tamanhoDaLista, itemInexistente);
    imprimirResultado("Binária Iterativa", itemInexistente, res6);
    printf("\n");

        // b) Versão Recursiva
    int res7 = buscaBinariaRecursiva(listaDeCompras, 0, tamanhoDaLista - 1, itemExistente);
    imprimirResultado("Binária Recursiva", itemExistente, res7);

    int res8 = buscaBinariaRecursiva(listaDeCompras, 0, tamanhoDaLista - 1, itemInexistente);
    imprimirResultado("Binária Recursiva", itemInexistente, res8);
    printf("----------------------------------------\n");

    return 0;
}
    /**
     * @brief Busca sequencial usando um laço iterativo.
     * @param lista Array de strings representando a lista de compras.
     * @param tamanho Tamanho da lista.
     * @param item String a ser buscada na lista.
     * @return Índice do item se encontrado, -1 caso contrário.
     */
int buscaSequencialIterativa(const char* lista[], int tamanhoDaLista, const char* item) {
    for (int i = 0; i < tamanhoDaLista; i++) {
        if (strcmp(lista[i], item) == 0) {
            return i; // Item encontrado
        }
    }
    return -1; // Item não encontrado
}

    /**
     * @brief Busca sequencial usando recursão.
     * @param lista Array de strings representando a lista de compras.
     * @param tamanho Tamanho da lista.
     * @param item String a ser buscada na lista.
     * @return Índice do item se encontrado, -1 caso contrário.
     */
int buscaSequencialRecursiva(const char* lista[], int tamanhoDaLista, const char* item) {
    //A logiva ficará na lista auxiliar
    return buscaSequencialRecursivaAux(lista, tamanhoDaLista, item, 0);
}

int buscaSequencialRecursivaAux(const char* lista[], int tamanhoDaLista, const char* item, int indice) {
    if (indice >= tamanhoDaLista) {
        return -1; // Item não encontrado
    }
    if (strcmp(lista[indice], item) == 0) {
        return indice; // Item encontrado
    }
    return buscaSequencialRecursivaAux(lista, tamanhoDaLista, item, indice + 1);
}

/**
 * @brief Busca binária usando um laço iterativo. A lista deve estar organizada.
 * 
 */
int buscaBinariaIterativa(const char* lista[], int tamanhoDaLista, const char* item) {
    int inicio = 0;
    int fim = tamanhoDaLista - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        int comparacao = strcmp(lista[meio], item);

        if (comparacao == 0) {
            return meio; // Item encontrado
        } else if (comparacao < 0) {
            inicio = meio + 1; // Buscar na metade superior
        } else {
            fim = meio - 1; // Buscar na metade inferior
        }
    }
    return -1; // Item não encontrado
}

/**
 * @brief Busca binária usando recursão. A lista deve estar organizada.
 * 
 */
int buscaBinariaRecursiva(const char* lista[], int inicio, int fim, const char* item) {
    if (inicio > fim) {
        return -1; // Item não encontrado
    }

    int meio = inicio + (fim - inicio) / 2;
    int comparacao = strcmp(lista[meio], item);

    if (comparacao == 0) {
        return meio; // Item encontrado
    } else if (comparacao < 0) {
        return buscaBinariaRecursiva(lista, meio + 1, fim, item); // Buscar na metade superior
    } else {
        return buscaBinariaRecursiva(lista, inicio, meio - 1, item); // Buscar na metade inferior
    }
}

int buscaBinariaRecursivaAux(const char* lista[], int inicio, int fim, const char* item) {
    if (inicio > fim) {
        return -1; // Item não encontrado
    } 
    int meio = inicio + (fim - inicio) / 2;
    int comparacao = strcmp(lista[meio], item); 
    if (comparacao == 0) {
        return meio; // Item encontrado
    } else if (comparacao < 0) {
        return buscaBinariaRecursivaAux(lista, meio + 1, fim, item); // Buscar na metade superior
    } else {
        return buscaBinariaRecursivaAux(lista, inicio, meio - 1, item); // Buscar na metade inferior
    }
}

    /**
     * @brief Imprime o resultado da busca.
     * @param tipoBusca Tipo de busca realizada (ex: "Sequencial Iterativa").
     * @param item Item que foi buscado.
     * @param resultado Índice do item se encontrado, -1 caso contrário.
     */
void imprimirResultado(const char* tipoBusca, const char* item, int resultado) {
    if (resultado != -1) {
        printf("%s: Item '%s' encontrado no índice %d.\n", tipoBusca, item, resultado);
    } else {    
        printf("%s: Item '%s' não encontrado na lista.\n", tipoBusca, item);
    }
}   