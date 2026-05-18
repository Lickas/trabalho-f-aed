#ifndef FICHEIROS_H
#define FICHEIROS_H

#include "aluno.h"

// guarda o array de alunos num ficheiro de texto
void guardar_alunos(Aluno alunos[], int total);

// carrega os dados do ficheiro de texto para o array e devolve quantos alunos leu
int carregar_alunos(Aluno alunos[]);

#endif