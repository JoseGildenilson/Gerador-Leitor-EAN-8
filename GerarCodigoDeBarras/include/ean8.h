#ifndef COMANDO_H
#define COMANDO_H
#include <stdio.h>

int validarIdentificador(int *ptr);

typedef struct{
    int espacamentoLateral; 
    int densidadePixel;
    int alturaCodigo;
    char nomeArquivo[100];
}preferencias;


void converterBinario(char *ptr, int *ptroriginal, int espa);

int criarPBM(preferencias dados, char *ptr);

int existe(char *nome);

void head();

void loading();

#endif 
