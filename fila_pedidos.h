#ifndef FILA_PEDIDOS_H
#define FILA_PEDIDOS_H

// estrutura de cada pedido que sabe qual é o próximo da fila
typedef struct Pedido {
    int id_pedido;
    struct Pedido *proximo;
} Pedido;

// serve para controlar quem é o primeiro e o último a ser atendido
typedef struct {
    Pedido *frente;
    Pedido *tras;
} FilaSecretaria;

// prepara a fila para ser usada, pondo tudo a NULL
void inicializar_fila(FilaSecretaria *f);

// adiciona um novo pedido ao fim da fila da secretaria
void enfileirar(FilaSecretaria *f, int id);

// tira e atende o pedido que está mais à frente na fila
void desenfileirar(FilaSecretaria *f);

#endif