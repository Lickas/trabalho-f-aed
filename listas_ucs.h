#ifndef LISTA_UCS_H
#define LISTA_UCS_H

#include "aluno.h"

// estrutura para a lista ligada das cadeiras
typedef struct NoUC {
    UC uc;
    struct NoUC* proximo;
} NoUC;

// cria uma nova caixinha para guardar uma cadeira (UC)
NoUC* criar_no_uc(UC uc);

// adiciona uma cadeira nova logo no início da lista
void inscrever_uc(NoUC** cabeca, UC uc);

#endif