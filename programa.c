#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "programa.h"

#define FILE_PATH "teste.txt"

void ler_arquivo() {
    printf("\n\n");
    printf("******************************\n");
    printf("Imprimindo dados do arquivo...\n");
    printf("******************************\n");
    printf("\n");

    FILE *arq = fopen(FILE_PATH, "a+");
    char c;
    if (arq) {
        while ((c = getc(arq)) != EOF) {
            putchar(c);
        }
        fclose(arq);
    }

    printf("\n\n");
}

void escrever() {
    char frase[60];
    
    printf("Digite a frase: ");
    fgets(frase, 60, stdin);

    FILE *arq = fopen(FILE_PATH, "a");
    if(arq) {
        fputs(frase, arq);
        fclose(arq);
    }
}

int main(void) {

    int opcao = -1;
    do {
        printf("**********************************\n");
        printf("************** MENU **************\n");
        printf("**********************************\n");
        printf("\n(1) Ler arquivo (2) Escrever no arquivo (0) SAIR");
        printf("\nDigite a opçao desejada: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                ler_arquivo();
                break;
            case 2:
                getchar();
                escrever();
                break;
            default:
                printf("Por favor, insira uma opção válida. \n\n\n");
        }
    } while (opcao != 0);
    
    return 0;    
}