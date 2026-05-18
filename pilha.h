#ifndef PILHA_H
#define PILHA_H

// =============================================================
// Ficheiro: pilha.h
// Descrição: Pilha para histórico de operações (undo)
// Autor: Leandro
// =============================================================

#include "aluno.h"

// lista dos tipos de operações que guardamos no histórico para fazer undo
typedef enum {
    OP_INSERIR_ALUNO,
    OP_REMOVER_ALUNO,
    OP_REGISTAR_NOTA,
    OP_ADICIONAR_UC
} TipoOperacao;

// caixinha da pilha que guarda a operação e quem está debaixo dela
typedef struct NoPilha {
    TipoOperacao tipo;
    Aluno aluno;        // guarda o aluno envolvido
    char descricao[100];
    struct NoPilha* baixo;
} NoPilha;

// estrutura principal da pilha que só sabe quem está em cima de tudo
typedef struct {
    NoPilha* topo;
} Pilha;

// adiciona uma nova operação no topo do histórico
void pilha_push_op(Pilha* pilha, TipoOperacao tipo, Aluno aluno, const char* descricao);

// tira a última operação que foi feita (a que está no topo)
void pilha_pop(Pilha* pilha);

// vê qual foi a última operação feita mas deixa-a ficar na pilha
void pilha_peek(Pilha* pilha);

// vê se o histórico de operações está vazio
int pilha_vazia(Pilha* pilha);

#endif