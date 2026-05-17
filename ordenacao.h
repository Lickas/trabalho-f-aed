#ifndef ORDENACAO_H
#define ORDENACAO_H

// =============================================================
// Ficheiro: ordenacao.h
// Descrição: Algoritmos de ordenação Bubble Sort e Quick Sort
// Autor: Leandro
//
// Nota: A estrutura e protótipos deste ficheiro foram desenvolvidos
// com apoio de ferramenta de IA (Claude - Anthropic), revistos
// e compreendidos pelo aluno.
// =============================================================

#include "aluno.h"

void bubble_sort(Aluno arr[], int n);
int particionamento(Aluno arr[], int baixo, int alto);
void quick_sort(Aluno arr[], int baixo, int alto);

#endif