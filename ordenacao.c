#include "ordenacao.h"

void bubble_sort(Aluno arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].media > arr[j+1].media) {
                Aluno temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int particionamento(Aluno arr[], int baixo, int alto) {
    float pivot = arr[alto].media;
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (arr[j].media <= pivot) {
            i++;
            Aluno temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    Aluno temp = arr[i+1];
    arr[i+1] = arr[alto];
    arr[alto] = temp;

    return i + 1;
}

void quick_sort(Aluno arr[], int baixo, int alto) {
    if (baixo < alto) {
        int p = particionamento(arr, baixo, alto);
        quick_sort(arr, baixo, p - 1);
        quick_sort(arr, p + 1, alto);
    }
}