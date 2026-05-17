#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "bst.h"
#include "hash.h"
#include "pilha.h"
#include "pesquisa.h"
#include "ficheiros.h"
#include "listas_ucs.h"
#include "ranking_heap.h"
#include "fila_pedidos.h"
#include "ordenacao.h"

#define MAX_ALUNOS 100

Aluno alunos[MAX_ALUNOS];
int total_alunos = 0;

No* raiz_bst = NULL;
HashTable tabela;
Pilha pilha;
NoUC* lista_ucs = NULL;
FilaSecretaria fila;
AlunoRanking ranking[MAX_ALUNOS];

// ==================== ALUNOS ====================

void adicionar_aluno() {
    if (total_alunos >= MAX_ALUNOS) {
        printf("Numero maximo de alunos atingido!\n");
        return;
    }

    Aluno a;
    printf("Numero mecanografico: ");
    scanf("%d", &a.numero);
    printf("Nome: ");
    scanf(" %[^\n]", a.nome);
    printf("Curso: ");
    scanf(" %[^\n]", a.curso);
    printf("Ano: ");
    scanf("%d", &a.ano);
    a.media = 0.0;

    alunos[total_alunos++] = a;
    raiz_bst = bst_inserir(raiz_bst, a);
    hash_inserir(&tabela, a);

    char operacao[100];
    snprintf(operacao, sizeof(operacao), "Inseriu aluno %d - %s", a.numero, a.nome);
    pilha_push(&pilha, operacao);

    printf("Aluno adicionado com sucesso!\n");
}

void remover_aluno() {
    int numero;
    printf("Numero mecanografico a remover: ");
    scanf("%d", &numero);

    raiz_bst = bst_remover(raiz_bst, numero);
    hash_remover(&tabela, numero);

    // remove do array também
    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].numero == numero) {
            for (int j = i; j < total_alunos - 1; j++) {
                alunos[j] = alunos[j+1];
            }
            total_alunos--;
            break;
        }
    }

    char operacao[100];
    snprintf(operacao, sizeof(operacao), "Removeu aluno %d", numero);
    pilha_push(&pilha, operacao);

    printf("Aluno removido com sucesso!\n");
}

void pesquisar_aluno() {
    int numero;
    printf("Numero mecanografico a pesquisar: ");
    scanf("%d", &numero);

    No* resultado = bst_pesquisar(raiz_bst, numero);
    if (resultado != NULL) {
        aluno_imprimir(&resultado->aluno);
    } else {
        printf("Aluno nao encontrado!\n");
    }
}

void listar_alunos() {
    printf("\n=== LISTA DE ALUNOS ===\n");
    if (total_alunos == 0) {
        printf("Nao existem alunos registados.\n");
        return;
    }
    bst_imprimir(raiz_bst);
}

// ==================== UCs ====================

void adicionar_uc() {
    UC uc;
    printf("Codigo da UC (ex: AED): ");
    scanf(" %[^\n]", uc.codigo);
    printf("Nome da UC: ");
    scanf(" %[^\n]", uc.nome);
    printf("Ano: ");
    scanf("%d", &uc.ano);
    printf("Semestre (1 ou 2): ");
    scanf("%d", &uc.semestre);

    inscrever_uc(&lista_ucs, uc);

    char operacao[100];
    snprintf(operacao, sizeof(operacao), "Adicionou UC %s - %s", uc.codigo, uc.nome);
    pilha_push(&pilha, operacao);

    printf("UC adicionada com sucesso!\n");
}

void listar_ucs() {
    printf("\n=== LISTA DE UCs ===\n");
    if (lista_ucs == NULL) {
        printf("Nao existem UCs registadas.\n");
        return;
    }
    NoUC* atual = lista_ucs;
    int i = 1;
    while (atual != NULL) {
        printf("\nUC %d\n", i++);
        printf("Codigo: %s\n", atual->uc.codigo);
        printf("Nome: %s\n", atual->uc.nome);
        printf("Ano: %d | Semestre: %d\n", atual->uc.ano, atual->uc.semestre);
        atual = atual->proximo;
    }
}

// ==================== AVALIAÇÕES ====================

