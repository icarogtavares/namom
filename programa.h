#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

#define FILE_PATH "teste.txt"

/*
    Hash1 => No. de buckets da Super Hash Table
    Hash2 => No. de buckets da Mini Hash Table
    h1 => Vetor representando buckets da SuperHashTable
    h2 => Vetor representando buckets da MiniHashTable
*/
#define HASH1_BUCKETS 3
#define HASH2_BUCKETS 5

// Interessante seria criar "node ** h1" e alocar memória de acordo como são preenchidos os buckets
//  para não ficar buckets vazios alocados em memória.
bucket hashtable[HASH1_BUCKETS][HASH2_BUCKETS];

void print_buckets();
void print_bucket(bucket * b);
void ler_arquivo();
void ler_tabela();
void escrever();
int get_hash(int key, int hash);