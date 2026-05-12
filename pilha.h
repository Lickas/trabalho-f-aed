#ifndef PILHA_H
#define PILHA_H

// =============================================================
// Ficheiro: pilha.h
// Descrição: Pilha para histórico de operações (undo)
// Autor: Leandro
// =============================================================

typedef struct NoPilha {
    char operacao[100];
    struct NoPilha* baixo;
} NoPilha;

typedef struct {
    NoPilha* topo;
} Pilha;

void pilha_push(Pilha* pilha, const char* operacao);
void pilha_pop(Pilha* pilha);
void pilha_peek(Pilha* pilha);
int pilha_vazia(Pilha* pilha);


#endif