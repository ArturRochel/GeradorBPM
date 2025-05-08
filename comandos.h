#include "comandos.c"
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    int pixel;
    int espacamento;
    int altura;
    int caracteres;
} Perfil;

int somar(int codigo[8]);
void codificar(int codigo[8], int espacamento, char *palavra);
int gerarPBM(FILE *file, int caracteres, int pixel, int altura, int espacamento, char *binario);
int verificarArquivo(const char nome[50]);
void barraProgresso();
void exibirMenu();
void preferencias();
void gerenciarMenu(char *entrada);