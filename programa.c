#include "programa.h"

void print_buckets() {
    int i, j;
    for(i = 0; i < HASH1_BUCKETS; i++) {
        printf("[%d]\n", i);
        for(j = 0; j < HASH2_BUCKETS; j++) {
            printf("--[%d]\n", j);
            print_bucket(&hashtable[i][j]);
        }
    }
}

void print_bucket(bucket * b) {
    node * current = b->head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

void ler_arquivo() {
    printf("\n\n");
    printf("Imprimindo dados do arquivo...\n");
    printf("******************************\n");
    printf("\n");

    FILE *arq = fopen(FILE_PATH, "r");
    char line[256];
    if (arq) {
        while ( fgets(line, sizeof(line), arq) ) {
            printf("%s", line);
        }
        fclose(arq);
    }
    printf("\n\n");
}

void ler_tabela() {
    printf("\n\n");
    printf("Imprimindo dados do arquivo...\n");
    printf("******************************\n");
    printf("\n");

    FILE *arq = fopen(FILE_PATH, "r");
    char line[256];
    if (arq) {
        while (fgets(line, sizeof(line), arq)) {
            printf("%s", line);
            int id = atoi(strtok(line, "|"));
            int super_hash_bucket = get_hash(id, HASH1_BUCKETS);
            int mini_hash_bucket = get_hash(id, HASH2_BUCKETS);
            printf("--id[%d] sup[%d] mini[%d]\n", id, super_hash_bucket, mini_hash_bucket);
            push(&hashtable[super_hash_bucket][mini_hash_bucket], id);
        }
        fclose(arq);
    }

    print_buckets();

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

int get_hash(int key, int hash) {
    return key % hash;
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
                ler_tabela();
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