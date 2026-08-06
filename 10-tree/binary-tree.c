#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Produto
{
    int codigo;
    char nome[100];
    float preco;
} Produto;

typedef struct No
{
    Produto produto;
    struct No *esquerda;
    struct No *direita;
} No;

typedef struct Arvore
{
    No *raiz;
} Arvore;

Produto criarProduto()
{
    Produto produto;

    printf("Digite o nome do produto: ");
    fgets(produto.nome, 100, stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0';

    printf("Digite o preço do produto: ");
    scanf("%f", &produto.preco);

    printf("Digite o código do produto: ");
    scanf("%d", &produto.codigo);

    return produto;
}

No* criarNo(Produto produto)
{
    No *novo = malloc(sizeof(No));

    if (novo == NULL)
        return NULL;

    novo->produto = produto;
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

No *inserirProduto(No *raiz, Produto produto)
{
    if (raiz == NULL)
    {
        return criarNo(produto);
    }

    if (produto.codigo < raiz->produto.codigo)
    {
        raiz->esquerda = inserirProduto(raiz->esquerda, produto);
    }
    else
    {
        raiz->direita = inserirProduto(raiz->direita, produto);
    }

    return raiz;
}

No *buscarProduto(No *raiz, int codigo)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (codigo == raiz->produto.codigo)
    {
        return raiz;
    }

    if (codigo < raiz->produto.codigo)
    {
        return buscarProduto(raiz->esquerda, codigo);
    }
    else if (codigo > raiz->produto.codigo)
    {
        return buscarProduto(raiz->direita, codigo);
    }
}

// A busca também pode ser feita de forma iterativa, conforme o trecho comentado abaixo

// No *buscarProdutoIterativo(No *raiz, int codigo)
// {
//     if (raiz == NULL)
//     {
//         return NULL;
//     }

//     if (codigo == raiz->produto.codigo)
//     {
//         return raiz;
//     }

//     No *atual = raiz;

//     while (atual != NULL && codigo != atual->produto.codigo)
//     {
//         if (codigo < atual->produto.codigo)
//         {
//             atual = atual->esquerda;
//         }
//         else if (codigo > atual->produto.codigo)
//         {
//             atual = atual->direita;
//         }
//     }

//     return atual;
// }

void listarProdutosCrescente(No *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    listarProdutosCrescente(raiz->esquerda);
    printf("Código %d - %s - R$ %.2f\n", raiz->produto.codigo, raiz->produto.nome, raiz->produto.preco);
    listarProdutosCrescente(raiz->direita);
}

void listarProdutosDecrescente(No *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    listarProdutosDecrescente(raiz->direita);
    printf("Código %d - %s - R$ %.2f\n", raiz->produto.codigo, raiz->produto.nome, raiz->produto.preco);
    listarProdutosDecrescente(raiz->esquerda);
}

No *removerProduto(No *raiz, int codigo)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (codigo == raiz->produto.codigo)
    {
        // Se for nó folha
        if (raiz->esquerda == NULL && raiz->direita == NULL)
        {
            free(raiz);
            printf("\nProduto removido com sucesso!\n");
            return NULL;
        }
        // Se tiver dois filhos
        else if (raiz->esquerda != NULL && raiz->direita != NULL)
        {
            No *auxiliar = raiz->direita;
            
            while (auxiliar->esquerda != NULL)
            {
                auxiliar = auxiliar->esquerda;
            }

            raiz->produto = auxiliar->produto;
            raiz->direita = removerProduto(raiz->direita, auxiliar->produto.codigo);
            return raiz;
        }
        // Se tiver um filho
        else if (raiz->esquerda != NULL)
        {
            No *auxiliar = raiz->esquerda;
            free(raiz);
            printf("\nProduto removido com sucesso!\n");
            return auxiliar;
        }
        else if (raiz->direita != NULL)
        {
            No *auxiliar = raiz->direita;
            free(raiz);
            printf("\nProduto removido com sucesso!\n");
            return auxiliar;
        }
    }

    if (codigo < raiz->produto.codigo)
    {
        raiz->esquerda = removerProduto(raiz->esquerda, codigo);
    }
    else if (codigo > raiz->produto.codigo)
    {
        raiz->direita = removerProduto(raiz->direita, codigo);
    }

    return raiz;
}

void liberarArvore(No *raiz)
{
    if (raiz != NULL)
    {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Arvore arvore = { NULL };
    int opcao;

    do
    {
        printf("\n====== MENU ======\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Buscar produto pelo código\n");
        printf("3 - Listar produtos em ordem crescente\n");
        printf("4 - Listar produtos em ordem decrescente\n");
        printf("5 - Remover produto\n");
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
            Produto produto = criarProduto();
            No *resultado = buscarProduto(arvore.raiz, produto.codigo);
            if (resultado == NULL)
            {
                arvore.raiz = inserirProduto(arvore.raiz, produto);
                printf("\nProduto cadastrado com sucesso!\n");
            }
            else
            {
                printf("\nJá existe um produto com o mesmo código!\n");
            }
            break;
        }

        case 2:
        {
            int codigo;
            printf("Digite o código do produto: ");
            scanf("%d", &codigo);
            No *resultado = buscarProduto(arvore.raiz, codigo);
            if (resultado == NULL)
            {
                printf("\nProduto não encontrado!\n");
            }
            else
            {
                printf("\nProduto encontrado!\nNome do produto: %s\nPreço: R$ %.2f\n", resultado->produto.nome, resultado->produto.preco);
            }
            break;
        }

        case 3:
            if (arvore.raiz == NULL)
            {
                printf("\nNenhum produto cadastrado!\n");
            }
            else
            {
                printf("\nTabela de produtos cadastrados\n");
                listarProdutosCrescente(arvore.raiz);
            }
            break;
        
        case 4:
            if (arvore.raiz == NULL)
            {
                printf("\nNenhum produto cadastrado!\n");
            }
            else
            {
                printf("\nTabela de produtos cadastrados\n");
                listarProdutosDecrescente(arvore.raiz);
            }
            break;

        case 5:
        {
            if (arvore.raiz == NULL)
            {
                printf("\nNenhum produto cadastrado!\n");
            }
            else
            {
                int codigo;
                printf("Digite o código do produto: ");
                scanf("%d", &codigo);
                arvore.raiz = removerProduto(arvore.raiz, codigo);
            }
            break;
        }

        case 0:
            liberarArvore(arvore.raiz);
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}