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
    int altura;
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
    novo->altura = 0;

    return novo;
}

int obterAltura(No *no)
{
    if (no == NULL)
    {
        return -1;
    }

    return no->altura;
}

int maior(int a, int b)
{
    return (a > b) ? a : b;
}

void atualizarAltura(No *no)
{
    no->altura = 1 + maior(
        obterAltura(no->esquerda),
        obterAltura(no->direita)
    );
}

int fatorBalanceamento(No *no)
{
    if (no == NULL)
        return 0;

    return obterAltura(no->esquerda)
         - obterAltura(no->direita);
}

No *rotacaoDireita(No *x)
{
    No *y = x->esquerda;
    No *subarvore = y->direita;
    y->direita = x;
    x->esquerda = subarvore;
    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

No *rotacaoEsquerda(No *x)
{
    No *y = x->direita;
    No *subarvore = y->esquerda;
    y->esquerda = x;
    x->direita = subarvore;
    atualizarAltura(x);
    atualizarAltura(y);

    return y;
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
    else if (produto.codigo > raiz->produto.codigo)
    {
        raiz->direita = inserirProduto(raiz->direita, produto);
    }

    atualizarAltura(raiz);
    int balanceamento = fatorBalanceamento(raiz);

    // Se caso LL
    if (balanceamento > 1 && fatorBalanceamento(raiz->esquerda) >= 0)
    {
        return rotacaoDireita(raiz);
    }

    // Se caso RR
    if (balanceamento < -1 && fatorBalanceamento(raiz->direita) <= 0)
    {
        return rotacaoEsquerda(raiz);
    }

    // Se caso LR
    if (balanceamento > 1 && fatorBalanceamento(raiz->esquerda) <= 0)
    {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    // Se caso RL
    if (balanceamento < -1 && fatorBalanceamento(raiz->direita) >= 0)
    {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
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

No *removerProduto(No *raiz, int codigo, int *removido)
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
            *removido = 1;
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
            raiz->direita = removerProduto(raiz->direita, auxiliar->produto.codigo, removido);
        }
        // Se tiver um filho esquerdo
        else if (raiz->esquerda != NULL)
        {
            No *auxiliar = raiz->esquerda;
            free(raiz);
            *removido = 1;
            return auxiliar;
        }
        // Se tiver um filho direito
        else if (raiz->direita != NULL)
        {
            No *auxiliar = raiz->direita;
            free(raiz);
            *removido = 1;
            return auxiliar;
        }
    }

    if (codigo < raiz->produto.codigo)
    {
        raiz->esquerda = removerProduto(raiz->esquerda, codigo, removido);
    }
    else if (codigo > raiz->produto.codigo)
    {
        raiz->direita = removerProduto(raiz->direita, codigo, removido);
    }

    atualizarAltura(raiz);
    int balanceamento = fatorBalanceamento(raiz);

    // Se for caso LL, rotaciona à direita
    if (balanceamento > 1 && fatorBalanceamento(raiz->esquerda) >= 0)
    {
        return rotacaoDireita(raiz);
    }

    // Se for caso RR, rotaciona à esquerda
    if (balanceamento < -1 && fatorBalanceamento(raiz->direita) <= 0)
    {
        return rotacaoEsquerda(raiz);
    }

    // Se for caso LR, duas rotações
    if (balanceamento > 1 && fatorBalanceamento(raiz->esquerda) < 0)
    {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    // Se for caso RL, duas rotações
    if (balanceamento < -1 && fatorBalanceamento(raiz->direita) > 0)
    {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
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
                int removido = 0;
                int codigo;
                printf("Digite o código do produto: ");
                scanf("%d", &codigo);
                arvore.raiz = removerProduto(arvore.raiz, codigo, &removido);
                if (removido)
                {
                    printf("\nProduto removido com sucesso!\n");
                }
                else
                {
                    printf("\nProduto de código %d não encontrado!\n", codigo);
                }
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