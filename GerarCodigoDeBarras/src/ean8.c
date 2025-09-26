#include "ean8.h"
#include <stdio.h>
#include <string.h>
int validarIdentificador(int *ptr) {
    int soma = 0; 
    

    for (int i = 0; i < 7; i++) {
        if (i % 2 == 0) { 
            soma += ptr[i] * 3;
        } else {        
            soma += ptr[i];
        }
    }
    int digito = soma % 10;
    if (digito != 0) {
        digito = 10 - digito;
    }
    
    if (digito != ptr[7]) { 
        printf("\033[1;37;41mDigito verificador invalido!\033[0m\n");
        return 1;
    }
    return 0;
}


void converterBinario(char *ptr, int *ptroriginal, int espa){
    for(int i = 0; i<espa; i++){ 
        strcat(ptr, "0");
    }
    
    strcat(ptr, "101");
    for(int i = 0; i < 4; i++){
        switch (ptroriginal[i])
        {
        case 0:
            strcat(ptr, "0001101");
            break;
        case 1:
            strcat(ptr, "0011001");
            break;
        case 2:
            strcat(ptr, "0010011");
            break;
        case 3:
            strcat(ptr, "0111101");
            break;
        case 4:
            strcat(ptr, "0100011");
            break;
        case 5:
            strcat(ptr, "0110001");
            break;
        case 6:
            strcat(ptr, "0101111");
            break;
        case 7:
            strcat(ptr, "0111011");
            break;
        case 8:
            strcat(ptr, "0110111");
            break;
        case 9:
            strcat(ptr, "0001011");
            break;
        default:
            printf("Erro ao tentar converter para binário");
            break;
        }
    }

    strcat(ptr, "01010"); 

    for(int i = 4; i < 8; i++){
        switch (ptroriginal[i])
        {
        case 0:
            strcat(ptr, "1110010");
            break;
        case 1:
            strcat(ptr, "1100110");
            break;
        case 2:
            strcat(ptr, "1101100");
            break;
        case 3:
            strcat(ptr, "1000010");
            break;
        case 4:
            strcat(ptr, "1011100");
            break;
        case 5:
            strcat(ptr, "1001110");
            break;
        case 6:
            strcat(ptr, "1010000");
            break;
        case 7:
            strcat(ptr, "1000100");
            break;
        case 8:
            strcat(ptr, "1001000");
            break;
        case 9:
            strcat(ptr, "1110100");
            break;
        default:
            printf("Erro ao tentar converter para binário");
            break;
        }
    }

    strcat(ptr, "101"); 

    for(int i = 0; i<espa; i++){
        strcat(ptr, "0");
    }     
}


int criarPBM(preferencias dados, char *ptr) {
    printf("Caminho completo: %s\n", dados.nomeArquivo);
    FILE *arquivo = fopen(dados.nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir ou criar o arquivo!\n");
        return 1;
    }

   
    fprintf(arquivo, "P1\n");

    
    int largura = strlen(ptr);
    int altura = dados.alturaCodigo * dados.densidadePixel + 2 * dados.espacamentoLateral * dados.densidadePixel;

    
    fprintf(arquivo, "%d %d\n", largura, altura);

    
    for (int i = 0; i < dados.espacamentoLateral * dados.densidadePixel; i++) {
        for (int j = 0; j < largura; j++) {
            fprintf(arquivo, "0");
            if (j < largura - 1) fprintf(arquivo, " "); 
        }
        fprintf(arquivo, "\n"); 
    }

    
    for (int i = 0; i < dados.alturaCodigo * dados.densidadePixel; i++) {
        for (int j = 0; j < largura; j++) {
            fprintf(arquivo, "%c", ptr[j]);
            if (j < largura - 1) fprintf(arquivo, " ");
        }
        fprintf(arquivo, "\n");
    }

    
    for (int i = 0; i < dados.espacamentoLateral * dados.densidadePixel; i++) {
        for (int j = 0; j < largura; j++) {
            fprintf(arquivo, "0");
            if (j < largura - 1) fprintf(arquivo, " "); 
        }
        fprintf(arquivo, "\n"); 
    }

    fclose(arquivo);
    return 0; 
}





int existe(char *nomeArquivo){
    int decisao = 1;
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo != NULL) {
        printf("\033[1;37mJá existe um arquivo com este nome\033[0m\n");
        printf("\033[1;36mDeseja sobreescrever o arquivo?\033[0m\n");
        printf("1 - sim\n");
        printf("2 - não\n");
        scanf("%d", &decisao);
        fclose(arquivo);
        return decisao;
    }
    else{
        return decisao;
    }
}

void head(){
    printf("\033[1;34m=======================================\033[0m\n");
    printf("\033[1;44m             Gerador EAN-8             \033[0m\n");
    printf("\033[1;34m=======================================\033[0m\n");
    printf("\033[1;34mSeja bem vindo ao nosso gerador EAN-8\033[0m\n");
}



