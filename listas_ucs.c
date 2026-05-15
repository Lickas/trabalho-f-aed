#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_ucs.h"

UC* criar_no_uc(int codigo, char *nome) {
    UC *novo = (UC*) malloc(sizeof(UC)); // Alocação dinâmica 
    if (novo != NULL) {
        novo->codigo = codigo;
        strcpy(novo->nome, nome); // Copia a string para a struct
        novo->proximo = NULL;
    }
    return novo;
}

void inscrever_uc(UC **cabeca, int codigo, char *nome) {
    UC *novo = criar_no_uc(codigo, nome);
    if (novo) {
        novo->proximo = *cabeca; // Insere no início da lista
        *cabeca = novo;
    }
}