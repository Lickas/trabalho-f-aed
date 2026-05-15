#ifndef FILA_PEDIDOS_H
#define FILA_PEDIDOS_H

typedef struct Pedido {
    int id_pedido;
    struct Pedido *proximo;
} Pedido;

typedef struct {
    Pedido *frente;
    Pedido *tras;
} FilaSecretaria;

void inicializar_fila(FilaSecretaria *f);
void enfileirar(FilaSecretaria *f, int id);
#endif