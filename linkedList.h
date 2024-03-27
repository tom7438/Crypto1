#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdint.h>

/**
 * @brief Macro for the size of the hash table
 */
#define SIZE 1 << 24

/**
 * @struct hash_table
 * @brief Hash table structure
 */
typedef struct hash_table_s {
    uint8_t h[6]; /**< Hash */
    uint8_t m[16]; /**< Message */
} hash_table_t;

typedef struct noeud {
    hash_table_t* data;
    struct noeud *next;
} Noeud;

typedef struct linkedList {
    Noeud *head;
} LinkedList;

LinkedList *createLinkedList();
hash_table_t *addNode(LinkedList *list, hash_table_t *data);
hash_table_t *searchNode(LinkedList *list, uint32_t hash[6]);

#endif
