#include "linkedlist.h"

void push(linkedlist * llist, tuple t) {
    if(llist->head == NULL) {
        llist->head = malloc(sizeof(node));
        llist->head->t = t;
        llist->head->next = NULL;
        return;
    }
    
    node * new_node;
    new_node = malloc(sizeof(node));

    new_node->t = t;
    new_node->next = llist->head;
    llist->head = new_node;
}

tuple * search_by_id(node * head, int id) {
    node * current = head;
    while(current != NULL) {
        if(current->t.id == id) {
            return &current->t;
        }
        current = current->next;
    }
    return NULL;
}