#ifndef PESQUISA_H
#define PESQUISA_H
#include "aluno.h"

// =============================================================
// Ficheiro: pesquisa.h
// Descrição: Algoritmos de pesquisa sequencial e binária
// Autor: Leandro
// =============================================================

// procura o aluno passando por todos os elementos do array um a um
Aluno* pesquisa_sequencial(Aluno* array, int tamanho, int numero);

// procura o aluno de forma rápida, partindo o array ao meio (o array tem de estar ordenado)
Aluno* pesquisa_binaria(Aluno* array, int tamanho, int numero);

#endif