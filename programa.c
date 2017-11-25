#include "programa.h"

void print_buckets(linkedlist hashtable[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS]) {
    int i, j;
    for(i = 0; i < SUPER_HASH_BUCKETS; i++) {
        printf("[%d]\n", i);
        for(j = 0; j < MINI_HASH_BUCKETS; j++) {
            printf("--[%d]\n", j);
            print_linkedlist(&hashtable[i][j]);
        }
    }
}

void print_linkedlist(linkedlist * llist) {
    node * current = llist->head;

    while (current != NULL) {
        printf("%d, %s, %s\n", current->t.id, current->t.name, current->t.last_name);
        current = current->next;
    }
}

void ler_tabela(linkedlist hashtable[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS]) {
    FILE *arq = fopen(FILE_PATH, "r");
    block b;

    int i, j;
    if (arq) {
        rewind(arq);
        fread(&b, sizeof(block), 1, arq);
    
        //lerblock
        while (!feof(arq)) {
            for(i=0; i < NUM_PAGES_IN_BLOCK; i++) {
                for(j=0; j < NUM_TUPLES_IN_PAGE; j++) {
                    int super_hash_bucket = get_hash(b.pages[i].tuples[j].id, SUPER_HASH_BUCKETS);
                    int mini_hash_bucket = get_hash(b.pages[i].tuples[j].id, MINI_HASH_BUCKETS);
                    push(&hashtable[super_hash_bucket][mini_hash_bucket], b.pages[i].tuples[j]);
                    // printf("%d, %s, %s\n", b.pages[i].tuples[j].id, b.pages[i].tuples[j].name, b.pages[i].tuples[j].last_name);
                }
            }
            fread(&b, sizeof(block),1,arq);
        }

        fclose(arq);
    }

    // print_buckets(hashtable);

    printf("\n\n");
}

void start_join(linkedlist hashtable_r[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS], linkedlist hashtable_s[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS]) {
    int i, j;
    node * r_node;
    node * s_node;
    for(i = 0; i < SUPER_HASH_BUCKETS; i++) {
        for(j = 0; j < MINI_HASH_BUCKETS; j++) {
            r_node = hashtable_r[i][j].head;
            while (r_node != NULL) {
                s_node = hashtable_s[i][j].head;
                while(s_node != NULL) {
                    if(r_node->t.id == s_node->t.id) {
                        printf("R %d deu match em S %d", r_node->t.id, s_node->t.id);
                    }
                    s_node = s_node->next;
                }
                r_node = r_node->next;
            }
        }
    }
}

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
    block b;
    int i, j;
    printf("\n\n");
    printf("******************************\n");
    printf("Imprimindo dados por bloco...\n");
    printf("******************************\n");
    printf("\n");
    arq = fopen("data_test.txt", "r");
    rewind(arq);
    fread(&b, sizeof(block), 1, arq);

    while (!feof(arq)) {
        for(i=0; i < 4; i++) {
            for(j=0; j < 2; j++) {
                printf("%d, %s, %s\n", b.pages[i].tuples[j].id, b.pages[i].tuples[j].name, b.pages[i].tuples[j].last_name);
            }
        }
        fread(&b, sizeof(block),1,arq);
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
        printf("\n(1) Ler Tabela R\n(2) Ler Tabela S \n(3) Join \n(0) SAIR");
        printf("\nDigite a opçao desejada: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                ler_tabela(hashtable_r);
                break;
            case 2:
                ler_tabela(hashtable_s);
                break;
            case 3:
                start_join(hashtable_r, hashtable_s);
                break;
            default:
                printf("Por favor, insira uma opção válida. \n\n\n");
        }
    } while (opcao != 0);
    
    return 0;    
}