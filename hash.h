#ifndef HASH_H
#define HASH_H

// =============================================================
// Ficheiro: hash.h
// Descrição: Tabela de dispersão para acesso direto por número
//            mecanográfico
// Autor: Leandro
// =============================================================

#include "aluno.h"

#define TAMANHO 100

typedef struct NodeHash {
    Aluno aluno;
    struct NodeHash* proximo;
} NodeHash;

typedef struct {
    NodeHash* caixas[TAMANHO];
} HashTable;

void hash_inicializar(HashTable* tabela);
void hash_inserir(HashTable* tabela, Aluno a);
void hash_remover(HashTable* tabela, int numero);
NodeHash* hash_pesquisar(HashTable* tabela, int numero);

#endif