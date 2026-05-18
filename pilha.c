#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =============================================================
// Ficheiro: pilha.c
// Descrição: Implementação da pilha para histórico de operações
// Autor: Leandro
// =============================================================

// adiciona uma nova operação no topo do histórico
void pilha_push_op(Pilha* pilha, TipoOperacao tipo, Aluno aluno, const char* descricao) {
    NoPilha* novo = (NoPilha*)malloc(sizeof(NoPilha));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memoria!\n");
        return;
    }
    novo->tipo = tipo;
    novo->aluno = aluno;
    
    // copia a string da descrição com um limite de tamanho para evitar estourar a memória
    snprintf(novo->descricao, sizeof(novo->descricao), "%s", descricao);
    
    // o elemento debaixo do novo passa a ser o que era o topo antes
    novo->baixo = pilha->topo;
    pilha->topo = novo;
}

// tira a última operação que foi feita (a que está no topo)
void pilha_pop(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        fprintf(stderr, "Pilha vazia!\n");
        return;
    }
    NoPilha* temp = pilha->topo;
    
    // o topo da pilha passa a ser o elemento que estava logo abaixo
    pilha->topo = pilha->topo->baixo;
    free(temp);
}

// vê qual foi a última operação feita mas deixa-a ficar na pilha
void pilha_peek(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        fprintf(stderr, "Pilha vazia!\n");
        return;
    }
    printf("Ultima operacao: %s\n", pilha->topo->descricao);
}

// vê se o histórico de operações está vazio
int pilha_vazia(Pilha* pilha) {
    return pilha->topo == NULL;
}