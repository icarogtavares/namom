#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
    int val;
    struct node * next;
} node;

void push(node ** head, int val)
void clear_list(node ** head);