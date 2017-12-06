#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "main.h"
#include "datatypes.h"

typedef struct node {
    struct tuple t;
    struct node * next;
} node_t;

typedef struct linkedlist {
    struct node * head;
    pthread_mutex_t mutex;
} linkedlist_t;

void push(linkedlist_t * llist, tuple_t t);
tuple_t * search_by_id(node_t * head, int id);

#endif