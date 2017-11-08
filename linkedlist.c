#include "linkedlist.h"

void push(bucket * b, int val) {
    if(b->head == NULL) {
        b->head = malloc(sizeof(node));
        b->head->val = val;
        b->head->next = NULL;
        return;
    }
    
    node * new_node;
    new_node = malloc(sizeof(node));

    new_node->val = val;
    new_node->next = b->head;
    b->head = new_node;
}

// void clear_list(node ** head) {
//     node * next_node = NULL;
    
//     if (*head == NULL) {
//         printf("Bucket is empty.\n");
//         return;
//     }

//     do {
//         next_node = (*head)->next;
//         free(*head);
//         *head = next_node;
//     } while ( (*head) != NULL );
// }