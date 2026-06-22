#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *proximo;
} No;

No *inicio = NULL;

int main()
{
    No *no1 = malloc(sizeof(No));
    no1->valor = 10;
    no1->proximo = NULL;

    inicio = no1;

    No *no2 = malloc(sizeof(No));
    no2->valor = 20;
    no2->proximo = NULL;

    no1->proximo = no2;

    No *no3 = malloc(sizeof(No));
    no3->valor = 15;
    no3->proximo = NULL;

    No *atual = inicio;

    no1->proximo = no3;
    no3->proximo = no2;

    No *no4 = malloc(sizeof(No));

    while(atual != NULL)
    {
        printf("| %d | Proximo | -> ", atual->valor);
    
        atual = atual->proximo;
    }

    printf("NULL\n");
    
    return 0;
}