#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO 7

typedef struct No
{
    int valor;
    struct No *proximo;
} No;

typedef struct HashTable
{
    No *tabela[TAMANHO];
} HashTable;

int hash(int valor)
{
    return valor % TAMANHO;
}

void inicializarHash(HashTable *hash_table)
{
    for (int i = 0; i < TAMANHO; i++)
    {
        hash_table->tabela[i] = NULL;
    }
}

No *criarNo(int valor)
{
    No *novo_no = malloc(sizeof(No));

    if (novo_no == NULL)
        return NULL;

    novo_no->valor = valor;
    novo_no->proximo = NULL;

    return novo_no;
}

No *buscar(HashTable *hash_table, int valor)
{
    int indice = hash(valor);
    No *atual = hash_table->tabela[indice];

    while (atual != NULL)
    {
        if (atual->valor == valor)
        {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}

int inserir(HashTable *hash_table, int valor)
{
    int indice = hash(valor);
    No *atual = hash_table->tabela[indice];

    while (atual != NULL)
    {
        if (atual->valor == valor)
        {
            return 0;
        }

        atual = atual->proximo;
    }

    No *no = criarNo(valor);

    if (no == NULL)
        return 0;

    if (hash_table->tabela[indice] == NULL)
    {        
        hash_table->tabela[indice] = no;
    }
    else
    {
        atual = hash_table->tabela[indice];

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = no;
    }

    return 1;
}

int remover(HashTable *hash_table, int valor)
{
    int indice = hash(valor);
    No *atual = hash_table->tabela[indice];
    No *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->valor == valor)
        {
            if (anterior == NULL)
            {
                No *no_removido = atual;
                hash_table->tabela[indice] = atual->proximo;
                free(no_removido);

                return 1;
            }
            else
            {
                anterior->proximo = atual->proximo;
                free(atual);

                return 1;
            }
        }

        anterior = atual;
        atual = atual->proximo;
    }

    return 0;
}

void exibir(HashTable *hash_table)
{
    for (int i = 0; i < TAMANHO; i++)
    {
        printf("Índice %d: ", i);
        No *atual = hash_table->tabela[i];
        while (atual != NULL)
        {
            printf("%d ", atual->valor);
            atual = atual->proximo;
        }
        printf("\n");
    }
}

void liberarHash(HashTable *hash_table)
{
    for (int i = 0; i < TAMANHO; i++)
    {
        No *atual = hash_table->tabela[i];
        while (atual != NULL)
        {
            No *temporario = atual;
            atual = atual->proximo;
            free(temporario);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    HashTable hash_table;
    inicializarHash(&hash_table);
    int opcao;

    do
    {
        printf("\n====== MENU ======\n");
        printf("1 - Inserir valor\n");
        printf("2 - Remover elemento\n");
        printf("3 - Exibir tabela\n");
        printf("4 - Buscar valor\n");
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

            if (inserir(&hash_table, valor))
            {
                printf("\nValor adicionado com sucesso!\n");
            }
            else
            {
                printf("\nNão foi possível adicionar o valor!\n");
            }

            break;
        }

        case 2:
        {
            int valor;
            printf("Informe o valor a ser removido: ");
            scanf("%d", &valor);

            if (remover(&hash_table, valor))
            {
                printf("\nValor removido com sucesso!\n");
            }
            else
            {
                printf("\nNão foi possível remover o valor!\n");
            }

            break;
        }

        case 3:
        {
            printf("\nTabela:\n");
            exibir(&hash_table);
            break;
        }
        
        case 4:
        {
            int valor;
            printf("Digite o valor: ");
            scanf("%d", &valor);
            No *resultadoBusca = buscar(&hash_table, valor);

            if (resultadoBusca == NULL)
            {
                printf("\nValor não encontrado!\n");
            }
            else
            {
                printf("\nValor encontrado: %d", resultadoBusca->valor);
            }
            break;
        }

        case 0:
            liberarHash(&hash_table);
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}