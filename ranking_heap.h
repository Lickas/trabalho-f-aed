#ifndef RANKING_HEAP_H
#define RANKING_HEAP_H

#include <stdio.h>

// versão mais simples do aluno só com os dados que interessam para o ranking de médias
typedef struct {
    int num_mecanografico;
    float media;
} AlunoRanking;

// empurra o aluno com média mais baixa para baixo para manter a árvore organizada (max heap)
void heapify(AlunoRanking heap[], int n, int i);

// pega num array normal e transforma-o numa árvore max heap (os maiores em cima)
void construir_heap(AlunoRanking heap[], int n);

// organiza o heap e imprime apenas os melhores alunos que pedimos
void imprimir_top_n(AlunoRanking heap[], int n, int top);

#endif