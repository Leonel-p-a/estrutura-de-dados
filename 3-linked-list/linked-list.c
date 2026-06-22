#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Usuario
{
    char primeiro_nome[30];
    char sobrenome[20];
    int idade;
} Usuario;

typedef struct No
{
    Usuario usuario;
    struct No *proximo;
} No;

typedef struct Lista
{
    No *inicio;
} Lista;

// Cria a cabeça da lista
Lista listaUsuarios = { NULL };

Usuario criarUsuario()
{
    // Cria uma variável do tipo struct Usuario
    Usuario usuario;

    // Atribui o valor ao campo primeiro_nome de usuario
    printf("Digite o Primeiro Nome do usuário: ");
    fgets(usuario.primeiro_nome, 29, stdin);
    usuario.primeiro_nome[strcspn(usuario.primeiro_nome, "\n")] = '\0';

    // Atribui o valor ao campo sobrenome de usuario
    printf("Digite o Sobrenome do usuário: ");
    fgets(usuario.sobrenome, 19, stdin);
    usuario.sobrenome[strcspn(usuario.sobrenome, "\n")] = '\0';

    // Atribui o valor ao campo idade de usuario
    printf("Digite a idade do usuário: ");
    scanf("%d", &usuario.idade);

    // Retorna um dado do tipo struct Usuario, que é o usuário criado
    return usuario;
}

void inserirUsuario(Usuario usuario) // Recebe o usuário criado na função criarUsuario
{
    // Cria um nó na memória
    No *novo_no = malloc(sizeof(No));

    // Verifica alocação de memória
    if (novo_no == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }
    // Atribui os valores do nó
    strcpy(novo_no->usuario.primeiro_nome, usuario.primeiro_nome);
    strcpy(novo_no->usuario.sobrenome, usuario.sobrenome);
    novo_no->usuario.idade = usuario.idade;
    novo_no->proximo = NULL;

    // Se a lista estiver vazia, atribui o nó criado ao início da lista
    if (listaUsuarios.inicio == NULL)
    {
        listaUsuarios.inicio = novo_no;
    }
    // Se a lista já tiver dados, percorre a lista para inserir o novo dado ao final da lista
    else
    {
        No *atual = listaUsuarios.inicio;

        // Percorre a lista
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        // Atribui o novo_no ao final da lista
        atual->proximo = novo_no;
    }

    printf("\nUsuário cadastrado com sucesso!\n");
}

// Insere usuário no início da lista
void inserirUsuarioInicio(Usuario usuario)
{
    // Cria um nó na memória
    No *novo_no = malloc(sizeof(No));

    // Verifica alocação de memória
    if (novo_no == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }
    // Atribui os valores do nó
    strcpy(novo_no->usuario.primeiro_nome, usuario.primeiro_nome);
    strcpy(novo_no->usuario.sobrenome, usuario.sobrenome);
    novo_no->usuario.idade = usuario.idade;


    if (listaUsuarios.inicio == NULL)
    {
        novo_no->proximo = NULL;
        listaUsuarios.inicio = novo_no;

        return;
    }

    novo_no->proximo = listaUsuarios.inicio;
    listaUsuarios.inicio = novo_no;

    printf("\nUsuário cadastrado com sucesso!\n");
}

No* buscarUsuario()
{
    // Atribui o início da lista à variável (ponteiro) temporária atual
    No *atual = listaUsuarios.inicio;

    // Variáveis para guardar a entrada do usuário para primeiro nome e sobrenome
    char primeiro_nome[30];
    char sobrenome[20];

    // Atribui a entrada do usuário às variáveis
    printf("Qual o Primeiro Nome do usuario: ");
    fgets(primeiro_nome, 29, stdin);
    primeiro_nome[strcspn(primeiro_nome, "\n")] = '\0';

    printf("Qual o Sobrenome do usuario: ");
    fgets(sobrenome, 19, stdin);
    sobrenome[strcspn(sobrenome, "\n")] = '\0';

    // Verifica se a lista está vazia, se estiver, retorna NULL
    if (listaUsuarios.inicio == NULL)
    {
        printf("\nNenhum usuário cadastrado!\n");
        return NULL;
    }

    // Percorre a lista
    while (atual != NULL)
    {
        // Se encontrar o valor (usuário) buscado, retorna um ponteiro para este valor
        if (strcmp(atual->usuario.primeiro_nome, primeiro_nome) == 0 && strcmp(atual->usuario.sobrenome, sobrenome) == 0)
        {
            return atual;
        }

        atual = atual->proximo;
    }

    // Ao percorrer a lista inteira, se não achar o valor buscado, retorna NULL
    printf("\nUsuário não encontrado!\n");
    return NULL;
}

