#include "hash.h"
#include <stdlib.h>
#include <stdio.h>

// =============================================================
// Ficheiro: hash.c
// Descrição: Implementação da tabela de dispersão
// Autor: Leandro
//
// Nota: A lógica deste ficheiro foi desenvolvida com apoio de
// ferramenta de IA (Claude - Anthropic), revista e compreendida
// pelo aluno.
// =============================================================

int hash(int numero) {
    return numero % TAMANHO;
}

void hash_inicializar(HashTable* tabela) {
    for (int i = 0; i < TAMANHO; i++) {
        tabela->caixas[i] = NULL;
    }
}

void hash_inserir(HashTable* tabela, Aluno a) {
    int indice = hash(a.numero);
    NodeHash* novoNode = (NodeHash*)malloc(sizeof(NodeHash));
    novoNode->aluno = a;
    novoNode->proximo = tabela->caixas[indice];
    tabela->caixas[indice] = novoNode;
}

void hash_remover(HashTable* tabela, int numero) {
    int indice = hash(numero);
    NodeHash* atual = tabela->caixas[indice];
    NodeHash* anterior = NULL;

    while (atual != NULL) {
        if (atual->aluno.numero == numero) {
            if (anterior == NULL) {
                tabela->caixas[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

NodeHash* hash_pesquisar(HashTable* tabela, int numero) {
    int indice = hash(numero);
    NodeHash* atual = tabela->caixas[indice];

    while (atual != NULL) {
        if (atual->aluno.numero == numero) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

