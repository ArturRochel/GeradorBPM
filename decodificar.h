#ifndef DECODIFICAR_H
#define DECODIFICAR_H

#include <stdio.h>

// Definição da estrutura para manipulação de imagens PBM
typedef struct {
    int largura;
    int altura;
    int *dados; // Vetor dinâmico para armazenar os dados da imagem
} ImagemPBM;

// Funções para manipulação de imagens PBM
ImagemPBM carregar_imagem(const char *caminho); // Carrega a imagem PBM a partir de um arquivo
void liberar_imagem(ImagemPBM *imagem);         // Libera a memória alocada para a imagem
int mapear_v1_a_v4(int *v);                     // Mapeia segmentos binários (v1 a v4) para números
int mapear_v5_em_diante(int *v);                // Mapeia segmentos binários (v5 em diante) para números
void preencher_vetores(int *lista, int vetores[8][7]); // Divide a lista em vetores de 7 caracteres

#endif
