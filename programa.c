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
    int i;
    pthread_t threads_for_hashing[NUM_THREADS];
    thread_read_args args[NUM_THREADS];
    
    for(i = 0; i < NUM_THREADS; i++) {
        // memcpy(args[i].hashtable, hashtable, sizeof(hashtable));
        // args[i].hashtable = hashtable;
        args[i].hashtable = hashtable;
        args[i].id = i + 1;
        pthread_create(&(threads_for_hashing[i]), NULL, read_table, &(args[i]));
    }
    join_threads(threads_for_hashing, NUM_THREADS);
}

void join_threads(pthread_t threads[], int length) {
    int i;
    for(i = 0; i < length; i++) {
        pthread_join(threads[i], NULL);
    }
}

int first_jump(int thread_id) {
    return thread_id * JUMP_FACTOR - JUMP_FACTOR;
}

void * read_table(void * arg) {
    thread_read_args * t_args = (thread_read_args*) arg;
    FILE *arq = fopen(FILE_PATH, "r");
    block b;
    int i, j;
    int cur_block = 0;

    if (arq) {
        fseek(arq, sizeof(block) * first_jump(t_args->id), SEEK_SET);
        fread(&b, sizeof(block), 1, arq);
        //ler bloco
        while (!feof(arq)) {
            // printf("Thread: %d // Block: %d\n", t_args->id, cur_block);
            for(i=0; i < NUM_PAGES_IN_BLOCK; i++) {
                for(j=0; j < NUM_TUPLES_IN_PAGE; j++) {
                    int super_hash_bucket = get_hash(b.pages[i].tuples[j].id, SUPER_HASH_BUCKETS);
                    int mini_hash_bucket = get_hash(b.pages[i].tuples[j].id, MINI_HASH_BUCKETS);
                    switch(t_args->hashtable) {
                        case 1:
                            pthread_mutex_lock(&mutex);
                            push(&hashtable_r[super_hash_bucket][mini_hash_bucket], b.pages[i].tuples[j]);
                            pthread_mutex_unlock(&mutex);
                            break;
                        case 2:
                            pthread_mutex_lock(&mutex);
                            push(&hashtable_s[super_hash_bucket][mini_hash_bucket], b.pages[i].tuples[j]);
                            pthread_mutex_unlock(&mutex);
                            break;
                    }
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
    // print_buckets(t_args->hashtable);

    printf("\n\n");
    pthread_exit((void*) 0);
}

void join_partitions() {
    int i;
    pthread_t threads_for_join[SUPER_HASH_BUCKETS];
    thread_join_args args[SUPER_HASH_BUCKETS];

    for(i = 0; i < SUPER_HASH_BUCKETS; i++) {
        args[i].super_hash_bucket = i;
        pthread_create(&(threads_for_join[i]), NULL, start_join, &args[i]);
    }
    join_threads(threads_for_join, SUPER_HASH_BUCKETS);
    printf("Total matches: %d", match_count);
    match_count = 0;
}

void * start_join(void * arg) {
    thread_join_args * t_args = (thread_join_args*) arg;
    int cur_mini_hash_bucket;
    int super_hash_bucket = t_args->super_hash_bucket;

    node * r_node;
    node * s_node;
    int local_match_count = 0;

    for(cur_mini_hash_bucket = 0; cur_mini_hash_bucket < MINI_HASH_BUCKETS; cur_mini_hash_bucket++) {
        r_node = hashtable_r[super_hash_bucket][cur_mini_hash_bucket].head;
        while (r_node != NULL) {
            s_node = hashtable_s[super_hash_bucket][cur_mini_hash_bucket].head;
            while(s_node != NULL) {
                if(r_node->t.id == s_node->t.id) {
                    local_match_count++;
                }
                s_node = s_node->next;
            }
            r_node = r_node->next;
        }
    }
    pthread_mutex_lock(&mutex);
    match_count+= local_match_count;
    pthread_mutex_unlock(&mutex);

    printf("Thread[%d] match count: %d\n", t_args->super_hash_bucket, local_match_count);

    pthread_exit((void*) 0);
}

int get_hash(int key, int hash) {
    return key % hash;
}

void popular_arquivo_com_3milhoes_de_tuplas() {
    int i;
    FILE *arq;
    tuple t;

    for(i = 1; i <= (5000 * NUM_TUPLES_IN_PAGE * NUM_PAGES_IN_BLOCK); i++) { // Colocar FILE_ROWS OU (5000 * NUM_TUPLES_IN_PAGE * NUM_PAGES_IN_BLOCK)
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
    pthread_mutex_init(&mutex, NULL);
    int opcao = -1;
    do {
        printf("**********************************\n");
        printf("************** MENU **************\n");
        printf("**********************************\n");
        printf("\n(1) Ler Tabela R.\n(2) Ler Tabela S.\n(3) Join.\n(4) Processo completo.\n(5) Popular Arquivo\n(0) SAIR.");
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
                join_partitions();
                break;
            case 4:
                start_leitura(1);
                start_leitura(2);
                join_partitions();
                break;
            case 5:
                popular_arquivo_com_3milhoes_de_tuplas();
                break;
            default:
                printf("Por favor, insira uma opção válida. \n\n\n");
        }
    } while (opcao != 0);
    
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
}