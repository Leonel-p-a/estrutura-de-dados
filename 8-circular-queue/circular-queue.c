#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define TAMANHO 5

typedef struct Documento
{
    int id;
    char nome[100];
    int paginas;
} Documento;

typedef struct FilaCircular
{
    Documento documentos[TAMANHO];
    int frente;
    int tras;
    int id;
} FilaCircular;

void criarFila(FilaCircular *fila)
{
    fila->frente = -1;
    fila->tras = -1;
    fila->id = 0;
}

int gerarIDDocumento(FilaCircular *fila)
{
    return ++(fila->id);
}

Documento criarDocumento(FilaCircular *fila)
{
    Documento documento;

    documento.id = gerarIDDocumento(fila);

    printf("Digite o nome do documento: ");
    fgets(documento.nome, 100, stdin);
    documento.nome[strcspn(documento.nome, "\n")] = '\0';

    printf("Digite o número de páginas: ");
    scanf("%d", &documento.paginas);

    return documento;
}

void adicionarAFila(FilaCircular *fila, Documento documento)
{
    if (fila->frente == -1)
    {
        fila->documentos[(fila->tras + 1) % TAMANHO] = documento;
        fila->frente = 0;
        fila->tras = 0;
        printf("\nDocumento adicionado à fila de impressão\n");

        return;
    }

    fila->tras = (fila->tras + 1) % TAMANHO;
    fila->documentos[fila->tras] = documento;

    printf("\nDocumento adicionado à fila de impressão\n");
}

Documento imprimirProximo(FilaCircular *fila)
{
    Documento documento = fila->documentos[fila->frente];

    if (fila->frente == fila->tras)
    {
        fila->frente = -1;
        fila->tras = -1;
    }
    else
    {
        fila->frente = (fila->frente + 1) % TAMANHO;
    }
    
    return documento;
}

void mostrarDocumentoImpresso(Documento documento)
{
    printf("\nIMPRIMINDO DOCUMENTO");
    printf("\n=======================\n");
    printf("ID do Documento: %d\nNome do Documento: %s\nQuantidade de páginas do Documento: %d", documento.id, documento.nome, documento.paginas);
    printf("\n=======================\n");
}

void mostrarFilaDeImpressao(FilaCircular *fila)
{
    int auxiliar = fila->frente;

    printf("\n===== FILA DE IMPRESSÃO =====\n");
    while (1)
    {
        printf("Nome do Documento: %s\n", fila->documentos[auxiliar].nome);

        if (auxiliar == fila->tras)
        {
            break;
        }

        auxiliar = (auxiliar + 1) % TAMANHO;
    }
    printf("=============================\n");
}

int estaCheia(FilaCircular *fila)
{
    if ((fila->tras + 1) % TAMANHO == fila->frente)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int estaVazia(FilaCircular *fila)
{
    if (fila->frente == -1 && fila->tras == -1)
    {
        return 1;
    }
    else{
        return 0;
    }
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    FilaCircular fila_de_impressao;
    criarFila(&fila_de_impressao);

    int opcao;

    do
    {
        printf("\n====== MENU ======\n");
        printf("1 - Adicionar documento à fila de impressão\n");
        printf("2 - Imprimir próximo documento\n");
        printf("3 - Mostrar fila de impressão\n");
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
            if (estaCheia(&fila_de_impressao))
            {
                printf("\nA fila de impressão está cheia!\n");
            }
            else
            {
                Documento documento = criarDocumento(&fila_de_impressao);
                adicionarAFila(&fila_de_impressao, documento);
            }
            break;
        }

        case 2:
        {
            if (estaVazia(&fila_de_impressao))
            {
                printf("\nA fila de impressão está vazia!\n");
            }
            else
            {
                Documento documento_impresso = imprimirProximo(&fila_de_impressao);
                mostrarDocumentoImpresso(documento_impresso);
            }
            break;
        }

        case 3:
            if (estaVazia(&fila_de_impressao))
            {
                printf("\nA fila de impressão está vazia!\n");
            }
            else
            {
                mostrarFilaDeImpressao(&fila_de_impressao);
            }
            break;

        case 0:
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}