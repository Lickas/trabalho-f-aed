#include <stdlib.h>
#include "fila_pedidos.h"

void inicializar_fila(FilaSecretaria *f) {
    f->frente = f->tras = NULL;
}

void enfileirar(FilaSecretaria *f, int id) {
    Pedido *novo = (Pedido*) malloc(sizeof(Pedido));
    novo->id_pedido = id;
    novo->proximo = NULL;
    
    if (f->tras == NULL) { // Fila vazia
        f->frente = f->tras = novo;
    } else {
        f->tras->proximo = novo; // Liga o antigo último ao novo
        f->tras = novo;          // Atualiza o ponteiro do fim
    }
}