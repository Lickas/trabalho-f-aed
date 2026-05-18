#include <stdio.h>
#include <stdlib.h>
#include "fila_pedidos.h"

// prepara a fila para ser usada, pondo tudo a NULL
void inicializar_fila(FilaSecretaria *f) {
    f->frente = f->tras = NULL;
}

// adiciona um novo pedido ao fim da fila da secretaria
void enfileirar(FilaSecretaria *f, int id) {
    Pedido *novo = (Pedido*) malloc(sizeof(Pedido));
    if (novo == NULL) {
        // falhou a pedir memória ao sistema para o novo pedido
        fprintf(stderr, "Erro ao alocar memoria!\n");
        return;
    }
    novo->id_pedido = id;
    novo->proximo = NULL;

    if (f->tras == NULL) {
        // se a fila estiver vazia, este pedido fica à frente e atrás ao mesmo tempo
        f->frente = f->tras = novo;
    } else {
        f->tras->proximo = novo;
        f->tras = novo;
    }
}

// tira e atende o pedido que está mais à frente na fila
void desenfileirar(FilaSecretaria *f) {
    if (f->frente == NULL) {
        printf("Fila vazia! Nao ha pedidos para atender.\n");
        return;
    }
    Pedido* temp = f->frente;
    printf("A atender pedido: %d\n", temp->id_pedido);
    f->frente = f->frente->proximo;
    if (f->frente == NULL) {
        // se tiramos o último pedido, a cauda também tem de ficar a NULL
        f->tras = NULL;
    }
    free(temp);
}