#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int contador_matricula = 1;
int aluno_rm = 0;

struct Aluno{

    int Matricula;
    char Nome[255];
    char Criacao[26];
    struct Aluno *prox;
    struct Aluno *prev;
};

struct ListaDupla {
    struct Aluno *inicio;
    struct Aluno *fim;
};

void inserirInicio(struct ListaDupla *lista, char *nome) {
    struct Aluno *novo = malloc(sizeof(struct Aluno));

    novo->Matricula = contador_matricula++;
    strcpy(novo->Nome, nome);

    time_t agora = time(NULL);
    char *string_tempo = ctime(&agora);
    strcpy(novo->Criacao, string_tempo);
    novo->Criacao[strcspn(novo->Criacao, "\n")] = 0;

    novo->prox = lista->inicio;
    novo->prev = NULL;

    if (lista->inicio != NULL) {
        lista->inicio->prev = novo;
    } else {
        lista->fim = novo;
    }

    lista->inicio = novo;
};

void ExibirAluno(struct ListaDupla *lista) {
    struct Aluno *atual = lista->inicio;

    if (atual == NULL) {
        printf("A lista está vazia");
        return;
    }

    printf("\n --- Lista de Alunos --- \n");
    while (atual != NULL) {
        printf("Matrícula: %012d | Nome: %-20s | Criado em: %s\n",
               atual->Matricula, atual->Nome, atual->Criacao);
        atual = atual->prox;
    }
    printf("-------------------------\n");
}

void salvarArquivo(struct ListaDupla *lista) {
    FILE *arq = fopen("alunos.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo para salvar");
        return;
    }

    struct Aluno *atual = lista->inicio;
    while (atual != NULL) {
        fprintf(arq, "%d;%s;%s\n", atual->Matricula, atual->Nome, atual->Criacao);
        atual = atual->prox;
    }

    fclose(arq);
    printf("Dados salvos com sucesso!\n");
}

void carregarArquivo(struct ListaDupla *lista) {
    FILE *arq = fopen("alunos.txt", "r");
    if (arq == NULL) return;

    char nome[255], criacao[26];
    int matricula;


    while (fscanf(arq, "%d;%[^;];%[^\n]\n", &matricula, nome, criacao) != EOF) {
        struct Aluno *novo = malloc(sizeof(struct Aluno));
        novo->Matricula = matricula;
        strcpy(novo->Nome, nome);
        strcpy(novo->Criacao, criacao);

        novo->prox = NULL;
        novo->prev = lista->fim;
        if (lista->fim != NULL) lista->fim->prox = novo;
        else lista->inicio = novo;
        lista->fim = novo;

        if (matricula >= contador_matricula) {
            contador_matricula = matricula + 1;
        }
    }
    fclose(arq);
}

void removerAluno(struct ListaDupla *lista, int aluno_rm) {
    struct Aluno *atual = lista->inicio;


    while (atual != NULL && atual->Matricula != aluno_rm) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Aluno com matrícula %d não encontrado. \n", aluno_rm);
        return;
    }

    if (atual->prev != NULL) {
        atual->prev->prox = atual->prox;
    } else {
        lista->inicio = atual->prox;
    }

    if (atual->prox != NULL) {
        atual->prox->prev = atual->prev;
    } else {
        lista->fim = atual->prev;
    }

    free(atual);
    printf("Aluno removido com Sucesso!\n");
}

void modificarAluno(struct ListaDupla *lista, int matricula) {
    struct Aluno *atual = lista->inicio;
    char nome[255];

        while (atual != NULL && atual->Matricula != matricula) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Aluno com matrícula %d não encontrado. \n", matricula);
        return;
    }

    printf("Qual o novo nome de %s?\n", atual->Nome);
    scanf(" %[^\n]", nome);
    strcpy(atual->Nome, nome);
}


int main() {

    int escolha = 0;
    char nome[255];
    int matricula = 0;

    struct ListaDupla Alunos = {NULL, NULL};
    carregarArquivo(&Alunos);

    while (escolha != 5) {

        printf("Escolha uma opção:\n");
        printf("1 - Adicionar novo aluno.\n");
        printf("2 - Ver lista atual de alunos.\n");
        printf("3 - Remover um aluno.\n");
        printf("4 - Modificar um aluno.\n");
        printf("5 - Sair.\n");
        printf("----------- Sessão Gatos -----------\n");
        printf("6 - Ver gato 'OIIA'.\n");
        printf("7 - Ver gato tocando piano.\n");
        scanf( "%d", &escolha);


        switch (escolha) {
            case 1:
                printf("Digite o nome do aluno: ");
                scanf(" %[^\n]", nome);

                inserirInicio(&Alunos, nome);

                printf("Adicionado com Sucesso!\n");
                break;

            case 2:

                ExibirAluno(&Alunos);
                break;


            case 3:

                printf("Digite a Matrícula do aluno a ser removido: \n");
                scanf("%d", &aluno_rm);

                removerAluno(&Alunos, aluno_rm);
                salvarArquivo(&Alunos);

                printf("Aluno removido com Sucesso!");
                break;


            case 4:
                printf("Digite a Matrícula do a ser modificado: \n");
                scanf("%d", &matricula);
               
                modificarAluno(&Alunos, matricula);
                salvarArquivo(&Alunos);

                printf("Aluno modificado com Sucesso!");
                break;


            case 5:
                printf("Salvando e saindo...\n");

                salvarArquivo(&Alunos);
                printf("Sessão encerrada com sucesso. Até logo!\n");
                return 0;

                break;


            case 6:
                system("xdg-open https://youtu.be/IxX_QHay02M?si=z_xpl588cMqxKqxK");
                break;


            case 7:
                system("xdg-open https://youtu.be/watch?v=J---aiyznGQ&si=XDB1URxua_G8V89t");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;

        }



    };



    return 0;
}
