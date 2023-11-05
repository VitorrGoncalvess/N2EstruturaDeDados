
/*
Usando conceito de lista duplamente encadeada construam uma agenda de contatos para guardar dados de nomes e telefones, 
neste sistema de agenda deve ter um menu com as seguintes opções: inserção de contato,
 consulta de contato, exclusão do contato, alteração do contato e lista de todos os contatos.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Contato {
    char nome[50];
    char telefone[15];
    struct Contato *anterior;
    struct Contato *proximo;
} Contato;

Contato *inserirContato(Contato *agenda);
void consultarContato(Contato *agenda);
Contato *excluirContato(Contato *agenda);
void alterarContato(Contato *agenda);
void listarContatos(Contato *agenda);
void liberarAgenda(Contato *agenda);

int main() {
    Contato *agenda = NULL;
    int opcao;

    do {
    	
        printf("\nMenu de Agenda\n");
        printf("1. Inserir Contato\n");
        printf("2. Consultar Contato\n");
        printf("3. Excluir Contato\n");
        printf("4. Alterar Contato\n");
        printf("5. Listar Contatos\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
            	system("cls");
                printf("Inserir contato. \n");
				agenda = inserirContato(agenda);
                break;
            case 2:
            	system("cls");
            	printf("Consultar contato. \n");
                consultarContato(agenda);
                break;
            case 3:
            	system("cls");
            	printf("Excluir contato. \n");
                agenda = excluirContato(agenda);
                break;
            case 4:
            	system("cls");
            	printf("Alterar Contato.\n");
                alterarContato(agenda);
                break;
            case 5:
            	system("cls");
            	printf("Listar Contatos.\n");
                listarContatos(agenda);
                break;
            case 6:
            	system("cls");
                liberarAgenda(agenda);
                printf("Encerrando o programa. Adeus!\n");
                break;
            default:
            	system("cls");
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}

Contato *inserirContato(Contato *agenda) {
    Contato *novoContato = (Contato *)malloc(sizeof(Contato));

    if (novoContato == NULL) {
        printf("Erro ao alocar memoria para o novo contato.\n");
        return agenda;
    }

    printf("Digite o nome do contato: ");
    fgets(novoContato->nome, sizeof(novoContato->nome), stdin);
    novoContato->nome[strlen(novoContato->nome) - 1] = '\0';

    printf("Digite o telefone do contato: ");
    fgets(novoContato->telefone, sizeof(novoContato->telefone), stdin);
    novoContato->telefone[strlen(novoContato->telefone) - 1] = '\0';

    novoContato->anterior = NULL;
    novoContato->proximo = agenda;

    if (agenda != NULL) {
        agenda->anterior = novoContato;
    }

    return novoContato;
}

void consultarContato(Contato *agenda) {
    char nome[50];
    printf("Digite o nome do contato para consulta: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = '\0';

    Contato *atual = agenda;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Nome: %s\n", atual->nome);
            printf("Telefone: %s\n", atual->telefone);
            return;
        }
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

Contato *excluirContato(Contato *agenda) {
    char nome[50];
    printf("Digite o nome do contato para exclusao: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = '\0';

    Contato *atual = agenda;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            Contato *anterior = atual->anterior;
            Contato *proximo = atual->proximo;

            if (anterior != NULL) {
                anterior->proximo = proximo;
            } else {
                agenda = proximo;
            }

            if (proximo != NULL) {
                proximo->anterior = anterior;
            }

            free(atual);
            printf("Contato excluido com sucesso.\n");
            return agenda;
        }
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
    return agenda;
}

void alterarContato(Contato *agenda) {
    char nome[50];
    printf("Digite o nome do contato para alteracao: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome) - 1] = '\0';

    Contato *atual = agenda;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Digite o novo nome do contato: ");
            fgets(atual->nome, sizeof(atual->nome), stdin);
            atual->nome[strlen(atual->nome) - 1] = '\0';

            printf("Digite o novo telefone do contato: ");
            fgets(atual->telefone, sizeof(atual->telefone), stdin);
            atual->telefone[strlen(atual->telefone) - 1] = '\0';

            printf("Contato alterado com sucesso.\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

void listarContatos(Contato *agenda) {
    if (agenda == NULL) {
        printf("A agenda esta vazia.\n");
        return;
    }

    printf("Contatos na agenda:\n");
    Contato *atual = agenda;
    while (atual != NULL) {
        printf("Nome: %s\n", atual->nome);
        printf("Telefone: %s\n\n", atual->telefone);
        atual = atual->proximo;
    }
}

void liberarAgenda(Contato *agenda) {
    while (agenda != NULL) {
        Contato *proximo = agenda->proximo;
        free(agenda);
        agenda = proximo;
    }
}

