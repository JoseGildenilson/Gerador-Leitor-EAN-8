# Gerador e Leitor de Código de Barras EAN-8 em C

![Linguagem C](https://img.shields.io/badge/linguagem-C-blue.svg)

## Sobre o Projeto

Este projeto foi desenvolvido como **trabalho de conclusão da disciplina de Introdução às Técnicas de Programação (ITP)**. Ele consiste em duas aplicações de console em **C** que lidam com códigos de barras no padrão **EAN-8**:

1. **Gerador de Código de Barras**
   Recebe um código EAN-8 de 8 dígitos, valida o dígito verificador e gera uma imagem do código de barras no formato `.pbm` (Portable Bitmap).

2. **Leitor de Código de Barras**
   Lê um arquivo de imagem `.pbm`, identifica e decodifica o código de barras, extraindo o número de 8 dígitos.

---

## Funcionalidades

### Gerador

* **Validação de Dígito Verificador**: Calcula o 8º dígito do código EAN-8 para garantir integridade.
* **Geração de Imagem**: Cria arquivos `.pbm` representando as barras pretas e brancas.
* **Customização**: Permite definir parâmetros como densidade de pixels, altura do código e espaçamento das bordas laterais.

### Leitor

* **Leitura de PBM**: Interpreta arquivos `.pbm` e armazena os dados em matriz para análise.
* **Decodificação de Barras**: Localiza o início do código, mede módulos (largura das barras) e traduz padrões da esquerda e direita em números.
* **Extração do Código**: Reconstrói e exibe o número EAN-8 da imagem.

---

## Estrutura do Projeto

O projeto está organizado em duas pastas principais:

```
.
├── GerarCodigoDeBarras/    # Código do gerador
│   ├── src/
│   ├── include/
│   ├── build/
│   └── Makefile
└── ExtrairCodigoDeBarras/  # Código do leitor
    ├── src/
    ├── include/
    ├── build/
    └── Makefile
```

---

## Pré-requisitos

Para compilar e executar o projeto, você precisará de:

* Compilador C (ex.: **GCC**)
* Utilitário **Make**

---

## Como Compilar e Executar

Ambas as aplicações usam **Makefiles** para simplificar a compilação.

### 1. Gerador de Código de Barras

Os arquivos `.pbm` gerados serão salvos em: `GerarCodigoDeBarras/CodigoGerado/`.

```bash
cd GerarCodigoDeBarras   # Entre na pasta do gerador
make                     # Compile o projeto
./build/ean8-generator   # Execute o programa
```

O programa solicitará:

* Código EAN-8 de 8 dígitos
* Configurações da imagem (altura, densidade das barras, bordas)

---

### 2. Leitor de Código de Barras

O leitor procura os arquivos `.pbm` gerados pelo gerador.

```bash
cd ExtrairCodigoDeBarras   # Entre na pasta do leitor
make                       # Compile o projeto
./build/ean8_leitor        # Execute o programa
```

O programa solicitará o **nome do arquivo `.pbm`** (sem a extensão).
Exemplo: se o arquivo for `teste.pbm`, digite `teste`.

---

## Colaboradora

- [RayssaBeatriz](https://github.com/RayssaBeatriz)

---

*Projeto desenvolvido para a disciplina de Introdução às Técnicas de Programação.*
