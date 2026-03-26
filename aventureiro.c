#include <stdio.h>

#define TAMANHO 10
#define NAVIO 3
#define AGUA 0

// Função para exibir o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%d |", i); // Índice da linha
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // 1. Criar e inicializar o tabuleiro 10x10 com 0 (água)
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    // 2. Posicionamento dos Navios (Tamanho fixo 3)
    
    // Navio 1: Horizontal (Linha 1, Colunas 1, 2, 3)
    for (int j = 1; j <= 3; j++) tabuleiro[1][j] = NAVIO;

    // Navio 2: Vertical (Linhas 5, 6, 7, Coluna 8)
    for (int i = 5; i <= 7; i++) tabuleiro[i][8] = NAVIO;

    // Navio 3: Diagonal Principal (Descendente: linha++ e coluna++)
    // Coordenadas: (2,6), (3,7), (4,8)
    int linhaD1 = 2, colD1 = 6;
    for (int k = 0; k < 3; k++) {
        tabuleiro[linhaD1 + k][colD1 + k] = NAVIO;
    }

    // Navio 4: Diagonal Secundária (Ascendente: linha++ e coluna--)
    // Coordenadas: (7,2), (8,1), (9,0)
    int linhaD2 = 7, colD2 = 2;
    for (int k = 0; k < 3; k++) {
        tabuleiro[linhaD2 + k][colD2 - k] = NAVIO;
    }

    // 3. Exibir o resultado final
    printf("=== TABULEIRO BATALHA NAVAL (INTERMEDIÁRIO) ===\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
