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
void buscarItem(Item mochila[], int total);
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
        // Cabeçalho exatamente igual aos Prints 1, 3 e 4
        printf("==================================================\n");
        printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("==================================================\n");
        printf("Itens na Mochila: %d/%d\n\n", totalItens, CAPACIDADE_MAXIMA);

        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n"); // Adicionado ao menu conforme requisito de busca
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
                // Apenas lista sem fazer alteracoes
                listarItens(mochila, totalItens);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 4:
                buscarItem(mochila, totalItens);
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
 FUNCAO: Inserir Item (Loot) - Conforme Print 2
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

    // Mensagem de confirmacao exata do Print 2
    printf("\nItem '%s' adicionado com sucesso!\n", mochila[*total].nome);
    
    // Incrementa o contador de itens totais por referencia
    (*total)++;

    // REQUISITO: Exibe a listagem atualizada imediatamente apos a operacao
    listarItens(mochila, *total);
    
    printf("\nPressione Enter para continuar...");
    getchar();
}

/* ============================================================================
 FUNCAO: Remover Item - Conforme Prints 5 e 6
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

    // Busca sequencial para encontrar a posicao do item
    for (i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontradoIdx = i;
            break;
        }
    }

    // Se o item foi localizado, fazemos a remocao reorganizando o vetor
    if (encontradoIdx != -1) {
        // Desloca os elementos subsequentes uma posicao para tras para nao deixar buracos na lista
        for (i = encontradoIdx; i < (*total) - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        
        // Decrementa o total de itens cadastrados
        (*total)--;
        
        // Mensagem de confirmacao exata do Print 5
        printf("\nItem '%s' removido com sucesso!\n", nomeBusca);
        
        // REQUISITO: Exibe a listagem atualizada imediatamente apos a operacao
        listarItens(mochila, *total);
    } else {
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeBusca);
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

/* ============================================================================
 FUNCAO: Listar Itens - Formato de Tabela exato dos Prints 2 e 5
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
 REQUISITO: Busca Sequencial por Nome
 ============================================================================
 */
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila esta vazia. Nao ha o que buscar!\n");
        return;
    }

    char nomeBusca[30];
    int i;
    int achou = 0;

    printf("\n--- Buscar Item (Busca Sequencial) ---\n");
    printf("Digite o nome do item que deseja procurar: ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    // Algoritmo clássico de busca sequencial percorrendo elemento por elemento
    for (i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem localizado com sucesso!\n");
            printf("-> Nome: %s\n", mochila[i].nome);
            printf("-> Tipo: %s\n", mochila[i].tipo);
            printf("-> Quantidade: %d\n", mochila[i].quantidade);
            achou = 1;
            break; // Interrompe o laço pois ja encontrou o registro unico
        }
    }

    if (!achou) {
        printf("\nO item '%s' nao foi encontrado no seu inventario.\n", nomeBusca);
    }
}

/* ============================================================================
 FUNCAO AUXILIAR: Limpeza de Buffer do Teclado
 ============================================================================
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
