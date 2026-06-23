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
    No *fim;
} Lista;

typedef struct ResultadoBusca
{
    No *anterior;
    No *atual;
} ResultadoBusca;

Usuario criarUsuario()
{
    // Cria uma variável do tipo struct Usuario
    Usuario usuario;

    // Atribui o valor ao campo primeiro_nome de usuario
    printf("Digite o Primeiro Nome do usuário: ");
    fgets(usuario.primeiro_nome, 30, stdin);
    usuario.primeiro_nome[strcspn(usuario.primeiro_nome, "\n")] = '\0';

    // Atribui o valor ao campo sobrenome de usuario
    printf("Digite o Sobrenome do usuário: ");
    fgets(usuario.sobrenome, 20, stdin);
    usuario.sobrenome[strcspn(usuario.sobrenome, "\n")] = '\0';

    // Atribui o valor ao campo idade de usuario
    printf("Digite a idade do usuário: ");
    scanf("%d", &usuario.idade);

    // Retorna um dado do tipo struct Usuario, que é o usuário criado
    return usuario;
}

// Cria nó na memória dinâmica
No *criarNo(Usuario usuario)
{
    // Cria novo nó na memória
    No *novo_no = malloc(sizeof(No));

    // Verifica alocação de memória
    if (novo_no == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }

    // Atribui os valores do nó e retorna o nó
    novo_no->usuario = usuario;

    return novo_no;
}

// Insere usuário ao final da lista
void inserirUsuario(Lista *lista, Usuario usuario) // Recebe o usuário criado na função criarUsuario
{
    // Cria um nó na memória
    No *novo_no = criarNo(usuario);

    if (novo_no == NULL)
    {
        return;
    }

    // Se a lista estiver vazia, faz o inicio e final da lista apontarem para o nó criado
    if (lista->inicio == NULL)
    {
        lista->inicio = novo_no;
        lista->fim = novo_no;
    }
    // Se a lista já tiver dados
    else
    {
        // o anttigo último nó da lista agora aponta para o novo nó
        lista->fim->proximo = novo_no;
        // faz o final da lista apontar para o novo último nó
        lista->fim = novo_no;
    }

    printf("\nUsuário cadastrado com sucesso!\n");
}

// Insere usuário no início da lista
void inserirUsuarioInicio(Lista *lista, Usuario usuario) // Recebe o usuário criado na função criarUsuario
{
    // Cria um nó na memória
    No *novo_no = criarNo(usuario);

    if (novo_no == NULL)
    {
        return;
    }

    // Verifica se a lista está vazia e, se sim, faz o primeiro nó apontar para NULL (ou seja, o primeiro nó é também o último)
    if (lista->inicio == NULL)
    {
        lista->inicio = novo_no;
        lista->fim = novo_no;

        printf("\nUsuário cadastrado com sucesso!\n");

        return;
    }

    // Ajusta os ponteiros
    novo_no->proximo = lista->inicio;
    lista->inicio = novo_no;

    printf("\nUsuário cadastrado com sucesso!\n");
}

