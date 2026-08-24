#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO 100

// MAX HEAP

typedef struct Heap
{
    int valores[TAMANHO];
    int tamanho;
} Heap;

void trocar(int *a, int *b)
{
    int temporario = *a;
    *a = *b;
    *b = temporario;
}

void heapifyUp(Heap *heap)
{
    int atual = heap->tamanho - 1;

    while (atual > 0)
    {
        int pai = (atual - 1) / 2;

        if (heap->valores[atual] <= heap->valores[pai])
        {
            break;
        }

        trocar(&heap->valores[atual], &heap->valores[pai]);

        atual = pai;
    }
}

int inserir(Heap *heap, int valor)
{
    if (heap->tamanho >= TAMANHO)
        return 0;

    heap->valores[heap->tamanho] = valor;
    heap->tamanho++;

    heapifyUp(heap);

    return 1;
}

void heapifyDown(Heap *heap, int atual, int tamanho)
{
    while (1)
    {
        // calcula os filhos
        int esquerda = 2 * atual + 1;
        int direita = 2 * atual + 2;

        // verifica se existe pelo menos o filho esquerdo
        if (esquerda >= tamanho)
        {
            break;
        }

        int maiorFilho = esquerda;

        // verifica se existe o filho direito e se ele é maior que o esquerdo
        if (direita < tamanho && heap->valores[direita] > heap->valores[esquerda])
        {
            maiorFilho = direita;
        }

        // verifica se a raiz é maior que o maior filho
        if (heap->valores[atual] >= heap->valores[maiorFilho])
        {
            break;
        }

        // faz a troca da raiz com o maior filho para manter a propriedade max heap
        trocar(&heap->valores[atual], &heap->valores[maiorFilho]);

        // continua a partir da posição para onde o elemento desceu
        atual = maiorFilho;
    }
}

int remover(Heap *heap, int *removido)
{
    // verifica se o heap está vazio
    if (heap->tamanho == 0)
        return 0;

    // guarda o elemento removido
    int raiz = heap->valores[0];
    *removido = raiz;

    // verifica se o elemento removido é o único no heap
    if (heap->tamanho == 1)
    {
        heap->tamanho--;
        return 1;
    }

    // faz a troca do valor da raiz pelo último elemento do heap e diminui o tamanho
    heap->valores[0] = heap->valores[heap->tamanho - 1];
    heap->tamanho--;

    heapifyDown(heap, 0, heap->tamanho);

    return 1;
}

void construirHeap(Heap *heap, const int vetor[], int tamanho)
{
    memcpy(heap->valores, vetor, sizeof(int) * tamanho);
    heap->tamanho = tamanho;
    
    int ultimoPai = (heap->tamanho / 2) - 1;

    for (int i = ultimoPai; i >= 0; i--)
    {
        heapifyDown(heap, i, heap->tamanho);
    }
}

void heapSort(Heap *heap, const int vetor[], int tamanho)
{
    construirHeap(heap, vetor, tamanho);

    while (tamanho > 1)
    {
        trocar(&heap->valores[0], &heap->valores[tamanho - 1]);
        tamanho--;
        heapifyDown(heap, 0, tamanho);
    }
}

void exibir(Heap *heap)
{
    if (heap->tamanho == 0)
    {
        return;
    }

    for (int i = 0; i < heap->tamanho; i++)
    {
        printf("%d ", heap->valores[i]);
    }
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Heap heap;
    heap.tamanho = 0;
    int opcao;

    do
    {
        printf("\n====== MENU ======\n");
        printf("1 - Inserir valor\n");
        printf("2 - Exibir Heap\n");
        printf("3 - Remover elemento\n");
        printf("4 - Construir Heap\n");
        printf("5 - Ordenar Heap em ordem crescente\n");
        printf("0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (opcao)
        {
        case 1:
        {
            int valor;
            printf("Insira um valor: ");
            scanf("%d", &valor);

            if (inserir(&heap, valor))
            {
                printf("\nValor adicionado com sucesso!\n");
            }
            else
            {
                printf("\nO Heap está cheio!\n");
            }

            break;
        }

        case 2:
        {
            if (heap.tamanho == 0)
            {
                printf("\nO heap está vazio!\n");
                break;
            }

            exibir(&heap);
            break;
        }

        case 3:
        {
            if (heap.tamanho == 0)
            {
                printf("\nO heap está vazio!\n");
                break;
            }

            int removido;
            if (remover(&heap, &removido))
            {
                printf("\nElemento %d removido com sucesso!\n", removido);
            }
            else
            {
                printf("\nO heap está vazio!\n");
            }
            break;
        }

        case 4:
        {
            int vetor[] = { 2, 20, 5, 30, 15, 40, 8 };
            int tamanho = 7;
            construirHeap(&heap, vetor, tamanho);
            break;
        }

        case 5:
        {
            int vetor[] = { 2, 20, 5, 30, 15, 40, 8 };
            int tamanho = 7;
            heapSort(&heap, vetor, tamanho);
            break;
        }

        case 0:
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}