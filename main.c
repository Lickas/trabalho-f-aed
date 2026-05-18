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

// verifica se uma disciplina (UC) já existe na lista procurando pelo código dela
int uc_existe(char* codigo) {
    NoUC* atual = lista_ucs;
    while (atual != NULL) {
        // compara as strings para ver se os códigos são iguais
        if (strcmp(atual->uc.codigo, codigo) == 0) {
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

// ==================== ALUNOS ====================

// pede os dados ao utilizador e guarda um aluno novo no sistema
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
    a.total_notas = 0;

    // adiciona o aluno ao array principal, à árvore e à tabela de hash para ser mais fácil pesquisar depois
    alunos[total_alunos++] = a;
    raiz_bst = bst_inserir(raiz_bst, a);
    hash_inserir(&tabela, a);

    // guarda na pilha para poder desfazer
    pilha_push_op(&pilha, OP_INSERIR_ALUNO, a, "Inseriu aluno");

    printf("Aluno adicionado com sucesso!\n");
}

// procura um aluno pelo número e apaga-o de todas as estruturas de dados
void remover_aluno() {
    int numero;
    printf("Numero mecanografico a remover: ");
    scanf("%d", &numero);

    // guarda o aluno ANTES de remover para poder desfazer
    Aluno aluno_removido = {0};
    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].numero == numero) {
            aluno_removido = alunos[i];
            break;
        }
    }

    raiz_bst = bst_remover(raiz_bst, numero);
    hash_remover(&tabela, numero);

    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].numero == numero) {
            // puxa todos os alunos seguintes uma posição para trás no array para tapar o buraco do aluno apagado
            for (int j = i; j < total_alunos - 1; j++) {
                alunos[j] = alunos[j+1];
            }
            total_alunos--;
            break;
        }
    }

    // guarda na pilha para poder desfazer
    pilha_push_op(&pilha, OP_REMOVER_ALUNO, aluno_removido, "Removeu aluno");

    printf("Aluno removido com sucesso!\n");
}

// usa a árvore para tentar encontrar e mostrar os dados de um aluno específico
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

// mostra todos os alunos que temos guardados, usando a árvore para imprimir por ordem
void listar_alunos() {
    printf("\n=== LISTA DE ALUNOS ===\n");
    if (total_alunos == 0) {
        printf("Nao existem alunos registados.\n");
        return;
    }
    bst_imprimir(raiz_bst);
}

// ==================== UCs ====================

// regista uma nova cadeira preenchendo os dados e guardando na lista ligada
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

    // guarda na pilha para poder desfazer
    Aluno vazio = {0};
    pilha_push_op(&pilha, OP_ADICIONAR_UC, vazio, "Adicionou UC");

    printf("UC adicionada com sucesso!\n");
}

// percorre a lista de cadeiras do início ao fim e imprime a informação de cada uma
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

// associa uma nota a um aluno numa certa cadeira e recalcula a média dele
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

    // confirma primeiro se a cadeira existe mesmo antes de tentar dar a nota
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

    // guarda o aluno ANTES da nota para poder desfazer
    Aluno aluno_antes = resultado->aluno;

    if (resultado->aluno.total_notas < 20) {
        resultado->aluno.notas[resultado->aluno.total_notas++] = nota;
    }

    float soma = 0;
    for (int i = 0; i < resultado->aluno.total_notas; i++) {
        soma += resultado->aluno.notas[i];
    }
    // faz a média aritmética simples com todas as notas que o aluno já tem
    resultado->aluno.media = soma / resultado->aluno.total_notas;

    for (int i = 0; i < total_alunos; i++) {
        if (alunos[i].numero == numero) {
            alunos[i] = resultado->aluno;
            break;
        }
    }
    // tira o aluno desatualizado da hash e volta a meter com a média nova
    hash_remover(&tabela, numero);
    hash_inserir(&tabela, resultado->aluno);

    // guarda na pilha para poder desfazer
    pilha_push_op(&pilha, OP_REGISTAR_NOTA, aluno_antes, "Registou nota");

    printf("Nota registada! Media atual: %.2f\n", resultado->aluno.media);
}

// ==================== RANKINGS ====================

