#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ean8_leitor.h"

int **codigoMatriz;
int larguraCodigo, alturaCodigo;

void lerArquivoPBM(const char *arquivo) {
    char tipo[3], formato[4];

    FILE *file = fopen(arquivo, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    int tam = strlen(arquivo);
    strncpy(formato, &arquivo[tam - 3], 3);
    formato[3] = '\0';

    if (strcmp(formato, "pbm") != 0) {
        fprintf(stderr, "Erro: O arquivo não é do tipo PBM.\n");
        exit(1);
    } else {
        printf("Arquivo válido\n");
    }

    fscanf(file, "%s", tipo);
    fscanf(file, "%d %d", &larguraCodigo, &alturaCodigo);

    codigoMatriz = (int **)malloc(sizeof(int *) * alturaCodigo);
    for (int i = 0; i < alturaCodigo; i++) {
        codigoMatriz[i] = (int *)malloc(sizeof(int) * larguraCodigo);
    }

    for (int i = 0; i < alturaCodigo; i++) {
        for (int j = 0; j < larguraCodigo; j++) {
            fscanf(file, "%d", &codigoMatriz[i][j]);
        }
    }

    fclose(file);
}

void liberarMatriz() {
    if (codigoMatriz) {
        for (int i = 0; i < alturaCodigo; i++)
            free(codigoMatriz[i]);
        free(codigoMatriz);
    }
}

int bitsParaDecimal(int *bits, int tamanho) {
    int valor = 0;
    for (int i = 0; i < tamanho; i++) {
        valor = (valor << 1) | bits[i];
    }
    return valor;
}

// ****** FUNÇÃO CORRIGIDA ******
void extrairIdentificador() {
    int bordaSuperior = 0, bordaLateral = 0, encontrou = 0;

    for (int i = 0; i < alturaCodigo && !encontrou; i++) {
        for (int j = 0; j < larguraCodigo; j++) {
            if (codigoMatriz[i][j] == 1) {
                bordaSuperior = i;
                bordaLateral = j;
                encontrou = 1;
                break;
            }
        }
    }

    if (!encontrou) {
        printf("Código de barras inválido.\n");
        return;
    }

    int larguraModulo = 0;
    int col_atual = bordaLateral;
    while(col_atual < larguraCodigo && codigoMatriz[bordaSuperior][col_atual] == 1) {
        larguraModulo++;
        col_atual++;
    }

    if (larguraModulo == 0) {
        printf("Código de barras inválido (não foi possível determinar a largura do módulo).\n");
        return;
    }

    int codigoL[10] = {0b0001101, 0b0011001, 0b0010011, 0b0111101,
                        0b0100011, 0b0110001, 0b0101111, 0b0111011,
                        0b0110111, 0b0001011};

    int codigoR[10] = {0b1110010, 0b1100110, 0b1101100, 0b1000010,
                        0b1011100, 0b1001110, 0b1010000, 0b1000100,
                        0b1001000, 0b1110100};

    printf("Identificador do código de barras: ");

    // Posição inicial após a guarda inicial (3 módulos)
    int offset = bordaLateral + (3 * larguraModulo);

    // Dígitos da esquerda
    for (int digito = 0; digito < 4; digito++) {
        int bits[7];
        for (int b = 0; b < 7; b++) {
            int col = offset + (digito * 7 * larguraModulo) + (b * larguraModulo);
            bits[b] = codigoMatriz[bordaSuperior][col];
        }
        int valor = bitsParaDecimal(bits, 7);
        for (int n = 0; n < 10; n++) {
            if (valor == codigoL[n]) {
                printf("%d", n);
                break;
            }
        }
    }

    // Pular para a seção da direita (após os 4 dígitos da esquerda e a guarda central de 5 módulos)
    offset += (28 * larguraModulo) + (5 * larguraModulo);

    // Dígitos da direita
    for (int digito = 0; digito < 4; digito++) {
        int bits[7];
        for (int b = 0; b < 7; b++) {
            int col = offset + (digito * 7 * larguraModulo) + (b * larguraModulo);
            bits[b] = codigoMatriz[bordaSuperior][col];
        }
        int valor = bitsParaDecimal(bits, 7);
        for (int n = 0; n < 10; n++) {
            if (valor == codigoR[n]) {
                printf("%d", n);
                break;
            }
        }
    }

    printf("\n");
}