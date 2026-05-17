// Nota: A seleção dos campos de cada struct (Aluno, Avaliacao, UC)
// foi realizada com apoio de ferramenta de IA (Claude - Anthropic).
// As structs foram revistas, compreendidas e adaptadas
// de acordo com os requisitos do sistema.


#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>

typedef struct {
    int numero;
    char nome[50];
    char curso[50];
    int ano;
    float media;
    float notas[20];      // array de notas
    int total_notas;      // quantas notas tem
} Aluno;

typedef struct {
   int numero_aluno;
   char uc[50];
   float nota; 
} Avaliacao;

typedef struct {
    char codigo[15];
    char nome[50];
    int ano;
    int semestre;
} UC;

void aluno_imprimir(Aluno* a);
float aluno_calcular_media(int numero);

#endif