#ifndef LISTA_UCS_H
#define LISTA_UCS_H

#include "aluno.h"

typedef struct NoUC {
    UC uc;
    struct NoUC* proximo;
} NoUC;

NoUC* criar_no_uc(UC uc);
void inscrever_uc(NoUC** cabeca, UC uc);

#endif