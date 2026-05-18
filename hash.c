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

// calcula a posição na tabela usando o resto da divisão
int hash(int numero) {
    return numero % TAMANHO;
}

// prepara a tabela pondo todos os espaços a NULL
void hash_inicializar(HashTable* tabela) {
    for (int i = 0; i < TAMANHO; i++) {
        tabela->caixas[i] = NULL;
    }
}

// adiciona um aluno na tabela de hash
void hash_inserir(HashTable* tabela, Aluno a) {
    int indice = hash(a.numero);
    NodeHash* novoNode = (NodeHash*)malloc(sizeof(NodeHash));
    novoNode->aluno = a;
    
    // empurra o novo nó para o início da lista ligada desta posição
    novoNode->proximo = tabela->caixas[indice];
    tabela->caixas[indice] = novoNode;
}

// procura e apaga um aluno da tabela usando o número dele
void hash_remover(HashTable* tabela, int numero) {
    int indice = hash(numero);
    NodeHash* atual = tabela->caixas[indice];
    NodeHash* anterior = NULL;

    while (atual != NULL) {
        if (atual->aluno.numero == numero) {
            if (anterior == NULL) {
                // se for logo o primeiro, a lista passa a começar no segundo nó
                tabela->caixas[indice] = atual->proximo;
            } else {
                // liga o nó de trás ao nó da frente, saltando o atual para o remover
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

// procura por um aluno na tabela e devolve a caixa (nó) onde ele está
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