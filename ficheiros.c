#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ficheiros.h"

// guarda o array de alunos num ficheiro de texto
void guardar_alunos(Aluno alunos[], int total) {

    FILE *f = fopen("alunos.txt", "w");

    if (f == NULL) {
        printf("Erro ao abrir ficheiro!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        // escreve os dados de cada aluno separados por ponto e vírgula
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

// carrega os dados do ficheiro de texto para o array e devolve quantos alunos leu
int carregar_alunos(Aluno alunos[]) {

    FILE *f = fopen("alunos.txt", "r");

    if (f == NULL) {
        printf("Ficheiro nao encontrado!\n");
        return 0;
    }

    int total = 0;

    // o %99[^;] serve para ler as strings todas até encontrar um ponto e vírgula
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