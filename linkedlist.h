#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include "datatypes.h"

typedef struct node {
    struct tuple * t;
    struct node * next;
} node;

typedef struct linkedlist {
    node * head;
} linkedlist;

void push(linkedlist * llist, tuple * t);
tuple* search_by_id(node * head, int id);
tuple* remove_by_id(node ** head, int id);
tuple* pop(node ** head);
// void clear_list(node ** head);

#endif