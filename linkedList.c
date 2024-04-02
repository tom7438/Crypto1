
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList *createLinkedList() {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

hash_table_t *addNode(LinkedList *list, hash_table_t *data) {
    Noeud *newNode = (Noeud *) malloc(sizeof(Noeud));
    newNode->data = data;

    Noeud *current = list->head;
    while (current != NULL) {
        for (int i = 0; i < 6; i++) {
            if (current->data->h[i] != data->h[i]) {
                break;
            }
            if (i == 5) {
                printf("Hash trouvé\n");
                return current->data;
            }
        }
        current = current->next;
    }
    newNode->next = list->head;
    list->head = newNode;
    return NULL;
}