#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

#define ALFABETO 26

typedef struct No
{
    char caractere;
    bool fimDePalavra;
    struct No *filhos[ALFABETO];
} No;

No *criarNo(char caractere)
{
    No *novo = malloc(sizeof(No));

    if (novo == NULL)
        return NULL;

    novo->caractere = caractere;
    novo->fimDePalavra = false;

    for (int i = 0; i < ALFABETO; i++)
    {
        novo->filhos[i] = NULL;
    }

    return novo;
}

void inserir(No *raiz, const char *palavra)
{
    int tamanho_palavra = 0;

    while (palavra[tamanho_palavra])
    {
        tamanho_palavra++;
    }
    
    No *atual = raiz;

    for (int i = 0; i < tamanho_palavra; i++)
    {
        int indice = palavra[i] - 'a';

        if (atual->filhos[indice] == NULL)
        {
            atual->filhos[indice] = criarNo(palavra[i]);
        }

        atual = atual->filhos[indice];
    }

    atual->fimDePalavra = true;
}

bool buscar(No *raiz, const char *palavra)
{
    int tamanho_palavra = 0;

    while (palavra[tamanho_palavra])
    {
        tamanho_palavra++;
    }
    
    No *atual = raiz;

    for (int i = 0; i < tamanho_palavra; i++)
    {
        int indice = palavra[i] - 'a';

        if (atual->filhos[indice] == NULL)
            return false;

        atual = atual->filhos[indice];
    }

    return atual->fimDePalavra;
}

// FUNÇÃO REMOÇÃO SUGERIDA POR IA

No *removerRecursivo(No *atual, const char *palavra, int indice)
{
    if (palavra[indice] != '\0')
    {
        int indice_letra = palavra[indice] - 'a';

        if (atual->filhos[indice_letra] != NULL)
        {
            atual->filhos[indice_letra] = removerRecursivo(atual->filhos[indice_letra], palavra, indice + 1);
        }
    }

    // Verifica seo nó possui algum filho
    bool possui_filhos = false;

    for (int i = 0; i < ALFABETO; i++)
    {
        if (atual->filhos[i] != NULL)
        {
            possui_filhos = true;
            break;
        }
    }

    // Se possui filhos, não remove o nó
    if (possui_filhos)
    {
        atual->fimDePalavra = false;
        return atual;
    }

    // Se não é fim de palavra e não possui filhos,
    // palavra não existe, não remove o nó
    if (!atual->fimDePalavra)
        return atual;

    // Se é fim de palavra e não possui filhos,
    // remove o nó
    free(atual);
    return NULL;
}

bool removerPalavra(No *raiz, const char *palavra)
{
    if (!buscar(raiz, palavra))
    {
        return false;
    }

    /*
        A função de remoção recursiva recebe o primeiro caractere (ao invés da raiz).
        Assim, a raiz nunca é liberada
    */
    int indice = palavra[0] - 'a';

    raiz->filhos[indice] = removerRecursivo(raiz->filhos[indice], palavra, 1);

    return true;
}

// FUNÇÃO ORIGINAL QUE DESENVOLVI

// No *remover(No *atual, const char *palavra, int indice)
// {
//     No *auxiliar = atual;

//     if (palavra[indice] != '\0')
//     {
//         int indice_letra = palavra[indice] - 'a';

//         if (auxiliar->filhos[indice_letra] != NULL)
//         {
//             indice++;
//             auxiliar->filhos[indice_letra] = remover(auxiliar->filhos[indice_letra], palavra, indice);
//         }
//     }

//     bool possui_filhos = false;

//     for (int i = 0; i < ALFABETO; i++)
//     {
//         if (auxiliar->filhos[i] != NULL)
//         {
//             possui_filhos = true;
//             break;
//         }
//     }

//     // É prefixo de outra palavra (possui filhos), não remove nó
//     if (possui_filhos)
//     {
//         auxiliar->fimDePalavra = false;
//         return auxiliar;
//     }
//     else
//     {
//         // Palavra não existe, não remove nó
//         if (!auxiliar->fimDePalavra)
//         {
//             return auxiliar;
//         }

//         // É fim de palavra enão possui filhos, remove nó
//         free(auxiliar);
//         return NULL;
//     }
// }

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    No *raiz = criarNo('\0');

    int opcao;

    do
    {
        printf("\n====== MENU ======\n");
        printf("1 - Inserir palavra\n");
        printf("2 - Buscar palavra\n");
        printf("3 - Remover palavra\n");
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
            char palavra[100];

            printf("\nDigite uma palavra: ");
            fgets(palavra, sizeof(palavra), stdin);
            palavra[strcspn(palavra, "\n")] = '\0';

            if (strlen(palavra) > 0)
            {
                inserir(raiz, palavra);
                printf("\nPalavra inserida com sucesso!\n");
            }
            else
            {
                printf("\nNenhuma palavra digitada!\n");
            }
            
            break;
        }

        case 2:
        {
            char palavra[100];

            printf("\nDigite uma palavra: ");
            fgets(palavra, sizeof(palavra), stdin);
            palavra[strcspn(palavra, "\n")] = '\0';

            if (strlen(palavra) > 0)
            {
                if (buscar(raiz, palavra))
                {
                    printf("\nPalavra encontrada: %s\n", palavra);
                }
                else
                {
                    printf("\nPalavra não encontrada: %s\n", palavra);
                }
            }
            else
            {
                printf("\nNenhuma palavra digitada!\n");
            }

            break;
        }

        case 3:
        {
            char palavra[100];

            printf("\nDigite uma palavra: ");
            fgets(palavra, sizeof(palavra), stdin);
            palavra[strcspn(palavra, "\n")] = '\0';

            if (strlen(palavra) > 0)
            {
                if (removerPalavra(raiz, palavra))
                {
                    printf("\nPalavra removida com sucesso!\n");
                }
                else
                {
                    printf("\nPalavra não existe!\n");
                }
            }
            else
            {
                printf("\nNenhuma palavra digitada!\n");
            }

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