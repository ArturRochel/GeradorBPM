#include <stdio.h>
#include "decodificar.h"

int main() {
    char caminho[100];
    printf("Digite o nome do arquivo .pbm (inclua a extensao): ");
    scanf("%s", caminho);

    ImagemPBM imagem = carregar_imagem(caminho); // Carrega o pbm escolhido pelo usuário

    int vetores[8][7];
    preencher_vetores(imagem.dados, vetores);

    // Imprime os números correspondentes às sequencias de 7 caracteres, em ordem
    printf("%d%d%d%d%d%d%d%d\n",
           mapear_v1_a_v4(vetores[0]), mapear_v1_a_v4(vetores[1]),
           mapear_v1_a_v4(vetores[2]), mapear_v1_a_v4(vetores[3]),
           mapear_v5_em_diante(vetores[4]), mapear_v5_em_diante(vetores[5]),
           mapear_v5_em_diante(vetores[6]), mapear_v5_em_diante(vetores[7]));

    liberar_imagem(&imagem); // Libera a memória alocada
    return 0;
}
