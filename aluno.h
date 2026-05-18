// Nota: A seleção dos campos de cada struct (Aluno, Avaliacao, UC)
// foi realizada com apoio de ferramenta de IA (Claude - Anthropic).
// As structs foram revistas, compreendidas e adaptadas
// de acordo com os requisitos do sistema.


#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>

// guarda os dados principais de um aluno
typedef struct {
    int numero;
    char nome[50];
    char curso[50];
    int ano;
    float media;
    float notas[20];    // array de notas
    int total_notas;    // quantas notas tem
} Aluno;

// serve para ligar a nota de um aluno a uma cadeira específica
typedef struct {
    int numero_aluno;
    char uc[50];
    float nota; 
} Avaliacao;

// info sobre as cadeiras do curso
typedef struct {
    char codigo[15];
    char nome[50];
    int ano;
    int semestre;
} UC;

// imprime os detalhes do aluno no ecrã
void aluno_imprimir(Aluno* a);

// calcula a média das avaliações usando o número do aluno
float aluno_calcular_media(int numero);

#endif