#include "ranking_heap.h"
#include <stdio.h>

void heapify(AlunoRanking heap[], int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && heap[esq].media > heap[maior].media) maior = esq;
    if (dir < n && heap[dir].media > heap[maior].media) maior = dir;

    if (maior != i) {
        AlunoRanking temp = heap[i];
        heap[i] = heap[maior];
        heap[maior] = temp;
        heapify(heap, n, maior);
    }
}

void construir_heap(AlunoRanking heap[], int n) {
    // começa a meio e vai para trás
    // os nós a partir de n/2 são folhas, não precisam de heapify
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

void imprimir_top_n(AlunoRanking heap[], int n, int top) {
    construir_heap(heap, n);
    printf("\n=== TOP %d ALUNOS ===\n", top);
    for (int i = 0; i < top && i < n; i++) {
        // troca o maior (topo) com o último
        AlunoRanking temp = heap[0];
        heap[0] = heap[n - 1 - i];
        heap[n - 1 - i] = temp;
        // ajusta o heap sem o último
        heapify(heap, n - 1 - i, 0);
        // imprime o que acabou de sair do topo
        printf("%d. Numero: %d | Media: %.2f\n",
            i + 1,
            heap[n - 1 - i].num_mecanografico,
            heap[n - 1 - i].media);
    }
}