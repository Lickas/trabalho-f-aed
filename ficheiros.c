#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ficheiros.h"

void guardar_alunos(Aluno alunos[], int total) {

    FILE *f = fopen("alunos.txt", "w");

    if (f == NULL) {
        printf("Erro ao abrir ficheiro!\n");
        return;
    }

    for (int i = 0; i < total; i++) {

        fprintf(f, "%d;%s;%s;%d;%.2f\n",
                alunos[i].numero,
                alunos[i].nome,
                alunos[i].curso,
                alunos[i].ano,
                alunos[i].media);
    }

    fclose(f);

    printf("Alunos guardados com sucesso!\n");
}

int carregar_alunos(Aluno alunos[]) {

    FILE *f = fopen("alunos.txt", "r");

    if (f == NULL) {
        printf("Ficheiro nao encontrado!\n");
        return 0;
    }

    int total = 0;

    while (fscanf(f,
                  "%d;%99[^;];%99[^;];%d;%f\n",
                  &alunos[total].numero,
                  alunos[total].nome,
                  alunos[total].curso,
                  &alunos[total].ano,
                  &alunos[total].media) == 5) {

        total++;
    }

    fclose(f);

    printf("Alunos carregados com sucesso!\n");

    return total;
}