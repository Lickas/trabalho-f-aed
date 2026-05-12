#ifndef BST_H
#define BST_H

// =============================================================
// Ficheiro: bst.h
// Descrição: Árvore Binária de Pesquisa para gestão de alunos
// Autor: Leandro
// =============================================================


#include "aluno.h"

typedef struct No {
    Aluno aluno;
    struct No* esquerda;
    struct No* direita;
} No;

No* bst_inserir(No* raiz, Aluno a);
No* bst_remover(No* raiz, int numero);
No* bst_pesquisar(No* raiz, int numero);
void bst_imprimir(No* raiz);

#endif