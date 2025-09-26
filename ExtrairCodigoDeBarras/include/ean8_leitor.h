#ifndef EAN8_LEITOR_H
#define EAN8_LEITOR_H

void exibirCabecalho();
void lerArquivoPBM(const char *arquivo);
void extrairIdentificador();
void liberarMatriz();
int bitsParaDecimal(int *bits, int tamanho);

#endif
