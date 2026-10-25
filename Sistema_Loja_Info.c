#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int cod_prod;
  char nome[75];
  char categoria[25];
  int qtd;
  float preco;
} Produto;

int main() {
  Produto p = {0};
  FILE *arquivoesp;
  int c;
  int opcao;

  do {
    printf("\n=================================================\n");
    printf("\n SISTEMA DE GERENCIA DE PRODUTOS\n");
    printf("\n=================================================\n");
    printf("1 - Cadastrar Produtos\n");
    printf("2 - Listar Produtos\n");
    printf("3 - Calcular Valor de Estoque\n");
    printf("4 - Buscar Produto\n");
    printf("0 - Encerrar Programa\n");
    printf("\nEscolha: ");
    scanf("%d", &opcao);

    switch(opcao) {

      case 1: {
        int encontrado = 0;
        Produto p_existente;

        printf("\nDigite o codigo do produto: ");
        scanf("%d", &p.cod_prod);

        while ((c = getchar()) != '\n' && c != EOF);

        arquivoesp = fopen("produtos.txt", "r");

        if (arquivoesp != NULL) {
          while (fscanf(arquivoesp, "%d;%74[^;];%f;%d;%24[^\n]\n",
                        &p_existente.cod_prod, p_existente.nome, &p_existente.preco, &p_existente.qtd, p_existente.categoria) == 5) {

            if (p_existente.cod_prod == p.cod_prod) {
              p = p_existente;
              encontrado = 1;
              break;
            }
          }
          fclose(arquivoesp);
        }

        if (!encontrado) {
          printf("Nome: ");
          fgets(p.nome, sizeof(p.nome), stdin);
          p.nome[strcspn(p.nome, "\n")] = '\0';
          printf("Categoria: ");
          fgets(p.categoria, sizeof(p.categoria), stdin);
          p.categoria[strcspn(p.categoria, "\n")] = '\0';

          printf("Quantidade adquirida do produto: ");
          scanf("%d", &p.qtd);

          printf("Digite o preco do produto: ");
          scanf("%f", &p.preco);

          // Anexa um produto inteiramente novo
          arquivoesp = fopen("produtos.txt", "a");
          if (arquivoesp != NULL) {
            fprintf(arquivoesp, "%d;%s;%.2f;%d;%s\n", p.cod_prod, p.nome, p.preco, p.qtd, p.categoria);
            fclose(arquivoesp);
            printf("\nProduto cadastrado com sucesso!\n");
          }
        } 
        else {
          int qtd_add, op, op2;

          printf("\nJa tens %d unidades do produto '%s'. Desejas adicionar mais?\n", p.qtd, p.nome);
          printf("1 - Sim.\n");
          printf("2 - Nao.\n");
          printf("Escolha: ");
          scanf("%d", &op);

          if (op == 1) {
            printf("Quantidade a adicionar: ");
            scanf("%d", &qtd_add);
            p.qtd += qtd_add;
            printf("\nNovo total no estoque: %d\n", p.qtd);
          } else if (op == 2) {
            printf("Desejas atualizar o preco?\n");
            printf("1 - Sim.\n");
            printf("2 - Nao.\n");
            printf("Escolha: ");
            scanf("%d", &op2);

            if (op2 == 1) {
              printf("Digite o preco atualizado do produto: ");
              scanf("%f", &p.preco);
            } else {
              printf("Retornando ao menu principal!\n");
              break;
            }
          }

          // Atualiza o arquivo substituindo a linha antiga via temp.txt
          FILE *original = fopen("produtos.txt", "r");
          FILE *temp = fopen("temp.txt", "w");

          if (original != NULL && temp != NULL) {
            while (fscanf(original, "%d;%74[^;];%f;%d;%24[^\n]\n",
                          &p_existente.cod_prod, p_existente.nome, &p_existente.preco, &p_existente.qtd, p_existente.categoria) == 5) {
              if (p_existente.cod_prod == p.cod_prod) {
                // Escreve os dados atualizados
                fprintf(temp, "%d;%s;%.2f;%d;%s\n", p.cod_prod, p.nome, p.preco, p.qtd, p.categoria);
              } else {
                // Mantem os outros produtos inalterados
                fprintf(temp, "%d;%s;%.2f;%d;%s\n", p_existente.cod_prod, p_existente.nome, p_existente.preco, p_existente.qtd, p_existente.categoria);
              }
            }
            fclose(original);
            fclose(temp);

            remove("produtos.txt");
            rename("temp.txt", "produtos.txt");
            printf("\nProduto atualizado com sucesso!\n");
          }
        }

        break;
      }
      
      case 2: {
		
	  
        arquivoesp = fopen("produtos.txt", "r");
        if (arquivoesp == NULL) {
          printf("\nErro ao abrir o ficheiro ou ainda nao existem produtos cadastrados!\n");
          break;
        }

        printf("\n====================== PRODUTOS CADASTRADOS ======================\n");

        while (fscanf(arquivoesp, "%d;%74[^;];%f;%d;%24[^\n]\n", &p.cod_prod, p.nome, &p.preco, &p.qtd, p.categoria) == 5) {
          printf("\nCodigo: %d\n", p.cod_prod);
          printf("Nome: %s\n", p.nome);
          printf("Preco: R$%.2f\n", p.preco);
          printf("Quantidade: %d\n", p.qtd);
          printf("Categoria: %s\n", p.categoria);
        }

        fclose(arquivoesp);
        break;
}
      case 3: {
		
        arquivoesp = fopen("produtos.txt", "r");

        if (arquivoesp == NULL) {
          printf("\nErro ao abrir o ficheiro ou ainda nao existem produtos cadastrados!\n");
          break;
        }

        float total_estoque = 0.00f;

        while (fscanf(arquivoesp, "%d;%74[^;];%f;%d;%24[^\n]\n", &p.cod_prod, p.nome, &p.preco, &p.qtd, p.categoria) == 5) {
          total_estoque += p.qtd * p.preco;
        }

        printf("\n=============================================\n");
        printf("  VALOR TOTAL EM ESTOQUE: R$ %.2f\n", total_estoque);
        printf("===============================================\n");

        fclose(arquivoesp);
        break;
}
      case 4: {
        int busca;
        char busca_nome[75];
        int encontrado1 = 0;
        int opcao1;

        printf("Quer buscar por nome ou codigo?\n");
        printf("1 - Nome\n");
        printf("2 - Codigo\n");
        printf("Escolha: ");
        scanf("%d", &opcao1);

        while ((c = getchar()) != '\n' && c != EOF);

        arquivoesp = fopen("produtos.txt", "r");
        if (arquivoesp == NULL) {
          printf("\nErro ao abrir o ficheiro ou ainda nao existem produtos cadastrados!\n");
          break;
        }

        if (opcao1 == 1) {
          printf("\nDigite o nome do produto: ");
          fgets(busca_nome, sizeof(busca_nome), stdin);
          busca_nome[strcspn(busca_nome, "\n")] = '\0';

          while (fscanf(arquivoesp, "%d;%74[^;];%f;%d;%24[^\n]\n", &p.cod_prod, p.nome, &p.preco, &p.qtd, p.categoria) == 5) {
            if (strcmp(p.nome, busca_nome) == 0) {
              printf("\nProduto Encontrado!\n");
              printf("Codigo: %d\n", p.cod_prod);
              printf("Nome: %s\n", p.nome);
              printf("Categoria: %s\n", p.categoria);
              printf("Preco: R$%.2f\n", p.preco);
              printf("Quantidade: %d\n", p.qtd);
              encontrado1 = 1;
              break;
            }
          }
        } else if (opcao1 == 2) {
          printf("\nDigite o codigo do produto: ");
          scanf("%d", &busca);

          while (fscanf(arquivoesp, "%d;%74[^;];%f;%d;%24[^\n]\n", &p.cod_prod, p.nome, &p.preco, &p.qtd, p.categoria) == 5) {
            if (p.cod_prod == busca) {
              printf("\nProduto Encontrado!\n");
              printf("Codigo: %d\n", p.cod_prod);
              printf("Nome: %s\n", p.nome);
              printf("Categoria: %s\n", p.categoria);
              printf("Preco: R$%.2f\n", p.preco);
              printf("Quantidade: %d\n", p.qtd);
              encontrado1 = 1;
              break;
            }
          }
        }

        if (!encontrado1) {
          printf("\nProduto nao encontrado!\n");
        }

        fclose(arquivoesp);
        break;
      }

      case 0: {
        printf("\nEncerrando o sistema...\n");
        printf("Ate Logo!\n");
        break;
}
      
	default: {
		
        printf("\nOpcao invalida!\n");
}
  
}  
  } while(opcao != 0);

  return 0;
}
