#include <stdio.h> // Padrão
#include <string.h> // String
#include <stdlib.h> // Alocação Dinâmica
#include <math.h> // Operações matemáticas
#include <errno.h> // Erros
#include <ctype.h> // Verificação digito
#include <unistd.h> // Para usar sleep()
#include "comandos.h" // Funções e structs

int main() {
    char entrada[9];
    int codigo[8];
    int soma=0, multi=0;
    int verificador, preferencia, sobrescrever;
    char nomeArquivo[50];


    gerenciarMenu(entrada); 

    // Verifica se a entrada possui 8 dígitos
    if(strlen(entrada) != 8) {
        printf("\033[1;31mERRO: O código deve ter 8 inteiros.\033[0m\n");
        printf("\033[1;34mDigite um novo código: \033[0m");
        entrada[0] = '\0';
        getchar();
        scanf("%s", entrada);
        getchar();
        if(strlen(entrada) != 8) {
            printf("\033[1;31mERRO: O código deve ter 8 inteiros.\033[0m\n");
            printf("\033[1;31mSaindo do programa...\033[0m\n");
            return 1;
        }
    }

    // Transforma string em inteiro
    for(int i=0; i<8; i++) {
        if(isdigit(entrada[i])) {
            codigo[i] = entrada[i] - '0';
    } else {
            printf("\033[1;31mERRO: O código deve conter apenas inteiros.\033[0m\n");
            return 1;
        }
    }
    // calcula a soma
    soma = somar(codigo);
    // Próximo múltiplo de 10
    multi = ceil(soma/10.0) * 10;

    // Testa o digito verificador
    if((multi-soma) != codigo[7]) {
        printf("\033[1;31mDígito verificad34567890or inválido.\033[0m\n");
        return 1;
    }

    // Struct de preferências
    Perfil dados;

    preferencias();
    scanf("%d", &preferencia);

    switch (preferencia) {
        case 1:
            printf("\033[1;33mDigite o nome: \033[0m");
            scanf("%s", dados.nome);
            dados.nome[strcspn(dados.nome, "\n")] = '\0';
            strcat(dados.nome, ".pbm");
            printf("\033[1;33mDigite o espaçamento: \033[0m");
            scanf("%d", &dados.espacamento);
            getchar();
            printf("\033[1;33mDigite os pixels de equivalência: \033[0m");
            scanf("%d", &dados.pixel);
            getchar();
            printf("\033[1;33mDigite a altura: \033[0m");
            scanf("%d", &dados.altura);
            dados.altura = dados.altura+(dados.espacamento*2);
            getchar();
            dados.caracteres = (67+(dados.espacamento*2));
            break;
        case 2:
            printf("\033[1;32mPreferências padrões utilizadas.\033[0m\n");
            strcpy(dados.nome, "realcodigo.pbm");
            dados.espacamento = 6;
            dados.pixel = 7;
            dados.altura = 50+(dados.espacamento*2);
            dados.caracteres = (67+(dados.espacamento*2));
            break;
    }

     // Verifica a existência do arquivo
    strcpy(nomeArquivo, dados.nome);

    if(verificarArquivo(nomeArquivo)) {
        printf("\n");
        printf("\033[1;31mO arquivo %s já existe.\033[0m\n", dados.nome);
        printf("\n");
        printf("\033[1;34mVocê deseja sobrescrever o arquivo: \033[0m\n");
        printf("\033[1;33m1. Sim\033[0m\n");
        printf("\033[1;33m2. Não\033[0m\n");
        printf("\033[1;34mOpção: \033[0m");
        scanf("%d", &sobrescrever);
    }

   if(sobrescrever == 2) {
        printf("\033[1;31mO arquivo resultante já existe.\033[0m\n");
        printf("\033[1;31mFinalizando o programa...\033[0m\n");
        return 1;
   }

    // Preparação string binario
    char *pre = (char *)malloc((dados.caracteres + 1) * sizeof(char));
    if(pre==NULL) {
        printf("ERRO MALLOC PRE\n");
        return 1;
    }

    // Preparação inteiros binarios
    char *binario = (char *)malloc(dados.caracteres*dados.pixel * sizeof(char));
    if(binario == NULL) {
        printf("ERRO MALLOC BINARIO\n");
        return 1;
    }

    // Função que criar o binário em string
    codificar(codigo, dados.espacamento, pre);

    int k=0;
    // TRANSFORMAR STRING EM STRING*PIXEL
    for(int i=0; i<dados.caracteres; i++) {
        if(isdigit(pre[i])) {
            for(int j=0; j<dados.pixel; j++) {
                binario[k++] = pre[i];
            }
        };
    }
    // Zera string binaria pre
    strcpy(pre, "");

    // FORMAR IMAGEM

    FILE *file = fopen(dados.nome, "w");
    if(file == NULL) {
        printf("ERRO: %s\n", strerror(errno));
        return 1;
    } else {
        if(gerarPBM(file, dados.caracteres, dados.pixel, dados.altura, dados.espacamento, binario) == 1) {
            printf("\033[1;33mIniciando o processo...\033[0m\n");
            barraProgresso();
            printf("\033[1;32mImagem gerada com sucesso!\033[0m\n");
            fclose(file);
        }
    }
    
    free(pre);
    free(binario);
    return 0;
}