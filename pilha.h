#ifndef PILHA_H
#define PILHA_H

// =============================================================
// Ficheiro: pilha.h
// Descrição: Pilha para histórico de operações (undo)
// Autor: Leandro
// =============================================================

#include "aluno.h"

typedef enum {
    OP_INSERIR_ALUNO,
    OP_REMOVER_ALUNO,
    OP_REGISTAR_NOTA,
    OP_ADICIONAR_UC
} TipoOperacao;

typedef struct NoPilha {
    TipoOperacao tipo;
    Aluno aluno;        // guarda o aluno envolvido
    char descricao[100];
    struct NoPilha* baixo;
} NoPilha;

typedef struct {
    NoPilha* topo;
} Pilha;

void pilha_push_op(Pilha* pilha, TipoOperacao tipo, Aluno aluno, const char* descricao);
void pilha_pop(Pilha* pilha);
void pilha_peek(Pilha* pilha);
int pilha_vazia(Pilha* pilha);

#endif