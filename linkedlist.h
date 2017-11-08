#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int val;
    struct node * next;
} node;

typedef struct bucket {
    node * head;
} bucket;

void push(bucket * b, int val);
// void clear_list(node ** head);