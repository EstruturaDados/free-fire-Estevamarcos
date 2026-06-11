#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CAPACIDADE_MAXIMA 10

/* ============================================================================
 STRUCT DO COMPONENTE
 ============================================================================
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade; 
    int prioridade;
} Componente;

// Controle de status de ordenação
int statusAtual = 0; // 0 = NAO ORDENADO, 1 = ORDENADO_NOME

// Contador global para o relatório de desempenho
int comparacoesRealizadas = 0;

// Protótipos das Funções
void bubbleSortNome(Componente vetor[], int tamanho);
void insertionSortTipo(Componente vetor[], int tamanho);
void selectionSortPrioridade(Componente vetor[], int tamanho);
int buscaBinariaPorNome(Componente vetor[], int tamanho, char chave[]);
void mostrarComponentes(Componente vetor[], int tamanho);
void adicionarComponente(Componente mochila[], int* total);
void descartarComponente(Componente mochila[], int* total);
void organizarMochila(Componente mochila[], int total);
void executarBuscaBinaria(Componente mochila[], int total);
void limparBuffer();

/* ============================================================================
 FUNÇÃO PRINCIPAL
 ============================================================================
 */
int main() {
    Componente mochila[CAPACIDADE_MAXIMA];
    int totalComponentes = 0;
    int opcao = -1;

    while (1) {
        // Cabeçalho idêntico aos Prints 1, 4 e 5
        printf("==================================================\n");
        printf("   PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("==================================================\n");
        printf("Itens na Mochila: %d/%d\n", totalComponentes, CAPACIDADE_MAXIMA);
        
        if (statusAtual == 1) {
            printf("Status da Ordenacao por Nome: ORDENADO\n\n");
        } else {
            printf("Status da Ordenacao por Nome: NAO ORDENADO\n\n");
        }

        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("--------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao == 0) {
            break;
        }

        switch (opcao) {
            case 1:
                adicionarComponente(mochila, &totalComponentes);
                break;
            case 2:
                descartarComponente(mochila, &totalComponentes);
                break;
            case 3:
                mostrarComponentes(mochila, totalComponentes);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 4:
                organizarMochila(mochila, totalComponentes);
                break;
            case 5:
                executarBuscaBinaria(mochila, totalComponentes);
                break;
            default:
                printf("\nOpcao invalida!\n");
                printf("Pressione Enter para continuar...\n");
                getchar();
                break;
        }
        printf("\n");
    }

    return 0;
}

/* ============================================================================
 ALGORITMOS DE ORDENAÇÃO
 ============================================================================
 */

void bubbleSortNome(Componente vetor[], int tamanho) {
    int i, j;
    Componente temp;
    comparacoesRealizadas = 0;

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            comparacoesRealizadas++;
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    statusAtual = 1; 
}

void insertionSortTipo(Componente vetor[], int tamanho) {
    int i, j;
    Componente chave;
    comparacoesRealizadas = 0;

    for (i = 1; i < tamanho; i++) {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0) {
            comparacoesRealizadas++;
            if (strcmp(vetor[j].tipo, chave.tipo) > 0) {
                vetor[j + 1] = vetor[j];
                j--;
            } else {
                break;
            }
        }
        vetor[j + 1] = chave;
    }
    statusAtual = 0; 
}

void selectionSortPrioridade(Componente vetor[], int tamanho) {
    int i, j, idxMaior;
    Componente temp;
    comparacoesRealizadas = 0;

    for (i = 0; i < tamanho - 1; i++) {
        idxMaior = i;
        for (j = i + 1; j < tamanho; j++) {
            comparacoesRealizadas++;
            if (vetor[j].prioridade > vetor[idxMaior].prioridade) {
                idxMaior = j;
            }
        }
        if (idxMaior != i) {
            temp = vetor[i];
            vetor[i] = vetor[idxMaior];
            vetor[idxMaior] = temp;
        }
    }
    statusAtual = 0; 
}

/* ============================================================================
 ALGORITMO DE BUSCA BINÁRIA
 ============================================================================
 */
