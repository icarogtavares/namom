#include "linkedlist.h"

void push(node ** head, int val) {
    node * new_node;
    new_node = malloc(sizeof(node));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

void clear_list(node ** head) {
    node * next_node = NULL;
    
    if (*head == NULL) {
        return -1;
    }

    do {
        next_node = (*head)->next;
        free(*head);
        *head = next_node;
    } while ( (*head) != null );
}