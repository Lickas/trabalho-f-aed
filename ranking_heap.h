#ifndef RANKING_HEAP_H
#define RANKING_HEAP_H

#include <stdio.h>

typedef struct {
    int num_mecanografico;
    float media;
} AlunoRanking;

void heapify(AlunoRanking heap[], int n, int i);
void construir_heap(AlunoRanking heap[], int n);
void imprimir_top_n(AlunoRanking heap[], int n, int top);

#endif