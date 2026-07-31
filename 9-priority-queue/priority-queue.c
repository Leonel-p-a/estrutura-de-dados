#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Paciente
{
    char nome[100];
    int senha;
    int prioridade;
} Paciente;

typedef struct No
{
    Paciente dados;
    struct No *proximo;
} No;

typedef struct FilaPrioridade
{
    No *frente;
    int senha;
} FilaPrioridade;

int criarSenha(FilaPrioridade *fila)
{
    return ++(fila->senha);
}

Paciente criarPaciente(FilaPrioridade *fila)
{
    Paciente paciente;

    printf("\nDigite o nome do paciente: ");
    fgets(paciente.nome, 50, stdin);
    paciente.nome[strcspn(paciente.nome, "\n")] = '\0';

    paciente.senha = criarSenha(fila);

    int nivel_prioridade;

    do
    {        
        printf("\nInforme o nível de prioridade do paciente %s: \n", paciente.nome);
        printf("1 - Emergência\n");
        printf("2 - Urgente\n");
        printf("3 - Preferencial\n");
        printf("4 - Normal\n");
        printf("\nNível: ");
        scanf("%d", &nivel_prioridade);

        if (nivel_prioridade < 1 || nivel_prioridade > 4)
            printf("Opção inválida\n");
    } while (nivel_prioridade < 1 || nivel_prioridade > 4);

    paciente.prioridade = nivel_prioridade;
    
    return paciente;
}

No* criarNo(Paciente paciente)
{
    No *no = malloc(sizeof(No));

    if (no == NULL)
    {
        printf("\nErro de memória!\n");
        return NULL;
    }

    no->dados = paciente;
    no->proximo = NULL;

    return no;
}

void adicionarPaciente(FilaPrioridade *fila, Paciente paciente)
{
    No *no = criarNo(paciente);

    if (no == NULL)
    {
        return;
    }

    // Se for o primeiro paciente da fila
    if (fila->frente == NULL)
    {
        fila->frente = no;
        printf("\nPaciente adicionado à fila com sucesso!\n");
        return;
    }

    if (paciente.prioridade < fila->frente->dados.prioridade)
    {
        no->proximo = fila->frente;
        fila->frente = no;

        printf("\nPaciente adicionado à fila com sucesso!\n");
        return;
    }

    No *atual = fila->frente;
    No *anterior = NULL;

    while (atual != NULL && atual->dados.prioridade <= paciente.prioridade)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    anterior->proximo = no;
    no->proximo = atual;
    printf("\nPaciente adicionado à fila com sucesso!\n");
    return;
}

int chamarProximoPaciente(FilaPrioridade *fila, Paciente *paciente)
{
    if (fila->frente == NULL)
    {
        printf("\nFila vazia\n");
        return 0;
    }

    if (fila->frente->proximo == NULL)
    {
        *paciente = fila->frente->dados;
        free(fila->frente);
        fila->frente = NULL;
        return 1;
    }

    *paciente = fila->frente->dados;
    No *auxiliar = fila->frente;
    fila->frente = fila->frente->proximo;
    free(auxiliar);

    return 1;
}

void mostrarPaciente(Paciente paciente)
{
    printf("\n=======================\n");
    printf("Chamando paciente para atendimento:\n\nSenha: %03d\nNome: %s", paciente.senha, paciente.nome);
    printf("\n=======================\n");
}

void mostrarFila(FilaPrioridade *fila)
{
    if (fila->frente == NULL)
    {
        printf("\nFila vazia\n");
        return;
    }

    char *prioridades[] =
    {
        "",
        "Emergência",
        "Urgente",
        "Preferencial",
        "Normal"
    };

    No *atual = fila->frente;
    printf("\nAguardando na fila:\n");
    while (atual != NULL)
    {
        printf("\n%03d - %s - %s\n", atual->dados.senha, atual->dados.nome, prioridades[atual->dados.prioridade]);
        atual = atual->proximo;
    }
}

void liberarFila(FilaPrioridade *fila)
{
    while (fila->frente != NULL)
    {
        No *atual = fila->frente;
        fila->frente = fila->frente->proximo;
        free(atual);
    }

    fila->frente = NULL;
}

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");

    FilaPrioridade fila_atendimentos = { NULL, 0 };
    int opcao;

    do
    {
        printf("\n====== MENU ======\n");
        printf("1 - Adicionar paciente à fila\n");
        printf("2 - Chamar próximo paciente\n");
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
            Paciente paciente = criarPaciente(&fila_atendimentos);
            adicionarPaciente(&fila_atendimentos, paciente);
            break;
        }

        case 2:
        {
            Paciente paciente;
            if (chamarProximoPaciente(&fila_atendimentos, &paciente))
            {
                mostrarPaciente(paciente);
            }
            break;
        }

        case 3:
            mostrarFila(&fila_atendimentos);
            break;

        case 0:
            liberarFila(&fila_atendimentos);
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}