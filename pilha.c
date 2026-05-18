#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =============================================================
// Ficheiro: pilha.c
// Descrição: Implementação da pilha para histórico de operações
// Autor: Leandro
// =============================================================

void pilha_push_op(Pilha* pilha, TipoOperacao tipo, Aluno aluno, const char* descricao) {
    NoPilha* novo = (NoPilha*)malloc(sizeof(NoPilha));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memoria!\n");
        return;
    }
    novo->tipo = tipo;
    novo->aluno = aluno;
    snprintf(novo->descricao, sizeof(novo->descricao), "%s", descricao);
    novo->baixo = pilha->topo;
    pilha->topo = novo;
}

void pilha_pop(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        fprintf(stderr, "Pilha vazia!\n");
        return;
    }
    NoPilha* temp = pilha->topo;
    pilha->topo = pilha->topo->baixo;
    free(temp);
}

void pilha_peek(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        fprintf(stderr, "Pilha vazia!\n");
        return;
    }
    printf("Ultima operacao: %s\n", pilha->topo->descricao);
}

int pilha_vazia(Pilha* pilha) {
    return pilha->topo == NULL;
}