// FUNÇÃO DE SOMAR
int somar(int codigo[8]) {
    int resultado=0;
    for(int i=0; i<7; i++) {
        if(i%2==0) {
            resultado += codigo[i]*3;
        } else {
            resultado += codigo[i];
        }
    }

    return resultado;
}

// FUNÇÃO DE PREENCHER STRING BINARIA
void codificar(int codigo[8], int espacamento, char *palavra) {
    // Espaçamento lateral esquerda
    for(int i=0; i<espacamento; i++) {
        strcat(palavra, "0");
    }

    // Marcador inicial
    strcat(palavra, "101");

    //Codificação L-code
    for(int i=0; i<4; i++) {
        switch (codigo[i]) {    
        case 0:
            strcat(palavra, "0001101");
            break;
        case 1:
            strcat(palavra, "0011001");
            break;
        case 2:
            strcat(palavra, "0010011");
            break;
        case 3:
            strcat(palavra, "0111101");
            break;
        case 4:
            strcat(palavra, "0100011");
            break;
        case 5:
            strcat(palavra, "0110001");
            break;
        case 6:
            strcat(palavra, "0101111");
            break;
        case 7:
            strcat(palavra, "0111011");
            break;
        case 8:
            strcat(palavra, "0110111");
            break;
        case 9:
            strcat(palavra, "0001011");
            break;
        }
    }

    // Marcador Central
    strcat(palavra, "01010");

    // Codificação R-code
    for(int i=4; i<8; i++) {
        switch (codigo[i]) {
        case 0:
            strcat(palavra, "1110010");
            break;
        case 1:
            strcat(palavra, "1100110");
            break;
        case 2:
            strcat(palavra, "1101100");
            break;
        case 3:
            strcat(palavra, "1000010");
            break;
        case 4:
            strcat(palavra, "1011100");
            break;
        case 5:
            strcat(palavra, "1001110");
            break;
        case 6:
            strcat(palavra, "1010000");
            break;
        case 7:
            strcat(palavra, "1000100");
            break;
        case 8:
            strcat(palavra, "1001000");
            break;
        case 9:
            strcat(palavra, "1110100");
            break;
        }
    }

    // Marcador final
    strcat(palavra, "101");

    // Espaçamento lateral direita
    for(int i=0; i<espacamento; i++) {
        strcat(palavra, "0");
    }
}

// VERIFICA SE O ARQUIVO JÁ EXISTE
int verificarArquivo(const char nome[50]) {
    FILE *arquivo = fopen(nome, "r");
    if (arquivo) {
        fclose(arquivo);
        return 1;
    }

    return 0;
}

// FUNÇÃO DE GERAR IMAGEM
int gerarPBM(FILE *file, int caracteres, int pixel, int altura, int espacamento, char *binario) {
    int retorno;
    // Formatação PBM
    fprintf(file, "P1\n");
    fprintf(file, "%d %d\n", caracteres*pixel, altura*pixel);

    // Espaçamento superior
    for(int i=0; i<espacamento*pixel; i++) {
        for(int j=0; j<caracteres*pixel; j++) {
            fprintf(file, "0");
        }
    }

    // string = "000101...101000"
    // int = 000101..101000, int[0], 67+6 int[0 -> 72]


    for(int linha = 0; linha<(altura-espacamento*2)*pixel; linha++) {
        for(int i=0; i<caracteres*pixel; i++) {
            fprintf(file, "%c", binario[i]);
        }
    }

    // Espaçamento inferior
    for(int i=0; i<espacamento*pixel; i++) {
        for(int j=0; j<caracteres*pixel; j++) {
            fprintf(file, "0");
        }
    }

    retorno = 1;
    return retorno;
}

// INTERFACE TERMINAL

void exibirMenu() {
    printf("\033[1;31m======== GERADOR DE CÓDIGO ========\033[0m\n");
    printf("\033[1;34m========= MENU PRINCIPAL ==========\033[0m\n");
    printf("\033[1;33m1. Inserir código\033[0m\n");
    printf("\033[1;33m2. Exibir informações\033[0m\n");
    printf("\033[1;33m3. Sair\033[0m\n");
    printf("\033[1;34m===================================\033[0m\n");
    printf("\033[1;36mEscolha uma opção: \033[0m");
}

void preferencias() {
    printf("\033[1;34mVocê deseja escolher as preferências: \033[0m\n");
    printf("\033[1;33m1. Sim\033[0m\n");
    printf("\033[1;33m2. Não\033[0m\n");
    printf("\033[1;34mOpção: \033[0m");
}

// LOOP MENU
void gerenciarMenu(char *entrada) {
    int continuar=1, opcao;
    while(continuar) {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao)  {
        case 1:
            printf("\033[1;34mDigite o código: \033[0m");
            scanf("%s", entrada);
            getchar();
            continuar = 0;
            break;
        case 2: 
            printf("\n");
            printf("\033[1;34mEste programa gera imagens.pbm através de códigos EAN-8.\033[0m\n");
            printf("\033[1;34mPara gerar um arquivo .pbm basta inserir um código válido de 8 inteiros.\033[0m\n");
            printf("\n");
            break;
        case 3:
            printf("\033[1;31mSaindo do programa...\033[0m\n");
            continuar=0;
            exit(0);
            break;
        default:
            printf("\n");
            printf("\033[1;31mERRO: Opção inválida. Insira uma das opções do menu.\033[0m\n");
            printf("\n");
            break;
        }
    }
}

void barraProgresso() {
    printf("\033[1;34mGerando imagem: [\033[0m");
    for (int i = 0; i < 20; i++) {
        printf("\033[1;32m#\033[0m");
        fflush(stdout);
        usleep(100000); // 100ms
    }
    printf("\033[1;34m]\033[0m\n");
}

