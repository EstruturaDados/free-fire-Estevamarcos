#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_MAXIMA 10

/* ============================================================================
 REQUISITO: Criacao da struct Item
 ============================================================================
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Prototipos das funcoes (Modularizacao e Manutenibilidade)
void inserirItem(Item mochila[], int* total);
void removerItem(Item mochila[], int* total);
void listarItens(Item mochila[], int total);
void limparBuffer();

/* ============================================================================
 FUNCAO PRINCIPAL
 ============================================================================
 */
int main() {
    Item mochila[CAPACIDADE_MAXIMA]; // Vetor estatico sequencial para ate 10 itens
    int totalItens = 0;              // Controlador do tamanho atual da lista
    int opcao = -1;

    while (1) {
        // Cabeçalho exatamente igual aos Prints do material
        printf("==================================================\n");
        printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("==================================================\n");
        printf("Itens na Mochila: %d/%d\n\n", totalItens, CAPACIDADE_MAXIMA);

        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("0. Sair\n");
        printf("--------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao == 0) {
            break;
        }

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("Pressione Enter para continuar...\n");
                getchar();
                break;
        }
        printf("\n"); // Espacamento visual entre turnos do menu
    }

    printf("\nEncerrando o inventario. Sobreviva a ilha!\n");
    return 0;
}

/* ============================================================================
 FUNCAO: Inserir Item (Loot) - Conforme Requisitos Visuais
 ============================================================================
 */
void inserirItem(Item mochila[], int* total) {
    // Validacao de limite maximo da lista sequencial
    if (*total >= CAPACIDADE_MAXIMA) {
        printf("\nA mochila esta cheia! Nao e possivel carregar mais loot.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    
    printf("Nome do item: ");
    scanf("%29s", mochila[*total].nome);
    limparBuffer();

    printf("Tipo do item (arma, municao, cura, etc.): ");
    scanf("%19s", mochila[*total].tipo);
    limparBuffer();

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    limparBuffer();

    // Mensagem de confirmacao em tela
    printf("\nItem '%s' adicionado com sucesso!\n", mochila[*total].nome);
    
    // Incrementa o contador de itens totais por referencia
    (*total)++;

    // Exibe a listagem atualizada imediatamente apos a operacao
    listarItens(mochila, *total);
    
    printf("\nPressione Enter para continuar...");
    getchar();
}

/* ============================================================================
 FUNCAO: Remover Item (Com Shifting/Deslocamento de memória)
 ============================================================================
 */
void removerItem(Item mochila[], int* total) {
    if (*total == 0) {
        printf("\nA mochila ja esta vazia!\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    char nomeBusca[30];
    int encontradoIdx = -1;
    int i;

    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    // Busca interna para encontrar a posicao do item para remocao
    for (i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontradoIdx = i;
            break;
        }
    }

    // Se o item foi localizado, reorganiza o vetor
    if (encontradoIdx != -1) {
        // Desloca os elementos subsequentes para nao deixar buracos na lista sequencial
        for (i = encontradoIdx; i < (*total) - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        
        // Decrementa o total de itens cadastrados
        (*total)--;
        
        printf("\nItem '%s' removido com sucesso!\n", nomeBusca);
        
        // Exibe a listagem atualizada imediatamente apos a operacao
        listarItens(mochila, *total);
    } else {
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeBusca);
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

/* ============================================================================
 FUNCAO: Listar Itens - Formato de Tabela Estrito
 ============================================================================
 */
void listarItens(Item mochila[], int total) {
    int i;
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", total, CAPACIDADE_MAXIMA);
    printf("--------------------------------------------------\n");
    printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("--------------------------------------------------\n");
    
    if (total == 0) {
        printf("              [ Mochila Vazia ]\n");
    } else {
        for (i = 0; i < total; i++) {
            printf("%-20s | %-15s | %d\n", 
                   mochila[i].nome, 
                   mochila[i].tipo, 
                   mochila[i].quantidade);
        }
    }
    printf("--------------------------------------------------\n");
}

/* ============================================================================
 FUNCAO AUXILIAR: Limpeza de Buffer do Teclado
 ============================================================================
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

