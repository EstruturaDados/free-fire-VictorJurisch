#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define MAX_NOME 50
#define MAX_TIPO 30

typedef enum {
    NOME,
    TIPO,
    PRIORIDADE
} OrdenacaoCriterio;

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade;
} Item;

int comparacoes = 0;

void adicionar_item(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("❌ Mochila cheia!\n");
        return;
    }
    
    printf("\n Adicionar Item\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", mochila[*total].nome);
    
    printf("Tipo do item: ");
    scanf(" %[^\n]", mochila[*total].tipo);
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    
    printf("Prioridade (1-5): ");
    scanf("%d", &mochila[*total].prioridade);
    
    if (mochila[*total].prioridade < 1 || mochila[*total].prioridade > 5) {
        printf("❌ Prioridade inválida!\n");
        return;
    }
    
    (*total)++;
    printf("Item adicionado!\n");
}

void remover_item(Item mochila[], int *total) {
    char nome_busca[MAX_NOME];
    printf("\nRemover Item\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", nome_busca);
    
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome_busca) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("Item removido\n");
            return;
        }
    }
    printf("❌ Item não encontrado!\n");
}

void listar_itens(Item mochila[], int total) {
    if (total == 0) {
        printf("\nMochila vazia\n");
        return;
    }
    
    printf("\n📋 Inventário:\n");
    printf("╔════════════════════╦════════════════════╦════════════╦════════════╗\n");
    printf("║ Nome               ║ Tipo               ║ Quantidade ║ Prioridade ║\n");
    printf("╠════════════════════╬════════════════════╬════════════╬════════════╣\n");
    
    for (int i = 0; i < total; i++) {
        printf("║ %-18s ║ %-18s ║ %10d ║ %10d ║\n", 
               mochila[i].nome, mochila[i].tipo, 
               mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("╚════════════════════╩════════════════════╩════════════╩════════════╝\n");
}

void ordenar_insercao(Item mochila[], int total, OrdenacaoCriterio criterio) {
    comparacoes = 0;
    
    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            int resultado;
            
            if (criterio == NOME) {
                resultado = strcmp(mochila[j].nome, chave.nome);
            } else if (criterio == TIPO) {
                resultado = strcmp(mochila[j].tipo, chave.tipo);
            } else {
                resultado = mochila[j].prioridade - chave.prioridade;
            }
            
            if (resultado > 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
}

void menu_ordenacao(Item mochila[], int total) {
    printf("\n📊 Escolha o critério de ordenação:\n");
    printf("1- Por Nome\n");
    printf("2- Por Tipo\n");
    printf("3- Por Prioridade\n");
    printf("Escolha: ");
    
    int opcao;
    scanf("%d", &opcao);
    
    OrdenacaoCriterio criterio;
    const char *nome_criterio;
    
    switch (opcao) {
        case 1:
            criterio = NOME;
            nome_criterio = "Nome";
            break;
        case 2:
            criterio = TIPO;
            nome_criterio = "Tipo";
            break;
        case 3:
            criterio = PRIORIDADE;
            nome_criterio = "Prioridade";
            break;
        default:
            printf("❌ Opção inválida!\n");
            return;
    }
    
    ordenar_insercao(mochila, total, criterio);
    printf("Mochila ordenada por %s!\n", nome_criterio);
    printf("Comparacoes realizadas: %d\n", comparacoes);
}

int busca_binaria(Item mochila[], int total, char *nome_busca) {
    int esquerda = 0, direita = total - 1;
    
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int resultado = strcmp(mochila[meio].nome, nome_busca);
        
        if (resultado == 0) {
            return meio;
        } else if (resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}

void buscar_item_binaria(Item mochila[], int total) {
    char nome_busca[MAX_NOME];
    
    printf("\nBusca Binária por Nome\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", nome_busca);
    
    int indice = busca_binaria(mochila, total, nome_busca);
    
    if (indice != -1) {
        printf("\nItem encontrado (posição %d)!\n", indice);
        printf("╔════════════════════╦════════════════════╦════════════╦════════════╗\n");
        printf("║ Nome               ║ Tipo               ║ Quantidade ║ Prioridade ║\n");
        printf("╠════════════════════╬════════════════════╬════════════╬════════════╣\n");
        printf("║ %-18s ║ %-18s ║ %10d ║ %10d ║\n", 
               mochila[indice].nome, mochila[indice].tipo, 
               mochila[indice].quantidade, mochila[indice].prioridade);
        printf("╚════════════════════╩════════════════════╩════════════╩════════════╝\n");
    } else {
        printf("❌ Item não encontrado!\n");
    }
}

void menu_mestre() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;
    
    do {
        printf("\nFree fire\n");
        printf("1- Adicionar item\n");
        printf("2- Remover item\n");
        printf("3- Listar itens\n");
        printf("4- Ordenar mochila\n");
        printf("5- Buscar item (busca binária)\n");
        printf("6- Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                adicionar_item(mochila, &total);
                break;
            case 2:
                remover_item(mochila, &total);
                break;
            case 3:
                listar_itens(mochila, total);
                break;
            case 4:
                if (total > 0) {
                    menu_ordenacao(mochila, total);
                } else {
                    printf("Mochila vazia\n");
                }
                break;
            case 5:
                if (total > 0) {
                    buscar_item_binaria(mochila, total);
                } else {
                    printf("Mochila vazia\n");
                }
                break;
            case 6:
                printf("Saindo\n");
                break;
            default:
                printf("Opção invalida\n");
        }
    } while (opcao != 6);
}

int main() {
    menu_mestre();
    return 0;
}
