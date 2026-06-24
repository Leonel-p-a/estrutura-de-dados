#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Produto
{
    int codigo;
    char nome[100];
    char descricao[200];
    float preco;
} Produto;

typedef struct No
{
    Produto dados;
    struct No *anterior;
    struct No *proximo;
} No;

typedef struct Lista
{
    No *inicio;
    No *fim;
    int proximo_codigo;
} Lista;

int gerarCodigo(Lista *lista)
{
    return ++lista->proximo_codigo;
}

Produto criarProduto(Lista *lista)
{
    Produto produto;

    produto.codigo = gerarCodigo(lista);

    printf("Nome do Produto: ");
    fgets(produto.nome, 100, stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0';

    int opcao;

    do
    {
        printf("\n====== SUBMENU ======\n");
        printf("Produto possui descrição? \n");
        printf("1 - Sim\n");
        printf("2 - Não\n");
        printf("\nOpção: \n");
        scanf("%d", &opcao);

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (opcao)
        {
        case 1:
            printf("Descrição do Produto: ");
            fgets(produto.descricao, 200, stdin);
            produto.descricao[strcspn(produto.descricao, "\n")] = '\0';
            break;

        case 2:
            strcpy(produto.descricao, "");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 1 && opcao != 2);

    printf("Preço do Produto: ");
    scanf("%f", &produto.preco);
    return produto;
}

No *criarNo(Produto produto)
{
    No *novo_no = malloc(sizeof(No));

    if (novo_no == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

    novo_no->dados = produto;
    novo_no->anterior = NULL;
    novo_no->proximo = NULL;
    return novo_no;
}

void inserirInicio(Lista *lista, Produto produto)
{
    No *novo_no = criarNo(produto);

    if (novo_no == NULL)
    {
        return;
    }

    if (lista->inicio == NULL)
    {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    }
    else
    {
        novo_no->proximo = lista->inicio;
        lista->inicio->anterior = novo_no;
        lista->inicio = novo_no;
    }

    printf("\nProduto cadastrado com sucesso!\n");
}

void inserirAposNo(Lista *lista, Produto produto, No *produto_referencia)
{
    No *novo_no = criarNo(produto);

    if (novo_no == NULL)
    {
        return;
    }

    if (lista->inicio == NULL)
    {
        lista->inicio = novo_no;
        lista->fim = novo_no;
        printf("\nProduto cadastrado com sucesso!\n");
        return;
    }

    if (produto_referencia == NULL)
    {
        novo_no->anterior = lista->fim;
        lista->fim->proximo = novo_no;
        lista->fim = novo_no;
        printf("O produto de referência não foi encontrado. Novo produto adicionado ao final da lista.\n");
        return;
    }

    novo_no->proximo = produto_referencia->proximo;
    novo_no->anterior = produto_referencia;

    if (produto_referencia->proximo != NULL)
    {
        produto_referencia->proximo->anterior = novo_no;
    }

    produto_referencia->proximo = novo_no;

    if (novo_no->proximo == NULL)
    {
        lista->fim = novo_no;
    }

    printf("Produto cadastrado com sucesso!\n");
}

void inserirFinal(Lista *lista, Produto produto)
{
    No *novo_no = criarNo(produto);

    if (novo_no == NULL)
        return;

    if (lista->inicio == NULL)
    {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    }
    else
    {
        novo_no->anterior = lista->fim;
        lista->fim->proximo = novo_no;
        lista->fim = novo_no;
    }

    printf("\nProduto cadastrado com sucesso!\n");
}

No *buscarProdutoCodigo(Lista *lista, int codigo_produto)
{
    No *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->dados.codigo == codigo_produto)
        {
            return atual;
        }

        atual = atual->proximo;
    }

    printf("Produto não encontrado!\n");
    return NULL;
}

void alterarProduto(No *produto)
{
    if (produto == NULL)
        return;

    printf("\nQual dado você quer alterar do Produto \"%s\"\n", produto->dados.nome);

    int opcao;

    do
    {
        printf("\n====== SUBMENU ======\n");
        printf("1 - Nome\n");
        printf("2 - Preço\n");
        printf("3 - Descrição\n");
        printf("0 - Terminar alterações\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (opcao)
        {
        case 1:
        {
            char novo_nome[100];

            printf("Digite o novo Nome do Produto: ");
            fgets(novo_nome, 100, stdin);
            strcpy(produto->dados.nome, novo_nome);
            produto->dados.nome[strcspn(produto->dados.nome, "\n")] = '\0';
            printf("Nome do Produto alterado com sucesso!\n");
            break;
        }

        case 2:
        {
            float novo_preco;

            printf("Digite o novo Preço do Produto: ");
            scanf("%f", &novo_preco);
            produto->dados.preco = novo_preco;
            printf("Preço do Produto alterado com sucesso!\n");
            break;
        }

        case 3:
        {
            int opcao;

            do
            {
                printf("\n====== SUBMENU ======\n");
                printf("Produto possui descrição? \n");
                printf("1 - Sim\n");
                printf("2 - Não\n");
                printf("\nOpção: \n");
                scanf("%d", &opcao);

                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;

                switch (opcao)
                {
                case 1:
                    printf("Descrição do Produto: ");
                    fgets(produto->dados.descricao, 200, stdin);
                    produto->dados.descricao[strcspn(produto->dados.descricao, "\n")] = '\0';
                    break;

                case 2:
                    strcpy(produto->dados.descricao, "");
                    break;

                default:
                    printf("Opção inválida!\n");
                }
            } while (opcao != 1 && opcao != 2);

            printf("Descrição alterada com sucesso!\n");
            break;
        }

        case 0:
            printf("Voltando ao Menu Inicial...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);
}

void excluirProduto(Lista *lista, No *produto)
{
    if (produto == NULL)
        return;

    // Se for nó único
    if (produto->anterior == NULL && produto->proximo == NULL)
    {
        lista->inicio = NULL;
        lista->fim = NULL;
        free(produto);
        printf("Produto excluído com sucesso!\n");
        return;
    }

    // Se for o primeiro nó da lista
    if (produto->anterior == NULL)
    {
        produto->proximo->anterior = NULL;
        lista->inicio = produto->proximo;
        free(produto);
        printf("Produto excluído com sucesso!\n");
        return;
    }

    // Se for o último nó da lista
    if (produto->proximo == NULL)
    {
        produto->anterior->proximo = NULL;
        lista->fim = produto->anterior;
        free(produto);
        printf("Produto excluído com sucesso!\n");
        return;
    }

    // Se for nó intermediário
    produto->anterior->proximo = produto->proximo;
    produto->proximo->anterior = produto->anterior;
    free(produto);
    printf("Produto excluído com sucesso!\n");
}

void listarProdutos(Lista *lista)
{
    if (lista->inicio == NULL)
    {
        printf("Nenhum produto cadastrado!\n");
        return;
    }

    No *no_atual = lista->inicio;

    printf("\nPRODUTOS CADASTRADOS:\n");
    printf("\n====================================\n");

    while (no_atual != NULL)
    {
        printf("Código [%d] - %s - R$ %.2f\n", no_atual->dados.codigo, no_atual->dados.nome, no_atual->dados.preco);
        printf("Descrição: %s\n", no_atual->dados.descricao);
        printf("====================================\n");

        no_atual = no_atual->proximo;
    }
}

void liberarLista(Lista *lista)
{
    No *no_atual = lista->inicio;

    while (no_atual != NULL)
    {
        No *temporario = no_atual;

        no_atual = no_atual->proximo;

        free(temporario);
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Lista lista_produtos = {NULL, NULL, 10000};
    int opcao;

    do
    {
        printf("\n====== MENU ======\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Alterar produto\n");
        printf("3 - Excluir produto\n");
        printf("4 - Exibir produtos\n");
        printf("0 - Sair\n");

        printf("\nOpção: ");
        scanf("%d", &opcao);

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (opcao)
        {
        case 1:
        {
            Produto produto = criarProduto(&lista_produtos);
            int opcao;

            do
            {
                printf("\nInserir o produto cadastrado:\n");
                printf("1 - No início da lista\n");
                printf("2 - No meio da lista\n");
                printf("3 - No final da lista\n");
                printf("\nOpção: ");
                scanf("%d", &opcao);

                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;

                switch (opcao)
                {
                case 1:
                    inserirInicio(&lista_produtos, produto);
                    break;

                case 2:
                {
                    int codigo_produto;

                    printf("Inserir o novo produto após qual produto da lista:\n");
                    printf("Digite o código do produto: ");
                    scanf("%d", &codigo_produto);
                    No *produto_referencia = buscarProdutoCodigo(&lista_produtos, codigo_produto);
                    inserirAposNo(&lista_produtos, produto, produto_referencia);
                    break;
                }

                case 3:
                    inserirFinal(&lista_produtos, produto);
                    break;

                default:
                    printf("Opção inválida!\n");
                }
            } while (opcao != 1 && opcao != 2 && opcao != 3);

            break;
        }

        case 2:
        {
            int codigo_produto;

            printf("Digite o código do produto: ");
            scanf("%d", &codigo_produto);
            No *produto_buscado = buscarProdutoCodigo(&lista_produtos, codigo_produto);
            alterarProduto(produto_buscado);
            break;
        }

        case 3:
        {
            int codigo_produto;

            printf("Digite o código do produto: ");
            scanf("%d", &codigo_produto);
            No *produto_buscado = buscarProdutoCodigo(&lista_produtos, codigo_produto);
            excluirProduto(&lista_produtos, produto_buscado);
            break;
        }

        case 4:
            listarProdutos(&lista_produtos);
            break;

        case 0:
            liberarLista(&lista_produtos);
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}