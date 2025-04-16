#include <stdio.h>
#include <stdlib.h>

void preencherMatriz(int *matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%d", (matriz + i * colunas + j));
        }
    }
}

void imprimirMatriz(int *matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", *(matriz + i * colunas + j));
        }
        printf("\n");
    }
}

void somarMatrizes(int *A, int *B, int *C, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            *(C + i * colunas + j) = *(A + i * colunas + j) + *(B + i * colunas + j);
        }
    }
}

void subtrairMatrizes(int *A, int *B, int *C, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            *(C + i * colunas + j) = *(A + i * colunas + j) - *(B + i * colunas + j);
        }
    }
}

void transporMatriz(int *A, int *T, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            *(T + j * linhas + i) = *(A + i * colunas + j);
        }
    }
}

void identidadeMatriz(int *I, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(I + i * n + j) = (i == j) ? 1 : 0;
        }
    }
}

void multiplicarMatrizes(int *A, int *B, int *C, int linhasA, int colunasA, int colunasB) {
    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            *(C + i * colunasB + j) = 0;
            for (int k = 0; k < colunasA; k++) {
                *(C + i * colunasB + j) += *(A + i * colunasA + k) * *(B + k * colunasB + j);
            }
        }
    }
}

int main() {
    int opcao, linhasA, colunasA, linhasB, colunasB;

    do {
        printf("\nEscolha uma operacao:\n");
        printf("1. Soma\n2. Subtracao\n3. Transposta\n4. Identidade\n5. Multiplicacao\n6. Sair\n");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 5) {
            printf("Digite o numero de linhas e colunas da Matriz 1: ");
            scanf("%d %d", &linhasA, &colunasA);
            if (opcao == 1 || opcao == 2 || opcao == 5) {
                printf("Digite o numero de linhas e colunas da Matriz 2: ");
                scanf("%d %d", &linhasB, &colunasB);
            }
        }

        int *A, *B, *C, *T;

        switch (opcao) {
            case 1:
            case 2:
                if (linhasA != linhasB || colunasA != colunasB) {
                    printf("As matrizes devem ter as mesmas dimensoes para soma/subtracao.\n");
                    break;
                }
                A = (int *)malloc(linhasA * colunasA * sizeof(int));
                B = (int *)malloc(linhasA * colunasA * sizeof(int));
                C = (int *)malloc(linhasA * colunasA * sizeof(int));
                printf("Preenchendo Matriz A:\n");
                preencherMatriz(A, linhasA, colunasA);
                printf("Preenchendo Matriz B:\n");
                preencherMatriz(B, linhasA, colunasA);
                if (opcao == 1) {
                    somarMatrizes(A, B, C, linhasA, colunasA);
                    printf("Soma das Matrizes:\n");
                } else {
                    subtrairMatrizes(A, B, C, linhasA, colunasA);
                    printf("Subtracao das Matrizes:\n");
                }
                imprimirMatriz(C, linhasA, colunasA);
                free(A); free(B); free(C);
                break;
            case 3:
                A = (int *)malloc(linhasA * colunasA * sizeof(int));
                T = (int *)malloc(colunasA * linhasA * sizeof(int));
                printf("Preenchendo Matriz A:\n");
                preencherMatriz(A, linhasA, colunasA);
                transporMatriz(A, T, linhasA, colunasA);
                printf("Transposta da Matriz A:\n");
                imprimirMatriz(T, colunasA, linhasA);
                free(A); free(T);
                break;
            case 4:
                if (linhasA != colunasA) {
                    printf("A matriz precisa ser quadrada para gerar uma identidade.\n");
                } else {
                    A = (int *)malloc(linhasA * colunasA * sizeof(int));
                    identidadeMatriz(A, linhasA);
                    printf("Matriz Identidade:\n");
                    imprimirMatriz(A, linhasA, colunasA);
                    free(A);
                }
                break;
            case 5:
                if (colunasA != linhasB) {
                    printf("O numero de colunas da Matriz 1 deve ser igual ao numero de linhas da Matriz 2.\n");
                    break;
                }
                A = (int *)malloc(linhasA * colunasA * sizeof(int));
                B = (int *)malloc(linhasB * colunasB * sizeof(int));
                C = (int *)malloc(linhasA * colunasB * sizeof(int));
                printf("Preenchendo Matriz A:\n");
                preencherMatriz(A, linhasA, colunasA);
                printf("Preenchendo Matriz B:\n");
                preencherMatriz(B, linhasB, colunasB);
                multiplicarMatrizes(A, B, C, linhasA, colunasA, colunasB);
                printf("Multiplicacao das Matrizes:\n");
                imprimirMatriz(C, linhasA, colunasB);
                free(A); free(B); free(C);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);

    return 0;
}