// Busca e retorna o usuário buscado
ResultadoBusca buscarUsuario(Lista *lista) // Retorna um dado do tipo ResultadoBusca ({No *anterior; No *atual})
{
    // Atribui o início da lista à variável (ponteiro) temporária atual e cria um ponteiro para o nó anterior
    No *atual = lista->inicio;
    No *anterior = NULL;

    ResultadoBusca resultado_busca = { anterior, atual };

    // Variáveis para guardar a entrada do usuário para primeiro nome e sobrenome
    char primeiro_nome[30];
    char sobrenome[20];

    // Atribui a entrada do usuário às variáveis
    printf("Qual o Primeiro Nome do usuario: ");
    fgets(primeiro_nome, 30, stdin);
    primeiro_nome[strcspn(primeiro_nome, "\n")] = '\0';

    printf("Qual o Sobrenome do usuario: ");
    fgets(sobrenome, 20, stdin);
    sobrenome[strcspn(sobrenome, "\n")] = '\0';

    // Verifica se a lista está vazia, se estiver, retorna os campos do dado sendo NULL
    if (lista->inicio == NULL)
    {
        printf("\nNenhum usuário cadastrado!\n");
        return resultado_busca;
    }

    // Percorre a lista
    while (atual != NULL)
    {
        // Se encontrar o valor (usuário) buscado, retorna um dado do tipo ResultadoBusca com ponteiro para o dado atual e o seu anterior
        if (strcmp(atual->usuario.primeiro_nome, primeiro_nome) == 0 && strcmp(atual->usuario.sobrenome, sobrenome) == 0)
        {
            resultado_busca.anterior = anterior;
            resultado_busca.atual = atual;
            return resultado_busca;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    resultado_busca.anterior = NULL;
    resultado_busca.atual = NULL;
    // Ao percorrer a lista inteira, se não achar o valor buscado, retorna NULL
    printf("\nUsuário não encontrado!\n");
    return resultado_busca;
}

// Exclui o usuário retornado pela função buscarUsuario
void excluirUsuario(Lista *lista, ResultadoBusca usuario)
{
    // Verifica se a busca retornou um usuário válido, se não, encerra a função sem exclusão
    if (usuario.atual == NULL)
    {
        return;
    }

    // Variável (ponteiro) temporária para a cabeça da lista e auxiliar para ajustar ponteiros da lista
    No *atual = usuario.atual;
    No *anterior = usuario.anterior;

    // Se o usuário a ser excluído for o primeiro, atribui o proximo usuário como o início da lista
    if (anterior == NULL)
    {
        lista->inicio = atual->proximo;

        // Se só tiver um usuário, agora o final da lista não aponta para nenhum nó (usuário)
        if (atual == lista->fim)
        {
            lista->fim = NULL;
        }
    }
    else
    {
        // ajusta o ponteiro do usuário anterior para apontar para o próximo do que foi excluído
        anterior->proximo = atual->proximo;
    
        // Se o usuário a ser excluído for o último, atribui o anterior (novo último usuário) como o último da lista (fim)
        if (atual == lista->fim)
        {
            lista->fim = anterior;
        }
    }

    free(atual);
    printf("\nUsuário excluído com sucesso!\n");
}

// Altera o usuário buscado na função buscarUsuario
void alterarUsuario(ResultadoBusca usuario)
{
    // Verifica se a busca retornou um usuário válido, se não, encerra a função
    if (usuario.atual == NULL)
    {
        return;
    }

    printf("\nQual dado você quer alterar do usuário \"%s\"\n", usuario.atual->usuario.primeiro_nome);

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
            strcpy(usuario.atual->usuario.primeiro_nome, novo_primeiro_nome);
            usuario.atual->usuario.primeiro_nome[strcspn(usuario.atual->usuario.primeiro_nome, "\n")] = '\0';
            printf("Primeiro Nome alterado com sucesso!\n");
            break;
        }

        case 2:
        {
            char novo_sobrenome[20];

            printf("Digite o novo Sobrenome: ");
            fgets(novo_sobrenome, 20, stdin);
            strcpy(usuario.atual->usuario.sobrenome, novo_sobrenome);
            usuario.atual->usuario.sobrenome[strcspn(usuario.atual->usuario.sobrenome, "\n")] = '\0';
            printf("Sobrenome alterado co sucesso!\n");
            break;
        }

        case 3:
        {
            int nova_idade;

            printf("Digite a nova Idade: ");
            scanf("%d", &nova_idade);

            usuario.atual->usuario.idade = nova_idade;

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
}

// recebe o ponteiro do início da lista e imprime os usuários cadastrados
void listarUsuarios(Lista *lista) // Recebe a cabeça da lista
{
    // Verifica se a lista está vazia
    if (lista->inicio == NULL)
    {
        printf("Nenhum usuário cadastrado!\n");
        return;
    }

    // Atribui o início da lista à variável (ponteiro) temporária atual
    No *atual = lista->inicio;

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
void liberarLista(Lista *lista)
{
    No *atual = lista->inicio;

    while (atual != NULL)
    {
        No *temporario = atual;

        atual = atual->proximo;

        free(temporario);
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Cria a cabeça da lista
    Lista lista_usuarios = { NULL, NULL };

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
                    inserirUsuarioInicio(&lista_usuarios, novo_usuario);
                    break;

                case 2:
                    inserirUsuario(&lista_usuarios, novo_usuario);
                    break;
                
                default:
                    printf("Opção inválida!\n");
                }
            } while (resposta != 1 && resposta != 2);

            break;
        }

        case 2:
        {
            ResultadoBusca usuario = buscarUsuario(&lista_usuarios);
            excluirUsuario(&lista_usuarios, usuario);
            break;
        }

        case 3:
            ResultadoBusca usuario = buscarUsuario(&lista_usuarios);
            alterarUsuario(usuario);
            break;

        case 4:
            listarUsuarios(&lista_usuarios);
            break;

        case 0:
            liberarLista(&lista_usuarios);
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}