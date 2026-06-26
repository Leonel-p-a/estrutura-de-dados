#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Musica
{
    char nome[100];
    char autor[100];
} Musica;

typedef struct No
{
    Musica musica;
    struct No *proximo;
} No;

typedef struct Lista
{
    No *inicio;
    No *fim;
    No *atual;
} Lista;

Musica salvarMusica()
{
    Musica musica;

    printf("Digite o Nome da Música: ");
    fgets(musica.nome, 100, stdin);
    musica.nome[strcspn(musica.nome, "\n")] = '\0';

    printf("Digite o(a) autor(a) da Música: ");
    fgets(musica.autor, 100, stdin);
    musica.autor[strcspn(musica.autor, "\n")] = '\0';

    return musica;
}

No *criarNo(Musica musica)
{
    No *novo_no = malloc(sizeof(No));

    if (novo_no == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

    novo_no->musica = musica;
    novo_no->proximo = NULL;

    return novo_no;
}

void adicionarMusicaAPlaylist(Lista *lista, Musica musica)
{
    No *no = criarNo(musica);

    if (no == NULL)
        return;

    if (lista->inicio == NULL)
    {
        lista->inicio = no;
        lista->fim = no;
        no->proximo = lista->inicio;
        lista->atual = no;
    }
    else
    {
        no->proximo = lista->inicio;
        lista->fim->proximo = no;
        lista->fim = no;
    }

    printf("Música adicionada à sua playlist!\n");
}

void listarPlaylist(Lista *lista)
{
    if (lista->inicio == NULL)
    {
        printf("Playlist vazia\nAdicione algumas músicas\n");
        return;
    }

    No *atual = lista->inicio;

    printf("\nSua playlist\n");

    do
    {
        printf("=================================\n");
        printf("%s - %s\n", atual->musica.nome, atual->musica.autor);
        atual = atual->proximo;
    } while (atual != lista->inicio);
    printf("=================================\n");
}

No *proximaMusica(Lista *lista)
{
    if(lista->inicio == NULL)
    {
        printf("Playlist vazia. Adicione suas músicas favoritas à sua playlist e se divirta\n");
        return NULL;
    }

    return lista->atual->proximo;
}

void musicaAtual(No *musica)
{
    printf("\n~~~~MUSIC PLAYER~~~~\n");
    printf("\n... MÚSICA TOCANDO ...\n");
    printf("%s\n(%s)\n", musica->musica.nome, musica->musica.autor);
}

No *buscarMusica(Lista *lista, char musica_nome[], char musica_autor[])
{
    No *atual = lista->inicio;

    if (lista->inicio == NULL)
    {
        printf("\nNenhuma música na sua playlist!\n");
        return NULL;
    }

    do
    {
        if (strcmp(atual->musica.nome, musica_nome) == 0 && strcmp(atual->musica.autor, musica_autor) == 0)
        {
            return atual;
        }

        atual = atual->proximo;
    } while (atual != lista->inicio);

    printf("\nMúsica não encontrada!\n");
    return NULL;
}

void removerMusica(Lista *lista, No *musica)
{
    if (musica == NULL || lista->inicio == NULL)
        return;

    No *atual = lista->inicio;
    No *anterior = lista->fim;

    do
    {
        if (atual == musica)
        {
            // Se for nó unico
            if (lista->inicio == lista->fim)
            {
                free(atual);
                lista->inicio = NULL;
                lista->fim = NULL;
                lista->atual = NULL;
                printf("Música removida da sua playlist\n");
                return;
            }

            // Se for o primeiro nó
            if (atual == lista->inicio)
            {
                lista->inicio = atual->proximo;
                lista->fim->proximo = lista->inicio;
                if (atual == lista->atual)
                {
                    lista->atual = atual->proximo;
                }
                free(atual);
                printf("Música removida da sua playlist\n");
                return;
            }
            
            // Se for o último nó
            if (atual == lista->fim)
            {
                lista->fim = anterior;
                lista->fim->proximo = lista->inicio;
                if (atual == lista->atual)
                {
                    lista->atual = atual->proximo;
                }
                free(atual);
                printf("Música removida da sua playlist\n");
                return;
            }
    
            // Se for intermediário
            anterior->proximo = atual->proximo;
            if (atual == lista->atual)
            {
                lista->atual = atual->proximo;
            }
            free(atual);
            printf("Música removida da sua playlist\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo; 
    } while (atual != lista->inicio);
}

void liberarLista(Lista *lista)
{
    No *atual = lista->inicio;

    do
    {
        No *temporario = atual;
        atual = atual->proximo;
        free(temporario);
    } while (atual != lista->inicio);

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->atual = NULL;
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Lista lista_circular = {NULL, NULL, NULL};
    int opcao;

    do
    {
        if (lista_circular.atual != NULL)
        {
            musicaAtual(lista_circular.atual);
        }

        printf("\n====== MENU ======\n");
        printf("1 - Adicionar música à playlist\n");
        printf("2 - Listar playlist\n");
        printf("3 - Próxima música\n");
        printf("4 - Remover música da playlist\n");
        printf("0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (opcao)
        {
        case 1:
            Musica musica = salvarMusica();
            adicionarMusicaAPlaylist(&lista_circular, musica);
            break;

        case 2:
            listarPlaylist(&lista_circular);
            break;

        case 3:
            lista_circular.atual = proximaMusica(&lista_circular);
            break;

        case 4:
        {
            char musica_nome[100];
            char musica_autor[100];

            printf("Digite o Nome da Música: ");
            fgets(musica_nome, 100, stdin);
            musica_nome[strcspn(musica_nome, "\n")] = '\0';

            printf("Digite o(a) autor(a) da Música: ");
            fgets(musica_autor, 100, stdin);
            musica_autor[strcspn(musica_autor, "\n")] = '\0';

            No *musica_buscada = buscarMusica(&lista_circular, musica_nome, musica_autor);
            removerMusica(&lista_circular, musica_buscada);
            break;
        }

        case 0:
            liberarLista(&lista_circular);
            printf("Fechando Music Player...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}