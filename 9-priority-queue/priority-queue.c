#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Paciente
{
    char nome[100];
    int senha;
    char prioridade[20];
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

        switch (nivel_prioridade)
        {
        case 1:
            strcpy(paciente.prioridade, "Emergência");
            break;

        case 2:
            strcpy(paciente.prioridade, "Urgente");
            break;

        case 3:
            strcpy(paciente.prioridade, "Preferencial");
            break;

        case 4:
            strcpy(paciente.prioridade, "Normal");
            break;
        
        default:
            printf("Opção inválida!\n");
        }
    } while (nivel_prioridade != 1 && nivel_prioridade != 2 && nivel_prioridade != 3 && nivel_prioridade != 4);
    
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

int verificarPrioridade(Paciente paciente)
{
    if (strcmp(paciente.prioridade, "Emergência") == 0)
    {
        return 1;
    }
    else if (strcmp(paciente.prioridade, "Urgente") == 0)
    {
        return 2;
    }
    else if (strcmp(paciente.prioridade, "Preferencial") == 0)
    {
        return 3;
    }
    else
    {
        return 4;
    }
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

    No *atual = fila->frente;

    // Se o paciente for prioridade Emergência
    if (verificarPrioridade(no->dados) == 1)
    {
        while (atual != NULL)
        {
            // Se for o primeiro com prioridade Emergência na fila
            if (verificarPrioridade(atual->dados) != 1)
            {
                no->proximo = fila->frente;
                fila->frente = no;
                printf("\nPaciente adicionado à fila com sucesso!\n");
                return;
            }

            // Se só houver um paciente na fila
            if (atual->proximo == NULL)
            {
                atual->proximo = no;
                printf("\nPaciente adicionado à fila com sucesso!\n");
                return;
            }

            // Se houver outros com prioridade Emergência, é adicionado como o último com tal prioridade
            if (verificarPrioridade(atual->proximo->dados) != 1)
            {
                No *proximo = atual->proximo;
                atual->proximo = no;
                no->proximo = proximo;
                printf("\nPaciente adicionado à fila com sucesso!\n");
                return;
            }

            atual = atual->proximo;
        }
    }

    // Se o paciente for prioridade Urgente
    if (verificarPrioridade(no->dados) == 2)
    {
        // Se o paciente for o que tiver a maior prioridade
        if (verificarPrioridade(atual->dados) > 2)
        {
            no->proximo = atual;
            fila->frente = no;
            printf("\nPaciente adicionado à fila com sucesso!\n");
            return;
        }

        // Se houver outros com prioridade maior ou mesma prioridade, percorre eles
        if (verificarPrioridade(atual->dados) <= 2)
        {
            No *anterior;

            while (verificarPrioridade(atual->dados) <= 2)
            {
                anterior = atual;
                atual = atual->proximo;

                if (atual == NULL)
                    break;
            }

            anterior->proximo = no;
            no->proximo = atual;
            printf("\nPaciente adicionado à fila com sucesso!\n");
            return;
        }
    }

    // Se o paciente for prioridade Preferencial
    if (verificarPrioridade(no->dados) == 3)
    {
        // Se o paciente for o que tiver a maior prioridade
        if (verificarPrioridade(atual->dados) > 3)
        {
            no->proximo = atual;
            fila->frente = no;
            printf("\nPaciente adicionado à fila com sucesso!\n");
            return;
        }

        // Se houver outros com prioridade maior ou mesma prioridade, percorre eles
        if (verificarPrioridade(atual->dados) <= 3)
        {
            No *anterior;

            while (verificarPrioridade(atual->dados) <= 3)
            {
                anterior = atual;
                atual = atual->proximo;

                if (atual == NULL)
                    break;
            }

            anterior->proximo = no;
            no->proximo = atual;
            printf("\nPaciente adicionado à fila com sucesso!\n");
            return;
        }
    }

    // Se o paciente for prioridade Normal
    if (verificarPrioridade(no->dados) == 4)
    {
        No *anterior;

        // Percorre toda a lista
        while (verificarPrioridade(atual->dados) <= 4)
        {
            anterior = atual;
            atual = atual->proximo;

            if (atual == NULL)
                break;
        }

        anterior->proximo = no;
        printf("\nPaciente adicionado à fila com sucesso!\n");
        return;
    }
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

    No *atual = fila->frente;
    printf("\nAguardando na fila:\n");
    while (atual != NULL)
    {
        printf("\n%03d - %s - %s\n", atual->dados.senha, atual->dados.nome, atual->dados.prioridade);
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