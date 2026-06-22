#include <stdio.h>
#include <stdlib.h>


int main()
{
    printf("=== MATRIZ ESTATICA ===\n");
    int matriz[3][3] = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90}
    };

    printf("%p\n", matriz[0]); // Endereço da primeira linha da matriz (primeiro array dentro do array)
    printf("%d\n", matriz[0][0]); // Primeiro valor/elemento do primeiro array dentro do array, ou seja, 10
    printf("%d\n", *(*(matriz + 0) + 0)); // Mesma coisa que acima, mas desreferenciando os ponteiros

    // Percorrendo a matriz
    for (int l = 0; l < 3; l++)
    {
        for (int c = 0; c < 3; c++)
        {
            printf("%d ", matriz[l][c]);
        }
        printf("\n");
    }

    // ===================================================================================================

    printf("=== MATRIZ DINAMICA ===\n");
    // Cria um ponteiro para ponteiro (vai apontar para o primeiro array dentro do array)
    int **matrizDinamica;
    int linhas = 3;
    int colunas = 3;

    // Aloca espaco na memoria para os arrays (ponteiros) dentro da matriz
    matrizDinamica = malloc(linhas * sizeof(int *));

    // Aloca espaço para cada linha
    for (int i = 0; i < 3; i++)
    {
        matrizDinamica[i] = malloc(colunas * sizeof(int));
    }

    int valor = 1;

    // Atribui valores para cada elemento dos vetores da matriz
    for (int l = 0; l < linhas; l++)
    {
        for (int c = 0; c < colunas; c++)
        {
            matrizDinamica[l][c] = valor * 10;
            valor++;
        }
    }

    for (int l = 0; l < linhas; l++)
    {
        for (int c = 0; c < colunas; c++)
        {
            printf("%d ", matrizDinamica[l][c]);
        }
        printf("\n");
    }

    // Libera as linhas
    for (int l = 0; l < linhas; l++)
    {
        free(matrizDinamica[l]);
    }

    // Libera a matriz
    free(matrizDinamica);

    return 0;
}