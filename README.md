# Gerador e Leitor de Código de Barras EAN-8 (PBM)

Este projeto tem como objetivo a criação de dois programas em linguagem C: um para gerar imagens de códigos de barras no padrão **EAN-8**, e outro para ler essas imagens e extrair o código representado. As imagens são geradas e manipuladas no formato **PBM (Portable Bitmap Format)**, utilizando apenas preto e branco.

O trabalho foi desenvolvido como parte da disciplina **Introdução de Técnicas de Programação (ITP)**.

## Funcionalidades

- **Geração de Código de Barras**
  - Gera um código de barras EAN-8 válido a partir de um identificador numérico de 8 dígitos.
  - Cria uma imagem PBM representando o código com opções configuráveis via linha de comando (largura das barras, altura, espaçamento e nome do arquivo).
  - Valida o identificador (formato e dígito verificador).
  - Verifica se o arquivo de imagem já existe e trata possíveis conflitos.

- **Leitura de Código de Barras**
  - Lê uma imagem PBM contendo um código de barras EAN-8.
  - Valida o formato da imagem.
  - Extrai e imprime o código representado na imagem, incluindo verificação do dígito verificador.

## Tecnologias Utilizadas

- Linguagem de programação **C**
- Manipulação de arquivos no formato **PBM (ASCII)**

## Estrutura do Projeto

- `gerador.c` — Contém a função `main()` responsável por gerar o código de barras.
- `leitor.c` — Contém a função `main()` responsável por ler o código de barras.
- Arquivos auxiliares `.c` e `.h` — Funções e estruturas compartilhadas entre os dois programas (leitura/escrita de PBM, cálculo de dígito verificador, codificação binária, etc).

## Autores

- **Artur Rochel Araujo do Nascimento**
- **Antonio Jamykson Freitas Holanda**
