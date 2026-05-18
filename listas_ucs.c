#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas_ucs.h"

// cria uma nova caixinha para guardar uma cadeira (UC)
NoUC* criar_no_uc(UC uc) {
    NoUC* novo = (NoUC*)malloc(sizeof(NoUC));
    if (novo != NULL) {
        novo->uc = uc;
        novo->proximo = NULL;
    }
    return novo;
}

// adiciona uma cadeira nova logo no início da lista
void inscrever_uc(NoUC** cabeca, UC uc) {
    NoUC* novo = criar_no_uc(uc);
    if (novo) {
        // o novo nó aponta para o que era o primeiro elemento da lista
        novo->proximo = *cabeca;
        *cabeca = novo;
    }
}