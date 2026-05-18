#include "aluno.h"
#include <stdio.h>

// imprime os detalhes do aluno no ecrã
void aluno_imprimir(Aluno* a) {
    printf("Número: %d\n", a->numero);
    printf("Nome: %s\n", a->nome);
    printf("Curso: %s\n", a->curso);
    printf("Ano: %d\n", a->ano);
    printf("Média: %.2f\n", a->media);
}

// calcula a média das avaliações usando o número do aluno
float aluno_calcular_media(int numero) {
    // TODO: implementar depois de ter as avaliações ligadas
    // vai percorrer as avaliações do aluno e calcular a média
    return 0.0;
}