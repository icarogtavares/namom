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

void start_leitura(int hashtable) {
    create_threads(hashtable);
}

void create_threads(int hashtable) {
    int i;
    thread_join_args args[NUM_THREADS];
    
    for(i = 0; i < NUM_THREADS; i++) {
        // memcpy(args[i].hashtable, hashtable, sizeof(hashtable));
        // args[i].hashtable = hashtable;
        args[i].hashtable = hashtable;
        args[i].id = i + 1;
        pthread_create(&(threads[i]), NULL, ler_tabela, &(args[i]));
    }
    join_threads();
}

void join_threads() {
    int i;
    for(i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

int init_jump(int thread_id) {
    return thread_id * JUMP_FACTOR - JUMP_FACTOR;
}

void * ler_tabela(void * arg) {
    thread_join_args * join_args = (thread_join_args*) arg;
    FILE *arq = fopen(FILE_PATH, "r");
    block b;
    int i, j;
    int cur_block = 0;

    if (arq) {
        fseek(arq, sizeof(block) * init_jump(join_args->id), SEEK_SET);
        fread(&b, sizeof(block), 1, arq);
        //ler bloco
        while (!feof(arq)) {
            printf("Thread: %d // Block: %d\n", join_args->id, cur_block);
            for(i=0; i < NUM_PAGES_IN_BLOCK; i++) {
                for(j=0; j < NUM_TUPLES_IN_PAGE; j++) {
                    int super_hash_bucket = get_hash(b.pages[i].tuples[j].id, SUPER_HASH_BUCKETS);
                    int mini_hash_bucket = get_hash(b.pages[i].tuples[j].id, MINI_HASH_BUCKETS);
                    switch(join_args->hashtable) {
                        case 1:
                            pthread_mutex_lock(&mutex_hashtable);
                            push(&hashtable_r[super_hash_bucket][mini_hash_bucket], b.pages[i].tuples[j]);
                            pthread_mutex_unlock(&mutex_hashtable);
                            break;
                        case 2:
                            pthread_mutex_lock(&mutex_hashtable);
                            push(&hashtable_s[super_hash_bucket][mini_hash_bucket], b.pages[i].tuples[j]);
                            pthread_mutex_unlock(&mutex_hashtable);
                            break;
                    }
                    // push(join_args->hashtable[super_hash_bucket][mini_hash_bucket], b.pages[i].tuples[j]);
                    // printf("%d, %s, %s\n", b.pages[i].tuples[j].id, b.pages[i].tuples[j].name, b.pages[i].tuples[j].last_name);
                }
            }
            ++cur_block;
            if(cur_block == JUMP_FACTOR) {
                fseek(arq, sizeof(block) * (JUMP_FACTOR * NUM_THREADS - JUMP_FACTOR), SEEK_CUR);
                cur_block = 0;
            }
            fread(&b, sizeof(block), 1, arq);
        }

        fclose(arq);        
    }

    //Método para imprimir os buckets após fazer a leitura da tabela
    // print_buckets(join_args->hashtable);

    printf("\n\n");
    pthread_exit((void*) 0);
}

void start_join(linkedlist hashtable_r[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS], linkedlist hashtable_s[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS]) {
    int i, j;
    node * r_node;
    node * s_node;
    int count = 0;
    for(i = 0; i < SUPER_HASH_BUCKETS; i++) {
        for(j = 0; j < MINI_HASH_BUCKETS; j++) {
            r_node = hashtable_r[i][j].head;
            while (r_node != NULL) {
                s_node = hashtable_s[i][j].head;
                while(s_node != NULL) {
                    if(r_node->t.id == s_node->t.id) {
                        count++;
                        printf("R %d deu match em S %d\n", r_node->t.id, s_node->t.id);
                    }
                    s_node = s_node->next;
                }
                r_node = r_node->next;
            }
        }
    }
    printf("Matches: %d", count);
}

int get_hash(int key, int hash) {
    return key % hash;
}

void popular_arquivo_com_3milhoes_de_tuplas() {
    int i;
    FILE *arq;
    tuple t;

    for(i = 1; i <= 5000 * NUM_TUPLES_IN_PAGE * NUM_PAGES_IN_BLOCK; i++) { // Colocar FILE_ROWS no <=
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

int main(int argc, char **argv) {
    pthread_mutex_init(&mutex_hashtable, NULL);
    int opcao = -1;
    do {
        printf("**********************************\n");
        printf("************** MENU **************\n");
        printf("**********************************\n");
        printf("\n(1) Ler Tabela R.\n(2) Ler Tabela S.\n(3) Join.\nProcesso completo.\n(5) Popular Arquivo\n(0) SAIR.");
        printf("\nDigite a opçao desejada: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                start_leitura(1);
                break;
            case 2:
                start_leitura(2);
                break;
            case 3:
                start_join(hashtable_r, hashtable_s);
                break;
            case 4:
                start_leitura(1);
                start_leitura(2);
                start_join(hashtable_r, hashtable_s);
                break;
            case 5:
                popular_arquivo_com_3milhoes_de_tuplas();
                break;
            default:
                printf("Por favor, insira uma opção válida. \n\n\n");
        }
    } while (opcao != 0);
    
    pthread_mutex_destroy(&mutex_hashtable);
    pthread_exit(NULL);
}