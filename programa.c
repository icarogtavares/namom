#include "programa.h"

void ler_arquivo() {
    printf("\n\n");
    printf("Imprimindo dados do arquivo...\n");
    printf("******************************\n");
    printf("\n");

    FILE *arq = fopen(FILE_PATH, "r");
    char line[256];
    if (arq) {
        while (fgets(line, sizeof(line), arq)) {
            printf("%s", line);
            char *p;
            p = strtok(line, "|");
            if(p) {
                printf("%d\n", atoi(p));
            }
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

int hash1(int key) {
    return key % HASH1_BUCKETS;
}

int hash2(int key) {
    return key % HASH2_BUCKETS;
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