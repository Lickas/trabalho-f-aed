#include "pesquisa.h"
#include <stdio.h>

// =============================================================
// Ficheiro: pesquisa.c
// Descrição: Implementação dos algoritmos de pesquisa sequencial e binária
// Autor: Leandro
// =============================================================

// procura o aluno passando por todos os elementos do array um a um
Aluno* pesquisa_sequencial(Aluno* array, int tamanho, int numero) {
    for (int i = 0; i < tamanho; i++) {
        if (array[i].numero == numero) {
            return &array[i];
        }
    }
    return NULL; // Não encontrado
}

// procura o aluno de forma rápida, partindo o array ao meio (o array tem de estar ordenado)
Aluno* pesquisa_binaria(Aluno* array, int tamanho, int numero) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        // acha a posição do meio para saber em que metade o aluno está
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