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

node h1[HASH1_BUCKETS];
node h2[HASH2_BUCKETS];

void ler_arquivo();
void escrever();
int hash1(int key);
int hash2(int key);