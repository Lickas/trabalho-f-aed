#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// =============================================================
// Ficheiro: bst.c
// Descrição: Implementação da Árvore Binária de Pesquisa
// Autor: Leandro
//
// Nota: A lógica de inserção, remoção e pesquisa foi desenvolvida
// com apoio de ferramenta de IA (Claude - Anthropic), revista
// e compreendida pelo aluno.
// =============================================================

No* bst_inserir(No* raiz, Aluno a) {
    if (raiz == NULL) {
        No* novo_no = (No*)malloc(sizeof(No));
        novo_no->aluno = a;
        novo_no->esquerda = NULL;
        novo_no->direita = NULL;
        return novo_no;
    }
    if (a.numero < raiz->aluno.numero) {
        raiz->esquerda = bst_inserir(raiz->esquerda, a);
    } else if (a.numero > raiz->aluno.numero) {
        raiz->direita = bst_inserir(raiz->direita, a);
    }
    return raiz;
}

No* bst_remover(No* raiz, int numero) {
    if (raiz == NULL) return raiz;
    if (numero < raiz->aluno.numero) {
        raiz->esquerda = bst_remover(raiz->esquerda, numero);
    } else if (numero > raiz->aluno.numero) {
        raiz->direita = bst_remover(raiz->direita, numero);
    } else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        No* temp = raiz->direita;
        while (temp && temp->esquerda !=NULL) {
            temp = temp->esquerda;
        }
        raiz->aluno = temp->aluno;
        raiz->direita = bst_remover(raiz->direita, temp->aluno.numero);
    }
    return raiz;
}

No* bst_pesquisar(No* raiz, int numero) {
    if (raiz == NULL || raiz->aluno.numero == numero) {
        return raiz;
    }
    if (numero < raiz->aluno.numero) {
        return bst_pesquisar(raiz->esquerda, numero);
    }
    return bst_pesquisar(raiz->direita, numero);
}

void bst_imprimir(No* raiz) {
    if (raiz != NULL) {
        bst_imprimir(raiz->esquerda);
        aluno_imprimir(&raiz->aluno);
        bst_imprimir(raiz->direita);
    }
}

