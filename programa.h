#ifndef _PROGRAMA_H
#define _PROGRAMA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"
#include "datatypes.h"

#define FILE_PATH "teste.txt"

/*
    SUPER_HASH => No. de buckets da Super Hash Table
    MINI_HASH => No. de buckets da Mini Hash Table
    h1 => Vetor representando buckets da SuperHashTable
    h2 => Vetor representando buckets da MiniHashTable
*/
#define SUPER_HASH_BUCKETS 3
#define MINI_HASH_BUCKETS 5

// Interessante seria criar "node ** h1" e alocar memória de acordo como são preenchidos os buckets
//  para não ficar buckets vazios alocados em memória.
bucket hashtable[SUPER_HASH_BUCKETS][MINI_HASH_BUCKETS];

void print_buckets();
void print_bucket(bucket * b);
// void ler_tabela();
void escrever();
int get_hash(int key, int hash);

void popular_arquivo_com_3milhoes_de_tuplas();

void imprimir_arquivo_tupla();
void imprimir_arquivo_pagina();
void imprimir_arquivo_bloco();

#endif