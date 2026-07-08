#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Cliente
{
    int senha;
    char nome[100];
} Cliente;

// Estrutura de um nó
typedef struct No
{
    Cliente cliente;
    struct No *proximo;
} No;

// Estrutura da fila
typedef struct Fila
{
    No *frente;
    No *tras;
    int senha;
} Fila;

int gerarSenha(Fila *fila)
{
    return ++(fila->senha);
}

Cliente criarCliente(Fila *fila)
{
    Cliente cliente;

    printf("\nDigite o nome do cliente: ");
    fgets(cliente.nome, 100, stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

    cliente.senha = gerarSenha(fila);

    return cliente;
}

No* criarNo(Cliente cliente)
{
    No *no = malloc(sizeof(No));

    if (no == NULL)
    {
        printf("\nErro de memória!\n");
        return NULL;
    }

    no->cliente = cliente;
    no->proximo = NULL;

    return no;
}

// Função de inserir
void adicionarCliente(Fila *fila, Cliente cliente)
{
    No *no = criarNo(cliente);

    if (no == NULL)
    {
        return;
    }

    if (fila->frente == NULL)
    {
        fila->frente = no;
    }
    else
    {
        fila->tras->proximo = no;
    }

    fila->tras = no;

    printf("\nCliente adicionado à fila com sucesso!\n");
}

// Função de remoção
int chamarProximoCliente(Fila *fila, Cliente *cliente)
{
    if (fila->frente == NULL)
    {
        printf("\nFila vazia\n");
        return 0;
    }

    if (fila->frente == fila->tras)
    {
        *cliente = fila->frente->cliente;
        free(fila->frente);
        fila->frente = NULL;
        fila->tras = NULL;
        return 1;
    }

    *cliente = fila->frente->cliente;
    No *auxiliar = fila->frente;
    fila->frente = fila->frente->proximo;
    free(auxiliar);

    return 1;
}

void mostrarCliente(Cliente cliente)
{
    printf("\n=======================\n");
    printf("Chamando:\n\nSenha: %03d\nNome: %s", cliente.senha, cliente.nome);
    printf("\n=======================\n");
}

// Função de listar
void mostrarFila(Fila *fila)
{
    if (fila->frente == NULL)
    {
        printf("\nFila vazia\n");
        return;
    }

    No *atual = fila->frente;
    printf("\nAguardando na fila:\n");
    while (atual != NULL)
    {
        printf("\n%03d - %s\n", atual->cliente.senha, atual->cliente.nome);
        atual = atual->proximo;
    }
}

void liberarFila(Fila *fila)
{
    while (fila->frente != NULL)
    {
        No *atual = fila->frente;
        fila->frente = fila->frente->proximo;
        free(atual);
    }

    fila->frente = NULL;
    fila->tras = NULL;
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Fila fila = { NULL, NULL, 0 };
    int opcao;

    do
    {
        printf("\n====== MENU ======\n");
        printf("1 - Adicionar cliente à fila\n");
        printf("2 - Chamar próximo cliente\n");
        printf("3 - Mostrar fila\n");
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
            Cliente cliente = criarCliente(&fila);
            adicionarCliente(&fila, cliente);
            break;
        }

        case 2:
        {
            Cliente cliente;
            if (chamarProximoCliente(&fila, &cliente))
            {
                mostrarCliente(cliente);
            }
            break;
        }

        case 3:
            mostrarFila(&fila);
            break;

        case 0:
            liberarFila(&fila);
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}