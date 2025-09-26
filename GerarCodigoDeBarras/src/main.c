#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ean8.h"
int main() {
    preferencias configuracoes; 

    int digitos[8];  
    char entradaIdentificador[9];  
    head();
    
    printf("\033[36mInsira o identificador abaixo:\033[0m\n");
    scanf("%8s", entradaIdentificador); 


    for (int i = 0; i < 8; i++) {
        if (entradaIdentificador[i] < '0' || entradaIdentificador[i] > '9') {
            printf("\033[1;37mErro: O caractere '%c' é inválido. Apenas números de 0 a 9 são permitidos.\033[0m\n", entradaIdentificador[i]);
            system("pause");
            return 1;  
        }
        digitos[i] = entradaIdentificador[i] - '0'; 
    }
    
    if (strlen(entradaIdentificador) != 8) {
        printf("\033[1;37;41mErro: E preciso digitar exatamente 8 números.\033[0m\n");
        system("pause");
        return 1;  
    }
    int resultadoValidacao = validarIdentificador(&digitos[0]); 
    if(resultadoValidacao == 1){
        system("pause");
        return 1;
    }

    
    configuracoes.espacamentoLateral = 4;
    configuracoes.densidadePixel = 1;
    configuracoes.alturaCodigo = 50;
    strcpy(configuracoes.nomeArquivo, "codigo_de_barras.pbm");
    
    printf("\033[1;36mInsira as configurações opcionais (em Pixels),\033[0m\n");
    printf("\033[1;36mou tecle enter para pular.\033[0m\n");
    
    printf("\n");
    printf("\033[1;36mBorda lateral:\033[0m\n");
    
    char entradaBuffer[100]; 
    
    getchar();
    
    fgets(entradaBuffer, sizeof(entradaBuffer), stdin); 
    
    entradaBuffer[strcspn(entradaBuffer, "\n")] = '\0';
    
    if(strlen(entradaBuffer) != 0){
        configuracoes.espacamentoLateral = atoi(entradaBuffer);
    }

    printf("\033[1;36mDensidade de pixels:\033[0m\n");

    fgets(entradaBuffer, sizeof(entradaBuffer), stdin);

    entradaBuffer[strcspn(entradaBuffer, "\n")] = '\0';

    if(strlen(entradaBuffer) != 0){
        configuracoes.densidadePixel = atoi(entradaBuffer);
    }

    printf("\033[1;36mAltura do codigo de barras:\033[0m\n");

    fgets(entradaBuffer, sizeof(entradaBuffer), stdin);

    entradaBuffer[strcspn(entradaBuffer, "\n")] = '\0';

    if(strlen(entradaBuffer) != 0){
        configuracoes.alturaCodigo = atoi(entradaBuffer);
    }

    printf("\033[1;36mNome do arquivo:\033[0m\n");

    fgets(entradaBuffer, sizeof(entradaBuffer), stdin);

    entradaBuffer[strcspn(entradaBuffer, "\n")] = '\0';

    if(strlen(entradaBuffer) != 0){
        strcpy(configuracoes.nomeArquivo, entradaBuffer);
        strcat(configuracoes.nomeArquivo, ".pbm");
    }

    
    char diretorio[256] = "CodigoGerado/";

    strncat(diretorio, configuracoes.nomeArquivo, sizeof(diretorio) - strlen(diretorio) - 1);

    strcpy(configuracoes.nomeArquivo, diretorio);


    char *codigoBarras = calloc(67+(configuracoes.espacamentoLateral*2) + 1, sizeof(char));
    converterBinario(codigoBarras, &digitos[0], configuracoes.espacamentoLateral);


    char *linhaPixels = calloc(strlen(codigoBarras)*configuracoes.densidadePixel + 1, sizeof(char));


    int indiceSaida = 0;
    for (size_t i = 0; i < strlen(codigoBarras); i++) { 
        for (int j = 0; j < configuracoes.densidadePixel; j++) {
            linhaPixels[indiceSaida++] = codigoBarras[i];
        }
    }
    linhaPixels[indiceSaida] = '\0';

 
    int resultadoArquivo = existe(configuracoes.nomeArquivo);
    if(resultadoArquivo == 1){
        criarPBM(configuracoes, linhaPixels);
    }
    if(resultadoArquivo == 2){
        printf("\033[1;36mPrograma encerrado.\033[0m\n");
    }

    free(linhaPixels);
    free(codigoBarras);
    printf("Pressione Enter para continuar...");
    getchar();
    return 0;
}