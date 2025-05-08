#include "decodificar.h"
#include <stdlib.h>
#include <string.h>

// Função para abrir a imagem PBM no modo de leitura
ImagemPBM carregar_imagem(const char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        fprintf(stderr, "Erro: O arquivo '%s.pbm nao existe.\n", caminho);
        exit(1);
    }

    char linha[240000];
    int linhaAtual = 0, proporcao = 0;

    // Lê as proporções da imagem
    while (fgets(linha, sizeof(linha), arquivo)) {
        linhaAtual++;
        if (linhaAtual == 3) {
            int i = 0;
            while (linha[i] != '\0') {
                if (linha[i] == '1') {
                    proporcao++;
                } else if (proporcao > 0) {
                    break;
                }
                i++;
            }
            break;
        }
    }

    rewind(arquivo); // Retorna ao início do arquivo para reler as informações
    linhaAtual = 0;

    // Aloca a estrutura da imagem
    ImagemPBM imagem;
    imagem.largura = 0;
    imagem.altura = 0;
    imagem.dados = NULL;

    imagem.dados = (int *)malloc(56 * sizeof(int)); // cria uma lista usando malloc
    if (!imagem.dados) {
        fprintf(stderr, "Erro ao alocar memória para os dados da imagem.\n");
        fclose(arquivo);
        exit(1);
    }

    int k = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        linhaAtual++;
        if (linhaAtual == 3) { // Processa a terceira linha
            int j = 0, i = 0;
            while (linha[i] != '\0' && linha[i] != '1') {
                i++;// Ignora até encontrar o primeiro "1"
            }

            while (linha[i] != '\0' && j < 67) { // Processa 67 bits da linha
                if ((j > 2 && j < 31) || (j > 35 && j < 64)) { // Vai ignorar as partes que não fazem parte do codigo
                    imagem.dados[k] = linha[i] - '0'; // Converte para inteiro e armazena em imagem.dados
                    k++;
                }
                j++;
                i += proporcao;
            }
            break;
        }
    }

    fclose(arquivo);
    return imagem;
}

// Função para liberar a memória de uma imagem PBM
void liberar_imagem(ImagemPBM *imagem) {
    if (imagem->dados) {
        free(imagem->dados); // Libera a memória
        imagem->dados = NULL;
    }
}

// Funções de mapeamento e preenchimento
int mapear_v1_a_v4(int *v) {

    char binario[8];
    for (int i = 0; i < 7; i++) binario[i] = v[i] + '0';
    binario[7] = '\0';
    if (strcmp(binario, "0001101") == 0) return 0;
    if (strcmp(binario, "0011001") == 0) return 1;
    if (strcmp(binario, "0010011") == 0) return 2;
    if (strcmp(binario, "0111101") == 0) return 3;
    if (strcmp(binario, "0100011") == 0) return 4;
    if (strcmp(binario, "0110001") == 0) return 5;
    if (strcmp(binario, "0101111") == 0) return 6;
    if (strcmp(binario, "0111011") == 0) return 7;
    if (strcmp(binario, "0110111") == 0) return 8;
    if (strcmp(binario, "0001011") == 0) return 9;
    return -1; // Retorna -1 se não houver reconhecimento
}

int mapear_v5_em_diante(int *v) {

    char binario[8];
    for (int i = 0; i < 7; i++) binario[i] = v[i] + '0';
    binario[7] = '\0';
    if (strcmp(binario, "1110010") == 0) return 0;
    if (strcmp(binario, "1100110") == 0) return 1;
    if (strcmp(binario, "1101100") == 0) return 2;
    if (strcmp(binario, "1000010") == 0) return 3;
    if (strcmp(binario, "1011100") == 0) return 4;
    if (strcmp(binario, "1001110") == 0) return 5;
    if (strcmp(binario, "1010000") == 0) return 6;
    if (strcmp(binario, "1000100") == 0) return 7;
    if (strcmp(binario, "1001000") == 0) return 8;
    if (strcmp(binario, "1110100") == 0) return 9;
    return -1; // Retorna -1 se não houver reconhecimento
}

// Função para dividir a lista de dados em vetores de 7 bits para que possa ocorrer a verificação
void preencher_vetores(int *lista, int vetores[8][7]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++) {
            vetores[i][j] = lista[i * 7 + j];
        }
    }
}