void registar_nota() {
    int numero;
    char codigo_uc[15];
    float nota;

    printf("Numero mecanografico do aluno: ");
    scanf("%d", &numero);

    No* resultado = bst_pesquisar(raiz_bst, numero);
    if (resultado == NULL) {
        printf("Aluno nao encontrado!\n");
        return;
    }

    printf("Codigo da UC: ");
    scanf(" %[^\n]", codigo_uc);

    // Bug 2 — verifica se UC existe
    if (!uc_existe(codigo_uc)) {
        printf("UC %s nao existe! Adicione a UC primeiro.\n", codigo_uc);
        return;
    }

    printf("Nota (0-20): ");
    scanf("%f", &nota);

    if (nota < 0 || nota > 20) {
        printf("Nota invalida!\n");
        return;
    }

    // Bug 3 — calcula média real
    if (resultado->aluno.total_notas < 20) {
        resultado->aluno.notas[resultado->aluno.total_notas++] = nota;
    }

    float soma = 0;
    for (int i = 0; i < resultado->aluno.total_notas; i++) {
        soma += resultado->aluno.notas[i];
    }
    resultado->aluno.media = soma / resultado->aluno.total_notas;

    // atualiza no array e na hash
    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].numero == numero) {
            alunos[i] = resultado->aluno;
            break;
        }
    }
    hash_remover(&tabela, numero);
    hash_inserir(&tabela, resultado->aluno);

    char operacao[100];
    snprintf(operacao, sizeof(operacao), "Registou nota %.1f ao aluno %d em %s", nota, numero, codigo_uc);
    pilha_push(&pilha, operacao);

    printf("Nota registada! Media atual: %.2f\n", resultado->aluno.media);
}

// ==================== RANKINGS ====================

void ver_ranking() {
    if (total_alunos == 0) {
        printf("Nao existem alunos registados!\n");
        return;
    }

    int top;
    printf("Quantos alunos quer ver no ranking? ");
    scanf("%d", &top);

    // copia os alunos para o array de ranking
    for (int i = 0; i < total_alunos; i++) {
        ranking[i].num_mecanografico = alunos[i].numero;
        ranking[i].media = alunos[i].media;
    }

    imprimir_top_n(ranking, total_alunos, top);
}

// ==================== PEDIDOS ADMINISTRATIVOS ====================

void adicionar_pedido() {
    int id;
    printf("ID do pedido: ");
    scanf("%d", &id);
    enfileirar(&fila, id);
    printf("Pedido %d adicionado à fila!\n", id);
}

void atender_pedido() {
    desenfileirar(&fila);
}

// ==================== HISTÓRICO ====================

void desfazer_operacao() {
    if (pilha_vazia(&pilha)) {
        printf("Nao ha operacoes para desfazer!\n");
        return;
    }
    pilha_peek(&pilha);
    pilha_pop(&pilha);
    printf("Operacao desfeita!\n");
}

// ==================== MENU ====================

void menu() {
    printf("\n==============================\n");
    printf(" SISTEMA DE GESTAO ACADEMICA\n");
    printf("==============================\n");
    printf("\n-- ALUNOS --\n");
    printf("1 - Adicionar aluno\n");
    printf("2 - Remover aluno\n");
    printf("3 - Pesquisar aluno\n");
    printf("4 - Listar alunos\n");
    printf("\n-- UNIDADES CURRICULARES --\n");
    printf("5 - Adicionar UC\n");
    printf("6 - Listar UCs\n");
    printf("\n-- AVALIACOES --\n");
    printf("7 - Registar nota\n");
    printf("\n-- RANKINGS --\n");
    printf("8 - Ver ranking de alunos\n");
    printf("\n-- ADMINISTRATIVO --\n");
    printf("9 - Adicionar pedido administrativo\n");
    printf("10 - Atender proximo pedido\n");
    printf("\n-- SISTEMA --\n");
    printf("11 - Guardar alunos\n");
    printf("12 - Carregar alunos\n");
    printf("13 - Desfazer ultima operacao\n");
    printf("0 - Sair\n");
    printf("\nOpcao: ");
}

int main() {
    hash_inicializar(&tabela);
    pilha.topo = NULL;
    inicializar_fila(&fila);

    int opcao;

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            while (getchar() != '\n');
            continue;
        }

        switch(opcao) {
            case 1:  adicionar_aluno(); break;
            case 2:  remover_aluno(); break;
            case 3:  pesquisar_aluno(); break;
            case 4:  listar_alunos(); break;
            case 5:  adicionar_uc(); break;
            case 6:  listar_ucs(); break;
            case 7:  registar_nota(); break;
            case 8:  ver_ranking(); break;
            case 9:  adicionar_pedido(); break;
            case 10: atender_pedido(); break;
            case 11: guardar_alunos(alunos, total_alunos); break;
            case 12: total_alunos = carregar_alunos(alunos); break;
            case 13: desfazer_operacao(); break;
            case 0:  printf("A sair...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}