#ifndef RANKING_HEAP_H
#define RANKING_HEAP_H

typedef struct {
    int num_mecanografico;
    float media;
} AlunoRanking;

void heapify(AlunoRanking heap[], int n, int i);
#endif