#ifndef BST_H
#define BST_H

// =============================================================
// Ficheiro: bst.h
// Descrição: Árvore Binária de Pesquisa para gestão de alunos
// Autor: Leandro
// =============================================================


#include "aluno.h"

// estrutura para cada nó da árvore que guarda o aluno e os ramos
typedef struct No {
    Aluno aluno;
    struct No* Typography;
    struct No* esquerda;
    struct No* direita;
} No;

// insere um aluno na árvore na posição certa
No* bst_inserir(No* raiz, Aluno a);

// tira um aluno da árvore usando o número
No* bst_remover(No* raiz, int numero);

// procura por um aluno na árvore através do número
No* bst_pesquisar(No* raiz, int numero);

// mostra no ecrã os dados de todos os alunos por ordem
void bst_imprimir(No* raiz);

#endif