void excluirUsuario(No *usuario)
{
    // Verifica se a busca retornou um usuário válido, se não, encerra a função sem exclusão
    if (usuario == NULL)
    {
        return;
    }

    // Variável (ponteiro) temporária para a cabeça da lista e auxiliar para ajustar ponteiros da lista
    No *atual = listaUsuarios.inicio;
    No *anterior = NULL;

    // Percorre a lista até o usuário (nó) a ser removido
    while (atual != NULL)
    {
        if (strcmp(atual->usuario.primeiro_nome, usuario->usuario.primeiro_nome) == 0 && strcmp(atual->usuario.sobrenome, usuario->usuario.sobrenome) == 0)
        {
            if (anterior == NULL)
            {
                listaUsuarios.inicio = atual->proximo;
            }
            else
            {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            printf("\nUsuário excluído com sucesso!\n");
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }
}

void alterarUsuario(No *usuario)
{
    // Verifica se a busca retornou um usuário válido, se não, encerra a função
    if (usuario == NULL)
    {
        return;
    }

    // Variável (ponteiro) temporária para a cabeça da lista
    No *atual = listaUsuarios.inicio;

    // Percorre a lista até o usuário (nó) a ser alterado
    while (atual != NULL)
    {
        if (strcmp(atual->usuario.primeiro_nome, usuario->usuario.primeiro_nome) == 0 && strcmp(atual->usuario.sobrenome, usuario->usuario.sobrenome) == 0)
        {
            printf("\nQual dado você quer alterar do usuário \"%s\"\n", atual->usuario.primeiro_nome);

            int opcao;

            do
            {
                printf("\nESCOLHA:\n");
                printf("1 - Primeiro Nome\n");
                printf("2 - Sobrenome\n");
                printf("3 - Idade\n");
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
                    char novo_primeiro_nome[30];

                    printf("Digite o novo Primeiro Nome: ");
                    fgets(novo_primeiro_nome, 30, stdin);
                    strcpy(atual->usuario.primeiro_nome, novo_primeiro_nome);
                    atual->usuario.primeiro_nome[strcspn(atual->usuario.primeiro_nome, "\n")] = '\0';
                    printf("Primeiro Nome alterado com sucesso!\n");
                    break;
                }

                case 2:
                {
                    char novo_sobrenome[20];

                    printf("Digite o novo Sobrenome: ");
                    fgets(novo_sobrenome, 20, stdin);
                    strcpy(atual->usuario.sobrenome, novo_sobrenome);
                    atual->usuario.sobrenome[strcspn(atual->usuario.sobrenome, "\n")] = '\0';
                    printf("Sobrenome alterado co sucesso!\n");
                    break;
                }

                case 3:
                {
                    int nova_idade;

                    printf("Digite a nova Idade: ");
                    scanf("%d", &nova_idade);

                    atual->usuario.idade = nova_idade;

                    printf("Idade alterada com sucesso!\n");
                    break;
                }

                case 0:
                    printf("Voltando ao Menu Inicial...\n");
                    break;

                default:
                    printf("Opção inválida!\n");
                }

            } while (opcao != 0);
            
            return;
        }

        atual = atual->proximo;
    }
}

void listarUsuarios(No *inicio) // Recebe a cabeça da lista
{
    // Verifica se a lista está vazia
    if (inicio == NULL)
    {
        printf("Nenhum usuário cadastrado!\n");
        return;
    }

    // Atribui o início da lista à variável (ponteiro) temporária atual
    No *atual = inicio;

    // Declara uma variável auxiliar contadora e atribui o valor 1
    int contador = 1;

    printf("\nUsuários cadastrados:\n");

    // Percorre a lista até o final (NULL) e exibe os dados dos usuários
    while (atual != NULL)
    {
        printf("%d - %s %s - %d anos\n", contador, atual->usuario.primeiro_nome, atual->usuario.sobrenome, atual->usuario.idade);
        atual = atual->proximo;

        contador++;
    }
}

// Liberar memória
void liberarLista()
{
    No *atual = listaUsuarios.inicio;

    while (atual != NULL)
    {
        No *temporario = atual;

        atual = atual->proximo;

        free(temporario);
    }

    listaUsuarios.inicio = NULL;
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcao;

    do
    {
        printf("\n====== MENU ======\n");
        printf("1 - Cadastrar usuário\n");
        printf("2 - Excluir usuário cadastrado\n");
        printf("3 - Alterar usuário cadastrado\n");
        printf("4 - Listar usuários cadastrados\n");
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
            Usuario novo_usuario = criarUsuario();

            int resposta;

            do
            {
                printf("\nInserir o usuário cadastrado:\n");
                printf("1 - No início da lista\n");
                printf("2 - No final da lista\n");
                printf("\nEscolha: ");
                scanf("%d", &resposta);

                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;

                switch (resposta)
                {
                case 1:
                    inserirUsuarioInicio(novo_usuario);
                    break;

                case 2:
                    inserirUsuario(novo_usuario);
                    break;
                
                default:
                    printf("Opção inválida!\n");
                }
            } while (resposta != 1 && resposta != 2);

            break;
        }

        case 2:
        {
            No *usuario = buscarUsuario();
            excluirUsuario(usuario);
            break;
        }

        case 3:
            No *usuario = buscarUsuario();
            alterarUsuario(usuario);
            break;

        case 4:
            listarUsuarios(listaUsuarios.inicio);
            break;

        case 0:
            liberarLista();
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}