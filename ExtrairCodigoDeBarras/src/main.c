#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ean8_leitor.h"

int main() {
    char nomeArquivo[100];
    char caminhoCompleto[200];

    exibirCabecalho();

    printf("Digite o nome do arquivo PBM (sem caminho): ");
    scanf("%s", nomeArquivo);

    // Adiciona caminho da pasta CodigoGerado
    // Se o usuário não digitou .pbm, adiciona
    if (strstr(nomeArquivo, ".pbm") == NULL) {
        snprintf(caminhoCompleto, sizeof(caminhoCompleto),
                 "../GerarCodigoDeBarras/CodigoGerado/%s.pbm", nomeArquivo);
    } else {
        snprintf(caminhoCompleto, sizeof(caminhoCompleto),
                 "../GerarCodigoDeBarras/CodigoGerado/%s", nomeArquivo);
    }

    // Verifica se o arquivo existe
    FILE *f = fopen(caminhoCompleto, "r");
    if (!f) {
        printf("Arquivo '%s' não encontrado em CodigoGerado.\n", nomeArquivo);
        return 1;
    }
    fclose(f);

    lerArquivoPBM(caminhoCompleto);
    extrairIdentificador();
    liberarMatriz();

    printf("Pressione Enter para continuar...");
    getchar(); getchar();

    return 0;
}
