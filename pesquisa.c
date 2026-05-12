#include "pesquisa.h"
#include <stdio.h>

// =============================================================
// Ficheiro: pesquisa.c
// Descrição: Implementação dos algoritmos de pesquisa sequencial e binária
// Autor: Leandro
// =============================================================

Aluno* pesquisa_sequencial(Aluno* array, int tamanho, int numero) {
    for (int i = 0; i < tamanho; i++) {
        if (array[i].numero == numero) {
            return &array[i];
        }
    }
    return NULL; // Não encontrado
}

Aluno* pesquisa_binaria(Aluno* array, int tamanho, int numero) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (array[meio].numero == numero) {
            return &array[meio]; // Encontrado
        } else if (numero < array[meio].numero) {
            fim = meio - 1; // Busca na metade esquerda
        } else {
            inicio = meio + 1; // Busca na metade direita
        }
    }
    return NULL; // Não encontrado
}

