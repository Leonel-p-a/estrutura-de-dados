#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct No
{
    char acao[150];
    struct No *proximo;
} No;

typedef struct Pilha
{
    No *topo;
} Pilha;

char* criarAcao(char acao[])
{
    printf("\nDigite a ação feita pelo usuário: ");
    fgets(acao, 150, stdin);
    acao[strcspn(acao, "\n")] = '\0';
    return acao;
}

No* criarNo(char acao[])
{
    No *elemento = malloc(sizeof(No));
    if (elemento == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    strcpy(elemento->acao, acao);
    elemento->proximo = NULL;
    return elemento;
}

// Função "push"
void inserir(Pilha *pilha, No *elemento)
{
    if (elemento == NULL)
        return;

    elemento->proximo = pilha->topo;
    pilha->topo = elemento;
    printf("Ação concluída com sucesso\n");
}

// Função "pop"
int remover(Pilha *pilha, char acao_a_ser_desfeita[])
{
    if (pilha->topo == NULL)
    {
        printf("\nNenhuma ação a ser desfeita\n");
        return 0;
    }
    No *auxiliar = pilha->topo;
    strcpy(acao_a_ser_desfeita, pilha->topo->acao);
    pilha->topo = pilha->topo->proximo;
    free(auxiliar);
    return 1;
}

void mostrarHistorico(Pilha *pilha)
{
    if (pilha->topo == NULL)
    {
        printf("\nHistórico vazio\n");
        return;
    }
    No *atual = pilha->topo;
    printf("\nHistórico:\n");
    while (atual != NULL)
    {
        printf("%s\n", atual->acao);
        atual = atual->proximo;
    }
}

void liberarPilha(Pilha *pilha)
{
    while (pilha->topo != NULL)
    {
        No *temp = pilha->topo;
        pilha->topo = pilha->topo->proximo;
        free(temp);
    }
}


int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Pilha pilha = { NULL };
    int opcao;

    do
    {
        printf("\n====== MENU ======\n");
        printf("1 - Executar ação\n");
        printf("2 - Desfazer ação\n");
        printf("3 - Mostrar histórico\n");
        printf("0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (opcao)
        {
        case 1:
            char acao[150];
            inserir(&pilha, criarNo(criarAcao(acao)));
            break;

        case 2:
            char acao_a_ser_desfeita[150];
            if (remover(&pilha, acao_a_ser_desfeita) == 1)
            {
                printf("\nÚltima ação desfeita:\n%s\n", acao_a_ser_desfeita);
            }
            break;

        case 3:
            mostrarHistorico(&pilha);
            break;

        case 0:
            liberarPilha(&pilha);
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}