#ifndef LISTA_UCS_H
#define LISTA_UCS_H

typedef struct UC {
    int codigo;
    char nome[50];
    struct UC *proximo;
} UC;

// Protótipos das funções
UC* criar_no_uc(int codigo, char *nome);
void inscrever_uc(UC **cabeca, int codigo, char *nome);
#endif