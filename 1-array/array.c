#include <stdio.h>
#include <stdlib.h>

// Função que "Remove" todas as ocorrências e retorna o "novo tamanho"
// (sem realloc, apenas para arrays estáticos. O tamanho do array original não muda)
int removerTodasOcorrencias(int arr[], int tamanho, int valor)
{
    int novoIndice = 0;
    
    for (int i = 0; i < tamanho; i++) {
        if (arr[i] != valor)
        {
            arr[novoIndice] = arr[i];
            novoIndice++;
        }
    }
    
    return novoIndice; // novo tamanho
}

// Função pata arrays dinâmicos com realloc
// Retorna o novo ponteiro e atualiza o novo tamanho via ponteiro
int* removerTodasOcorrenciasComRealloc(int *arr, int *tamanho, int valor)
{
    int novoIndice = 0;

    // Compacta o array ("remove" os elementos, por colocar todos os elementos que deverão permanecer à esquerda)
    for (int i = 0; i < *tamanho; i++)
    {
        if (arr[i] != valor)
        {
            arr[novoIndice] = arr[i];
            novoIndice++;
        }
    }

    // Se não houver remoção, retorna o array original
    if (novoIndice == *tamanho)
    {
        return arr;
    }

    // Redimensiona o array com realloc
    int *temporario = realloc(arr, novoIndice * sizeof(int));

    // Se o realloc falhar, retorna o array original
    if (temporario == NULL)
    {
        printf("Erro ao redimensionar\n");
        return arr;
    }

    // Altera o tamanho via ponteiro
    *tamanho = novoIndice;

    // Retorna o array modificado
    return temporario;
}

int main()
{
    // "REMOÇÃO" DE ELEMENTOS DO ARRAY, MAS NÃO ALTERA O TAMANHO ORIGINAL DO ARRAY
    printf("=== ARRAY ESTATICO ===\n");
    int arr[] = {10, 20, 30, 20, 40, 20};
    int tamanhoArr = 6;

    printf("Array estatico antes: \n");
    for (int i = 0; i < tamanhoArr; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    tamanhoArr = removerTodasOcorrencias(arr, tamanhoArr, 20);
    
    printf("Resultado do array estatico depois: \n");
    for (int i = 0; i < tamanhoArr; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Veja que o tamanho do array continua igual, ou seja, 6
    int tamanhoRealDoArray = sizeof(arr) / sizeof(int);
    printf("Tamanho fisico do array estatico: %d\n", tamanhoRealDoArray);
    printf("Tamanho logico do array estatico: %d\n", tamanhoArr);

    free(arr);

    // ================================================================

    // REMOÇÃO DE ELEMENTO DE ARRAY DINÂMICO COM malloc E realloc

    printf("=== ARRAY DINAMICO ===\n");
    int *vetor = malloc(6 * sizeof(int));
    if (vetor == NULL)
    {
        printf("Erro ao alocar memoria\n");
    }

    vetor[0] = 10, vetor[1] = 20, vetor[2] = 30, vetor[3] = 20, vetor[4] = 40, vetor[5] = 20;

    int tamanhoVetor = 6;

    printf("Vetor antes de realloc: ");
    for (int i = 0; i < tamanhoVetor; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    printf("Tamanho do vetor: %d\n", tamanhoVetor);

    vetor = removerTodasOcorrenciasComRealloc(vetor, &tamanhoVetor, 20);

    printf("Vetor apos realloc: ");
    for (int i = 0; i < tamanhoVetor; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    printf("Novo tamanho: %d\n", tamanhoVetor);

    free(vetor);
    
    return 0;
}