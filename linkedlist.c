#include "linkedlist.h"

void push(linkedlist_t * llist, tuple_t t) {
    if(llist->head == NULL) {
        llist->head = malloc(sizeof(node_t));
        llist->head->t = t;
        llist->head->next = NULL;
        return;
    }
    
    node_t * new_node;
    new_node = malloc(sizeof(node_t));

    new_node->t = t;
    new_node->next = llist->head;
    llist->head = new_node;
}

tuple_t * search_by_id(node_t * head, int id) {
    node_t * current = head;
    while(current != NULL) {
        if(current->t.id == id) {
            return &current->t;
        }
        current = current->next;
    }
    return NULL;
}