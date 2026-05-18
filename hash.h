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

// nó para construir a lista ligada dentro de cada posição da tabela
typedef struct NodeHash {
    Aluno aluno;
    struct NodeHash* proximo;
} NodeHash;

// a tabela de hash que tem um array com o início das listas
typedef struct {
    NodeHash* caixas[TAMANHO];
} HashTable;

// prepara a tabela pondo todos os espaços a NULL
void hash_inicializar(HashTable* tabela);

// adiciona um aluno na tabela de hash
void hash_inserir(HashTable* tabela, Aluno a);

// procura e apaga um aluno da tabela usando o número dele
void hash_remover(HashTable* tabela, int numero);

// procura por um aluno na tabela e devolve a caixa (nó) onde ele está
NodeHash* hash_pesquisar(HashTable* tabela, int numero);

#endif