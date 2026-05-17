#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas_ucs.h"

NoUC* criar_no_uc(UC uc) {
    NoUC* novo = (NoUC*)malloc(sizeof(NoUC));
    if (novo != NULL) {
        novo->uc = uc;
        novo->proximo = NULL;
    }
    return novo;
}

void inscrever_uc(NoUC** cabeca, UC uc) {
    NoUC* novo = criar_no_uc(uc);
    if (novo) {
        novo->proximo = *cabeca;
        *cabeca = novo;
    }
}