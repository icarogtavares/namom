#ifndef _DATATYPES_H
#define _DATATYPES_H

#define NUM_PAGES_IN_BLOCK 4
#define NUM_TUPLES_IN_PAGE 2
#define NUM_TUPLES_IN_BLOCK NUM_PAGES_IN_BLOCK * NUM_TUPLES_IN_PAGE

#define KEY_MAX_LENGTH (256)

typedef struct super_hash_table_s
{
    char key_string[KEY_MAX_LENGTH];
    map_t mini_hash_buckets;
} super_hash_bucket_struct;

typedef struct mini_hash_table_s
{
    char key_string[KEY_MAX_LENGTH];
    struct linkedlist llist_of_tuples;
} mini_hash_table_t;

typedef struct tuple {
    int id;
    char name[100];
    char last_name[100];
} tuple_t;

typedef struct page {
    struct tuple tuples[NUM_TUPLES_IN_PAGE];
} page_t;

typedef struct block {
    struct page pages[NUM_PAGES_IN_BLOCK];
} block_t;

#endif