int buscaBinariaPorNome(Componente vetor[], int tamanho, char chave[]) {
    int esquerda = 0;
    int direita = tamanho - 1;
    int meio;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;
        int resComp = strcmp(vetor[meio].nome, chave);

        if (resComp == 0) {
            return meio; 
        }
        if (resComp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1; 
}

/* ============================================================================
 GESTÃO DE EXECUÇÃO DA BUSCA BINÁRIA (Ajustado conforme Print 5 e 9)
 ============================================================================
 */
void executarBuscaBinaria(Componente mochila[], int total) {
    if (statusAtual != 1) {
        printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
        printf("Use a Opcao 4 para organizar a mochila primeiro.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    char nomeBusca[30];
    // Ajustado conforme o Print 9
    printf("\n--- Busca Binaria por Componente-Chave ---\n");
    printf("Nome do componente a buscar: ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    int resultado = buscaBinariaPorNome(mochila, total, nomeBusca);

    if (resultado != -1) {
        printf("\n SUCESSO Componente-Chave localizado!\n");
        printf("Nome: %s,  Tipo: %s, Quantidade: %d,  Prioridade: %d\n", 
               mochila[resultado].nome, mochila[resultado].tipo, mochila[resultado].quantidade, mochila[resultado].prioridade);
    } else {
        printf("\nComponente '%s' nao foi localizado no inventario.\n", nomeBusca);
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}

/* ============================================================================
 GESTÃO DE EXECUÇÃO DA ORDENAÇÃO (Ajustado conforme Print 6 e 8)
 ============================================================================
 */
void organizarMochila(Componente mochila[], int total) {
    if (total == 0) {
        printf("\nInventario vazio. Adicione componentes primeiro!\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    int criterio = -1;
    printf("\n--- Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabética)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade de Montagem\n");
    printf("0. Cancelar\n");
    printf("Escolha o criterio: ");
    scanf("%d", &criterio);
    limparBuffer();

    if (criterio == 0) return;

    clock_t tInicio = clock();
    char labelCriterio[20];

    if (criterio == 1) {
        bubbleSortNome(mochila, total);
        strcpy(labelCriterio, "NOME");
    } else if (criterio == 2) {
        insertionSortTipo(mochila, total);
        strcpy(labelCriterio, "TIPO");
    } else if (criterio == 3) {
        selectionSortPrioridade(mochila, total);
        strcpy(labelCriterio, "PRIORIDADE");
    } else {
        printf("\nCriterio invalido!\n");
        return;
    }

    clock_t tFim = clock();
    double tempoGasto = ((double)(tFim - tInicio)) / CLOCKS_PER_SEC * 1000.0;

    // Mensagem corrigida milimetricamente conforme a saída do Print 6 e 8
    printf("\nMochila organizada por %s.\n", labelCriterio);
    printf("Analyse de Desempenho: Foram necessarias %d comparacoes.\n", comparacoesRealizadas);

    mostrarComponentes(mochila, total);
    printf("\nPressione Enter para continuar...");
    getchar();
}

/* ============================================================================
 FUNÇÕES AUXILIARES DE ENTRADA E SAÍDA (Ajustado conforme Print 2 e 3)
 ============================================================================
 */
void adicionarComponente(Componente mochila[], int* total) {
    if (*total >= CAPACIDADE_MAXIMA) {
        printf("\nMochila cheia!\n");
        return;
    }
    
    printf("\n--- Coletando Novo Componente ---\n");
    printf("Nome: ");
    scanf("%29s", mochila[*total].nome);
    limparBuffer();

    printf("Tipo (Estrutural, Eletronico, Energia): ");
    scanf("%19s", mochila[*total].tipo);
    limparBuffer();

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    limparBuffer();

    printf("Prioridade de Montagem (1-5): ");
    scanf("%d", &mochila[*total].prioridade);
    limparBuffer();

    // Texto exato extraído do seu Print 3
    printf("\nComponente '%s' adicionado!\n", mochila[*total].nome);

    (*total)++;
    statusAtual = 0; 

    // Lista automaticamente após a inserção conforme as regras do trabalho
    mostrarComponentes(mochila, *total);
    printf("\nPressione Enter para continuar...\n");
    getchar();
}

void descartarComponente(Componente mochila[], int* total) {
    if (*total == 0) return;
    char nomeBusca[30];
    printf("\nDigite o nome do componente a descartar: ");
    scanf("%29s", nomeBusca);
    limparBuffer();

    int idx = -1, i;
    for (i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            idx = i;
            break;
        }
    }
    if (idx != -1) {
        for (i = idx; i < (*total) - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*total)--;
        statusAtual = 0;
        printf("\nComponente descartado!\n");
        mostrarComponentes(mochila, *total);
    } else {
        printf("\nComponente nao encontrado.\n");
    }
    printf("\nPressione Enter para continuar...\n");
    getchar();
}

void mostrarComponentes(Componente vetor[], int tamanho) {
    int i;
    // Título e formatação idênticos aos Prints 3, 6 e 8
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", tamanho, CAPACIDADE_MAXIMA);
    printf("----------------------------------------------------------------------\n");
    printf("%-20s | %-15s | %-12s | %s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("----------------------------------------------------------------------\n");
    for (i = 0; i < tamanho; i++) {
        printf("%-20s | %-15s | %-12d | %d\n", 
               vetor[i].nome, vetor[i].tipo, vetor[i].quantidade, vetor[i].prioridade);
    }
    printf("----------------------------------------------------------------------\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}