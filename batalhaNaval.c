#include <stdio.h>

#define TAMANHO_TABULEIRO 10 // Tamanho do tabuleiro 10x10
#define TAMANHO_NAVIO 3      // Tamanho dos navios
#define TAMANHO_HABILIDADE 5 // Tamanho das matrizes de habilidade

// Função para inicializar o tabuleiro
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // Inicializa com água
        }
    }
}

// Função para posicionar navios no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int novaLinha = linha;
        int novaColuna = coluna;

        if (orientacao == 0) { // Horizontal
            novaColuna += i;
        } else if (orientacao == 1) { // Vertical
            novaLinha += i;
        }
        tabuleiro[novaLinha][novaColuna] = 3; // 3 representa a parte do navio
    }
}

// Função para criar a matriz de habilidade em forma de cone
void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= (TAMANHO_HABILIDADE / 2) - i && j <= (TAMANHO_HABILIDADE / 2) + i) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de cruz
void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para criar a matriz de habilidade em forma de octaedro
void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i + j >= TAMANHO_HABILIDADE / 2 && i + (TAMANHO_HABILIDADE - 1 - j) >= TAMANHO_HABILIDADE / 2 &&
                (TAMANHO_HABILIDADE - 1 - i) + j >= TAMANHO_HABILIDADE / 2 && (TAMANHO_HABILIDADE - 1 - i) + (TAMANHO_HABILIDADE - 1 - j) >= TAMANHO_HABILIDADE / 2) {
                habilidade[i][j] = 1; // Área afetada
            } else {
                habilidade[i][j] = 0; // Área não afetada
            }
        }
    }
}

// Função para sobrepor a matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int origemLinha, int origemColuna) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int novaLinha = origemLinha + i;
                int novaColuna = origemColuna + j;
                // Verifica se a nova posição está dentro dos limites do tabuleiro
                if (novaLinha >= 0 && novaLinha < TAMANHO_TABULEIRO && novaColuna >= 0 && novaColuna < TAMANHO_TABULEIRO) {
                    tabuleiro[novaLinha][novaColuna] = 5; // 5 representa a área afetada pela habilidade
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro de Batalha Naval:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]); // Imprime cada elemento do tabuleiro
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro
    }
}

int main() {
    // Declaração e inicialização do tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posicionamento dos navios
    posicionarNavio(tabuleiro, 2, 1, 0); // Navio 1: Horizontal
    posicionarNavio(tabuleiro, 0, 5, 1); // Navio 2: Vertical

    // Matrizes de habilidade
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Criar as matrizes de habilidade
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);

    // Aplicar habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, habilidadeCone, 0, 2); // Cone na posição (0, 2)
    aplicarHabilidade(tabuleiro, habilidadeCruz, 4, 4); // Cruz na posição (4, 4)
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 6, 3); // Octaedro na posição (6, 3)

    // Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}