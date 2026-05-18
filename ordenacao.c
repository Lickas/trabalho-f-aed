#include "ordenacao.h"

// ordena os alunos pela média usando o método da bolha (vai empurrando os maiores para o fim)
void bubble_sort(Aluno arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // se o aluno atual tiver média maior, troca de lugar com o próximo
            if (arr[j].media > arr[j+1].media) {
                Aluno temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// ajuda o quick sort a dividir o array em duas partes
int particionamento(Aluno arr[], int baixo, int alto) {
    // escolhe o último aluno como referência (pivot) para comparar as médias
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

    // mete o pivot no lugar definitivo dele, entre os menores e os maiores
    Aluno temp = arr[i+1];
    arr[i+1] = arr[alto];
    arr[alto] = temp;

    return i + 1;
}

// ordena os alunos pela média de forma rápida a usar recursividade
void quick_sort(Aluno arr[], int baixo, int alto) {
    if (baixo < alto) {
        // divide a lista e descobre a posição certa do pivot
        int p = particionamento(arr, baixo, alto);
        quick_sort(arr, baixo, p - 1);
        quick_sort(arr, p + 1, alto);
    }
}