// cria um ranking com as melhores médias usando a estrutura heap
void ver_ranking() {
    if (total_alunos == 0) {
        printf("Nao existem alunos registados!\n");
        return;
    }

    int top;
    printf("Quantos alunos quer ver no ranking? ");
    scanf("%d", &top);

    for (int i = 0; i < total_alunos; i++) {
        ranking[i].num_mecanografico = alunos[i].numero;
        ranking[i].media = alunos[i].media;
    }

    // chama a função que constrói o max heap e tira de lá os melhores
    imprimir_top_n(ranking, total_alunos, top);
}

// ==================== PEDIDOS ADMINISTRATIVOS ====================

// mete um novo pedido no fim da fila de espera da secretaria
void adicionar_pedido() {
    int id;
    printf("ID do pedido: ");
    scanf("%d", &id);
    enfileirar(&fila, id);
    printf("Pedido %d adicionado a fila!\n", id);
}

// tira e resolve o pedido que estava há mais tempo à espera na fila
void atender_pedido() {
    desenfileirar(&fila);
}

// ==================== HISTÓRICO ====================

// funciona como um Ctrl+Z, lê a última coisa que fizemos na pilha e faz o inverso
void desfazer_operacao() {
    if (pilha_vazia(&pilha)) {
        printf("Nao ha operacoes para desfazer!\n");
        return;
    }

    NoPilha* topo = pilha.topo;
    printf("A desfazer: %s\n", topo->descricao);

    switch(topo->tipo) {
        case OP_INSERIR_ALUNO:
            raiz_bst = bst_remover(raiz_bst, topo->aluno.numero);
            hash_remover(&tabela, topo->aluno.numero);
            for (int i = 0; i < total_alunos; i++) {
                if (alunos[i].numero == topo->aluno.numero) {
                    // como a última operação foi inserir, o desfazer é apagar o aluno puxando os outros para trás no array
                    for (int j = i; j < total_alunos - 1; j++) {
                        alunos[j] = alunos[j+1];
                    }
                    total_alunos--;
                    break;
                }
            }
            printf("Aluno %d removido!\n", topo->aluno.numero);
            break;

        case OP_REMOVER_ALUNO:
            alunos[total_alunos++] = topo->aluno;
            raiz_bst = bst_inserir(raiz_bst, topo->aluno);
            hash_inserir(&tabela, topo->aluno);
            printf("Aluno %d reinserido!\n", topo->aluno.numero);
            break;

        case OP_REGISTAR_NOTA:
            for (int i = 0; i < total_alunos; i++) {
                if (alunos[i].numero == topo->aluno.numero) {
                    alunos[i] = topo->aluno;
                    // substitui o aluno atual pelo aluno antigo (que guardamos antes da nota) na árvore e na hash
                    raiz_bst = bst_remover(raiz_bst, topo->aluno.numero);
                    raiz_bst = bst_inserir(raiz_bst, topo->aluno);
                    hash_remover(&tabela, topo->aluno.numero);
                    hash_inserir(&tabela, topo->aluno);
                    break;
                }
            }
            printf("Nota desfeita!\n");
            break;

        case OP_ADICIONAR_UC:
            if (lista_ucs != NULL) {
                NoUC* temp = lista_ucs;
                lista_ucs = lista_ucs->proximo;
                free(temp);
            }
            printf("UC removida!\n");
            break;
    }

    pilha_pop(&pilha);
}

// ==================== MENU ====================

// mostra as opções todas que podemos escolher no ecrã
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

// ponto de entrada do programa, inicializa as coisas e fica à espera que o utilizador escolha o que fazer
int main() {
    hash_inicializar(&tabela);
    pilha.topo = NULL;
    inicializar_fila(&fila);

    int opcao;

    do {
        menu();
        // limpa o buffer do teclado se o utilizador escrever letras em vez de números para o menu não bugar
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
            case 12:
                    total_alunos = carregar_alunos(alunos);
                     // reinicia a BST e hash
                    raiz_bst = NULL;
                    hash_inicializar(&tabela);
                     // insere cada aluno carregado na BST e hash
                    for (int i = 0; i < total_alunos; i++) {
                    // como carregamos do ficheiro para o array, temos de voltar a construir a árvore e a hash do zero
                    raiz_bst = bst_inserir(raiz_bst, alunos[i]);
                     hash_inserir(&tabela, alunos[i]);
                         }
                    printf("Estruturas atualizadas com sucesso!\n");
                     break;
            case 13: desfazer_operacao(); break;
            case 0:  printf("A sair...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}