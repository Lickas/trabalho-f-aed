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

// ordena os alunos pela média usando o método da bolha (vai empurrando os maiores para o fim)
void bubble_sort(Aluno arr[], int n);

// ajuda o quick sort a dividir o array em duas partes
int particionamento(Aluno arr[], int baixo, int alto);

// ordena os alunos pela média de forma rápida a usar recursividade
void quick_sort(Aluno arr[], int baixo, int alto);

#endif