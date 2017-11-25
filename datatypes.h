#ifndef _DATATYPES_H
#define _DATATYPES_H

#define NUM_PAGES_IN_BLOCK 4
#define NUM_TUPLES_IN_PAGE 2

typedef struct tuple {
    int id;
    char name[100];
    char last_name[100];
} tuple;

typedef struct page {
    struct tuple tuples[NUM_TUPLES_IN_PAGE];
} page;

typedef struct block {
    struct page pages[NUM_PAGES_IN_BLOCK];
} block;

#endif