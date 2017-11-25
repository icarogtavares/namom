#ifndef _DATATYPES_H
#define _DATATYPES_H

typedef struct tuple {
    int id;
    char name[100];
    char last_name[100];
} tuple;

typedef struct page {
    struct tuple tuples[2];
} page;

typedef struct block {
    struct page pages[4];
} block;

#endif