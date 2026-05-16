#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "ficheiros.h"

#define MAX_ALUNOS 100

// Declarações de funções
void adicionar_aluno(void);
void guardar_alunos(Aluno* alunos, int total);
int carregar_alunos(Aluno* alunos);

typedef struct {
    int numero;
    char nome[100];
    char curso[100];
    int ano;
    float media;
} Aluno;

Aluno alunos[MAX_ALUNOS];
int total_alunos = 0;

void listar_alunos() {
    printf("\n=== LISTA DE ALUNOS ===\n");

    if (total_alunos == 0) {
        printf("Nao existem alunos registados.\n");
        return;
    }

    for (int i = 0; i < total_alunos; i++) {

        printf("\nAluno %d\n", i + 1);

        printf("Numero: %d\n", alunos[i].numero);
        printf("Nome: %s\n", alunos[i].nome);
        printf("Curso: %s\n", alunos[i].curso);
        printf("Ano: %d\n", alunos[i].ano);
        printf("Media: %.2f\n", alunos[i].media);
    }
}

void menu() {

    printf("\n==============================\n");
    printf(" SISTEMA DE GESTAO ACADEMICA\n");
    printf("==============================\n");

    printf("1 - Adicionar aluno\n");
    printf("2 - Listar alunos\n");
    printf("3 - Guardar alunos\n");
    printf("4 - Carregar alunos\n");
    printf("0 - Sair\n");

    printf("Opcao: ");
}

int main() {

    int opcao;

    do {

        menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            while (getchar() != '\n');
            continue;
        }

        switch(opcao) {

            case 1:
                adicionar_aluno();
                break;

            case 2:
                listar_alunos();
                break;

            case 3:
                guardar_alunos(alunos, total_alunos);
                break;

            case 4:
                total_alunos = carregar_alunos(alunos);
                break;

            case 0:
                printf("A sair...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}