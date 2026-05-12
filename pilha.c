#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

// =============================================================
// Ficheiro: pilha.c
// Descrição: Implementação da pilha para histórico de operações
// Autor: Leandro
// =============================================================

void pilha_push(Pilha* pilha, const char* operacao) {
    NoPilha* novo_no = (NoPilha*)malloc(sizeof(NoPilha));
    if (novo_no == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a pilha.\n"); //stderr para mensagens de erro, separando de mensagens normais
        return;
    }
    snprintf(novo_no->operacao, sizeof(novo_no->operacao), "%s", operacao);
    novo_no->baixo = pilha->topo;
    pilha->topo = novo_no;
}

void pilha_pop(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        fprintf(stderr, "Pilha vazia. Não é possível realizar pop.\n");
        return;
    }
    NoPilha* temp = pilha->topo;
    pilha->topo = pilha->topo->baixo;
    free(temp);
}

void pilha_peek(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        fprintf(stderr, "Pilha vazia. Não é possível realizar peek.\n");
        return;
    }
    printf("Operação no topo da pilha: %s\n", pilha->topo->operacao);
}

int pilha_vazia(Pilha* pilha) {
    return pilha->topo == NULL;
}