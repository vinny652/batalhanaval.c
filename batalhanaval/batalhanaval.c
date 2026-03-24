#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABULEIRO 10
#define NUM_NAVIOS 5

typedef struct {
    char grade[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
} Tabuleiro;

typedef struct {
    char nome[20];
    int tamanho;
} Navio;

Navio navios[NUM_NAVIOS] = {
    {"Porta-aviões", 5},
    {"Encouraçado", 4},
    {"Cruzador", 3},
    {"Submarino", 3},
    {"Destróier", 2}
};

void inicializar_tabuleiro(Tabuleiro *t) {
    for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for(int j = 0; j < TAMANHO_TABULEIRO; j++) {
            t->grade[i][j] = '~';
        }
    }
}

void imprimir_tabuleiro(Tabuleiro *t, int esconder_navios) {
    printf("  ");
    for(int i = 0; i < TAMANHO_TABULEIRO; i++) printf("%d ", i);
    printf("\n");
    for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
        for(int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if(esconder_navios && t->grade[i][j] == 'N') printf("~ ");
            else printf("%c ", t->grade[i][j]);
        }
        printf("\n");
    }
}

int posicionar_navio(Tabuleiro *t, Navio n, int linha, int coluna, int direcao) {
    // direcao 0 horizontal, 1 vertical
    if(direcao == 0) {
        if(coluna + n.tamanho > TAMANHO_TABULEIRO) return 0;
        for(int i = 0; i < n.tamanho; i++) {
            if(t->grade[linha][coluna + i] != '~') return 0;
        }
        for(int i = 0; i < n.tamanho; i++) {
            t->grade[linha][coluna + i] = 'N';
        }
    } else {
        if(linha + n.tamanho > TAMANHO_TABULEIRO) return 0;
        for(int i = 0; i < n.tamanho; i++) {
            if(t->grade[linha + i][coluna] != '~') return 0;
        }
        for(int i = 0; i < n.tamanho; i++) {
            t->grade[linha + i][coluna] = 'N';
        }
    }
    return 1;
}

int atirar(Tabuleiro *t, int linha, int coluna) {
    if(t->grade[linha][coluna] == 'N') {
        t->grade[linha][coluna] = 'X';
        return 1; // acerto
    } else if(t->grade[linha][coluna] == '~') {
        t->grade[linha][coluna] = 'O';
        return 0; // erro
    }
    return -1; // já atirou
}

int verificar_vitoria(Tabuleiro *t) {
    for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for(int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if(t->grade[i][j] == 'N') return 0;
        }
    }
    return 1;
}

int main() {
    Tabuleiro j1, j2;
    inicializar_tabuleiro(&j1);
    inicializar_tabuleiro(&j2);

    // Posicionar navios para j1
    printf("Jogador 1, posicione seus navios.\n");
    for(int i = 0; i < NUM_NAVIOS; i++) {
        imprimir_tabuleiro(&j1, 0);
        printf("Posicione %s (tamanho %d)\n", navios[i].nome, navios[i].tamanho);
        int linha, coluna, direcao;
        printf("Digite linha, coluna, direcao (0 hor, 1 ver): ");
        scanf("%d %d %d", &linha, &coluna, &direcao);
        while(!posicionar_navio(&j1, navios[i], linha, coluna, direcao)) {
            printf("Posicionamento inválido. Tente novamente: ");
            scanf("%d %d %d", &linha, &coluna, &direcao);
        }
    }

    // Mesmo para j2
    printf("Jogador 2, posicione seus navios.\n");
    for(int i = 0; i < NUM_NAVIOS; i++) {
        imprimir_tabuleiro(&j2, 0);
        printf("Posicione %s (tamanho %d)\n", navios[i].nome, navios[i].tamanho);
        int linha, coluna, direcao;
        printf("Digite linha, coluna, direcao (0 hor, 1 ver): ");
        scanf("%d %d %d", &linha, &coluna, &direcao);
        while(!posicionar_navio(&j2, navios[i], linha, coluna, direcao)) {
            printf("Posicionamento inválido. Tente novamente: ");
            scanf("%d %d %d", &linha, &coluna, &direcao);
        }
    }

    // Loop do jogo
    int turno = 0;
    while(1) {
        Tabuleiro *atacante, *defensor;
        if(turno % 2 == 0) {
            atacante = &j1;
            defensor = &j2;
            printf("Vez do Jogador 1\n");
        } else {
            atacante = &j2;
            defensor = &j1;
            printf("Vez do Jogador 2\n");
        }
        imprimir_tabuleiro(defensor, 1);
        int linha, coluna;
        printf("Digite linha coluna para atirar: ");
        scanf("%d %d", &linha, &coluna);
        int resultado = atirar(defensor, linha, coluna);
        if(resultado == 1) {
            printf("Acerto!\n");
        } else if(resultado == 0) {
            printf("Erro!\n");
        } else {
            printf("Já atirou aí. Tente novamente.\n");
            continue;
        }
        if(verificar_vitoria(defensor)) {
            printf("Jogador %d vence!\n", (turno % 2) + 1);
            break;
        }
        turno++;
    }

    return 0;
}