#ifndef _PROGRAMA_H
#define _PROGRAMA_H

#include "main.h"
#include "linkedlist.h"
#include "datatypes.h"


#define FILE_PATH "data_test.txt"
#define FILE_ROWS 3000000
#define BLOCKS_IN_TABLE FILE_ROWS / NUM_TUPLES_IN_BLOCK
#define NUM_THREADS 4
#define JUMP_FACTOR 10

/*
    SUPER_HASH => No. de buckets da Super Hash Table
    MINI_HASH => No. de buckets da Mini Hash Table
    h1 => Vetor representando buckets da SuperHashTable
    h2 => Vetor representando buckets da MiniHashTable
*/
#define SUPER_HASH_BUCKETS 3
#define MINI_HASH_BUCKETS 5

typedef struct thread_read_args {
    // linkedlist * hashtable[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS];
    int hashtable; // [1=hashtable_r], [2=hashtable_s]
    int id;
} thread_read_args;

typedef struct thread_join_args {
    int super_hash_bucket;
} thread_join_args;

// Interessante seria criar "node ** h1" e alocar memória de acordo como são preenchidos os buckets
//  para não ficar buckets vazios alocados em memória.
linkedlist hashtable_r[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS];
linkedlist hashtable_s[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS];

int match_count = 0; // Para o join

pthread_mutex_t mutex;

void print_buckets(linkedlist hashtable[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS]);
void print_linkedlist(linkedlist * llist);

void start_leitura(int hashtable);
void join_threads(pthread_t threads[], int length);
int first_jump(int thread_id);
void * read_table(void * arg);

void join_partitions();
void * start_join(void * arg);

int get_hash(int key, int hash);

void popular_arquivo_com_3milhoes_de_tuplas();

void imprimir_arquivo_tupla();
void imprimir_arquivo_pagina();
void imprimir_arquivo_bloco();

void init_mutexes();

#endif