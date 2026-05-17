#include <stdio.h>
#include <stdlib.h>
#include "fila_pedidos.h"

void inicializar_fila(FilaSecretaria *f) {
    f->frente = f->tras = NULL;
}

void enfileirar(FilaSecretaria *f, int id) {
    Pedido *novo = (Pedido*) malloc(sizeof(Pedido));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memoria!\n");
        return;
    }
    novo->id_pedido = id;
    novo->proximo = NULL;

    if (f->tras == NULL) {
        f->frente = f->tras = novo;
    } else {
        f->tras->proximo = novo;
        f->tras = novo;
    }
}

void desenfileirar(FilaSecretaria *f) {
    if (f->frente == NULL) {
        printf("Fila vazia! Nao ha pedidos para atender.\n");
        return;
    }
    Pedido* temp = f->frente;
    printf("A atender pedido: %d\n", temp->id_pedido);
    f->frente = f->frente->proximo;
    if (f->frente == NULL) {
        f->tras = NULL;
    }
    free(temp);
}