#ifndef CRYPTO1_COLSEARCH_H
#define CRYPTO1_COLSEARCH_H

#include <stdint.h>
#include <pthread.h>
#include "linkedList.h"

/**
 * @brief Search for collisions in tcz48_dm function
 *
 * @return int 0 if successful, -1 otherwise
 */
int ColSearch();

/**
 * @brief Hash table initialization
 *
 * @param size Size of the hash table
 * @return struct hash_table* Pointer to the hash table
 */
LinkedList **init_ll_tab(uint32_t size);

/**
 * @brief Hash table insertion
 *
 * @param ht Hash table
 * @param h Hash
 * @param m Message
 * @param size Size of the hash table
 * @return int 0 if successful, 1 if the hash already exists, -2 if the hash table is full, -1 otherwise
 */
hash_table_t *insert_tuple(LinkedList* ll[SIZE], uint8_t h[static 6], uint8_t m[static 16], uint32_t size);

/**
 * @brief Compare two hashes
 * @param h1
 * @param h2
 * @return int 0 if the hashes are equal, -1 otherwise
 */
int verif2hash(uint8_t h1[static 6], uint8_t h2[static 6]);


/**
 * @brief Thread data structure
 * @struct ThreadData
 * @param m Message
 * @param ht Hash table
 * @param size Size of the hash table
 * @param fin Final message (after incrementation)
 */
typedef struct ThreadData_s {
    uint8_t m[16];
    LinkedList **LlTab;
    uint8_t fin[16];
    pthread_mutex_t *mutex;
} ThreadData_t;

/**
 * @brief Search for collisions in the hash table (threaded)
 * @param arg ThreadData_t structure
 * @return
 */
void *searchCollision(void *arg);

#define THREADS (1 << 7)

#endif //CRYPTO1_COLSEARCH_H
