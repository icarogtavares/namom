#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "main.h"
#include "datatypes.h"

typedef struct node {
    struct tuple t;
    struct node * next;
} node;

typedef struct linkedlist {
    node * head;
    pthread_mutex_t mutex;
} linkedlist;

void push(linkedlist * llist, tuple t);
tuple * search_by_id(node * head, int id);

#endif