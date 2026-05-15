#include "ranking_heap.h"

void heapify(AlunoRanking heap[], int n, int i) {
    int maior = i;
    int esq = 2 * i + 1; // Fórmula para filho esquerdo
    int dir = 2 * i + 2; // Fórmula para filho direito

    if (esq < n && heap[esq].media > heap[maior].media) maior = esq;
    if (dir < n && heap[dir].media > heap[maior].media) maior = dir;

    if (maior != i) {
        AlunoRanking temp = heap[i];
        heap[i] = heap[maior];
        heap[maior] = temp;
        heapify(heap, n, maior); // Recursividade para ajustar o resto
    }
}