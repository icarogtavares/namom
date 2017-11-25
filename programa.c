#include "programa.h"

void print_buckets() {
    int i, j;
    for(i = 0; i < SUPER_HASH_BUCKETS; i++) {
        printf("[%d]\n", i);
        for(j = 0; j < MINI_HASH_BUCKETS; j++) {
            printf("--[%d]\n", j);
            print_bucket(&hashtable[i][j]);
        }
    }
}

void print_bucket(linkedlist * llist) {
    node * current = llist->head;

    while (current != NULL) {
        printf("%d\n", current->t->id);
        current = current->next;
    }
}

// void ler_tabela() {
//     printf("\n\n");
//     printf("Imprimindo dados do arquivo...\n");
//     printf("******************************\n");
//     printf("\n");

//     FILE *arq = fopen(FILE_PATH, "r");
//     char line[256];
//     if (arq) {
//         while (fgets(line, sizeof(line), arq)) {
//             printf("%s", line);
//             int id = atoi(strtok(line, "|"));
//             int super_hash_bucket = get_hash(id, SUPER_HASH_BUCKETS);
//             int mini_hash_bucket = get_hash(id, MINI_HASH_BUCKETS);
//             printf("--id[%d] sup[%d] mini[%d]\n", id, super_hash_bucket, mini_hash_bucket);
//             push(&hashtable[super_hash_bucket][mini_hash_bucket], id);
//         }
//         fclose(arq);
//     }

//     print_buckets();

//     printf("\n\n");
// }

int get_hash(int key, int hash) {
    return key % hash;
}

void popular_arquivo_com_3milhoes_de_tuplas() {
    int i;
    FILE *arq;
    tuple t;

    for(i = 1; i <= 3000000; i++) {
        sprintf(t.name, "%dicaro", i);
        sprintf(t.last_name, "%dtavares", i);
        t.id = i;
        
        arq = fopen("data_test.txt", "a");
        if (arq==NULL) {
            printf("Problema em abrir o arquivo");
            exit(9);
        }
        fwrite(&t, sizeof(tuple), 1, arq);
        fclose(arq);
    }
}

void imprimir_arquivo_tupla() {
    FILE *arq;
    tuple t;

    printf("\n\n");
    printf("*****************************\n");
    printf("Imprimindo dados por tupla...\n");
    printf("*****************************\n");
    printf("\n");
    arq = fopen("data_test.txt", "r");
    rewind(arq);
    fread(&t, sizeof(tuple), 1, arq);

    while (!feof(arq)) {
        printf("%d, %s, %s\n", t.id, t.name, t.last_name);
        fread(&t, sizeof(tuple),1,arq);
    }
    printf("\n\n");
}

void imprimir_arquivo_pagina() {
    FILE *arq;
    page p;
    int i;
    printf("\n\n");
    printf("******************************\n");
    printf("Imprimindo dados por pagina...\n");
    printf("******************************\n");
    printf("\n");
    arq = fopen("data_test.txt", "r");
    rewind(arq);
    fread(&p, sizeof(page), 1, arq);

    while (!feof(arq)) {
        for(i=0; i < 2; i++) {
            printf("%d, %s, %s\n", p.tuples[i].id, p.tuples[i].name, p.tuples[i].last_name);
        }
        fread(&p, sizeof(page),1,arq);
    }
    printf("\n\n");
}

void imprimir_arquivo_bloco() {
    FILE *arq;
    block llist;
    int i, j;
    printf("\n\n");
    printf("******************************\n");
    printf("Imprimindo dados por bloco...\n");
    printf("******************************\n");
    printf("\n");
    arq = fopen("data_test.txt", "r");
    rewind(arq);
    fread(&llist, sizeof(block), 1, arq);

    while (!feof(arq)) {
        for(i=0; i < 4; i++) {
            for(j=0; j < 2; j++) {
                printf("%d, %s, %s\n", llist.pages[i].tuples[j].id, llist.pages[i].tuples[j].name, llist.pages[i].tuples[j].last_name);
            }
        }
        fread(&llist, sizeof(block),1,arq);
    }
    printf("\n\n");
}

int main(void) {
    // popular_arquivo_com_3milhoes_de_tuplas();

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
                imprimir_arquivo_bloco();
                break;
            case 2:
                getchar();
                // escrever();
                break;
            default:
                printf("Por favor, insira uma opção válida. \n\n\n");
        }
    } while (opcao != 0);
    
    return 0;    
}