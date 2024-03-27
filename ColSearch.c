#include "ColSearch.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "ht48.h"
#include <pthread.h>
#include "linkedList.h"

LinkedList **init_ll_tab(uint32_t size) {
    LinkedList **linkedList = (LinkedList **) malloc(sizeof(LinkedList*) * size);
    for (int i = 0; i < size; i++) {
        linkedList[i] = createLinkedList();
    }
    return linkedList;
}

int verif2hash(uint8_t h1[static 6], uint8_t h2[static 6]) {
    for (int i = 0; i < 6; i++) {
        if (h1[i] != h2[i]) {
            return -1;
        }
    }
    return 0;
}

int verif2message(uint8_t m1[static 16], uint8_t m2[static 16]) {
    for (int i = 0; i < 16; i++) {
        if (m1[i] != m2[i]) {
            return -1;
        }
    }
    return 0;
}

uint32_t convertHash(uint8_t h[static 3]) {
    return (h[0] << 16) | (h[1] << 8) | h[2];
}


hash_table_t *insert_tuple(LinkedList** ll, uint8_t h[static 6], uint8_t m[static 16], uint32_t size) {
    uint8_t new_hash[3] = {h[4], h[5], h[6]};
    hash_table_t *new_ht = malloc(sizeof(hash_table_t));
    for (int i = 0; i < 6; i++) {
        new_ht->h[i] = h[i];
    }
    for (int i = 0; i < 16; i++) {
        new_ht->m[i] = m[i];
    }

    hash_table_t *res = addNode(ll[convertHash(new_hash)], new_ht);
    if (res != NULL) {
        printf("Collision found\n");
        return res;
    }
    return NULL;
}

void incr(uint8_t *m) {
    for (int i = 15; i >= 0; i--) {
        if (m[i] == 0xFF) {
            m[i] = 0;
        } else {
            m[i]++;
            break;
        }
    }
}

void decr(uint8_t *m) {
    for (int i = 15; i >= 0; i--) {
        if (m[i] == 0) {
            m[i] = 0xFF;
        } else {
            m[i]--;
            break;
        }
    }
}

int binToHex(uint8_t *m, char *hex) {
    for (int i = 0; i < 16; i++) {
        sprintf(hex + i * 2, "%02X", m[i]);
    }
    return 0;
}

void opDiv(uint8_t m[static 16], uint8_t res[static 16], int nb) {
    for(int i = 0; i < 16; i++) {
        res[i] = m[i];
    }
    for (int i = 0; i < nb; i++) {
        // Décalage à droite de 1 à chaque fois en commencant par la fin
        for (int j = 15; j > 0; j--) {
            res[j] = res[j] >> 1;
            // Si le bit de poids faible de l'octet suivant est à 1, on met le bit de poids fort de l'octet actuel à 1
            if (res[j - 1] & 1) {
                res[j] |= 0x80;
            }
        }
        res[0] = res[0] >> 1;
    }
}

void opAdd(uint8_t m1[static 16], uint8_t m2[static 16], uint8_t res[static 16]) {
    uint8_t carry = 0;
    for (int i = 15; i >= 0; i--) {
        res[i] = m1[i] + m2[i] + carry;
        if (res[i] < m1[i] || res[i] < m2[i]) {
            carry = 1;
        } else {
            carry = 0;
        }
    }
}

void *searchCollision(void *arg) {
    ThreadData_t *data = (ThreadData_t *) arg;
    uint8_t h[6];
    uint8_t m1[16];
    LinkedList **LlTab = data->LlTab;
    pthread_mutex_t *mutex = data->mutex;
    uint8_t fin[16];

    hash_table_t *res;

    for (int i = 0; i < 16; i++) {
        m1[i] = data->m[i];
        fin[i] = data->fin[i];
    }

    do {
        // Remettre le h à IV
        h[0] = IVB0;
        h[1] = IVB1;
        h[2] = IVB2;
        h[3] = IVB3;
        h[4] = IVB4;
        h[5] = IVB5;

        /*
        pthread_mutex_lock(mutex);
        fprintf(stdout, "Thread %d\n", (int) pthread_self());
        fprintf(stdout, "Message: ");
        for (int i = 0; i < 16; i++) {
            fprintf(stdout, "%02X", m1[i]);
        }
        fprintf(stdout, "\n");
        pthread_mutex_unlock(mutex);
         */

        tcz48_dm(m1, h);

        pthread_mutex_lock(mutex);
        res = insert_tuple(LlTab, h, m1, SIZE);
        pthread_mutex_unlock(mutex);

        if (res != NULL) {
            printf("Collision found\n");
            getchar();
            break;
        }

        // Incrementer m1
        incr(m1);
    } while (verif2message(m1, fin) != 0);

    // Afficher les 2 messages ayant le même hash
    if (res != NULL) {
        printf("Message 1: ");
        for (int i = 0; i < 16; i++) {
            printf("%02X", res->m[i]);
        }
        printf("\n");
        printf("Message 2: ");
        for (int i = 0; i < 16; i++) {
            printf("%02X", m1[i]);
        }
        printf("\n");
    }

    pthread_exit(NULL);
}

int ColSearch() {
    uint8_t m1[16];
    uint8_t fin[16];
    uint8_t currentFin[16];

    for (int i = 0; i < 16; i++) {
        m1[i] = 0;
    }

    // Max
    uint8_t max[16];
    for (int i = 0; i < 16; i++) {
        max[i] = 0xFF;
    }

    opDiv(max, fin, THREADS/2);
    fprintf(stdout, "Fin: ");
    for (int j = 0; j < 16; j++) {
        fprintf(stdout, "%02X", fin[j]);
        currentFin[j] = fin[j];
    }
    fprintf(stdout, "\n");
    getchar();

    // Initialiser la table de hash
    LinkedList **LlTab = init_ll_tab(SIZE);


    pthread_t threads[THREADS];
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);


    ThreadData_t data[THREADS];
    for (int i = 0; i < THREADS; i++) {
        data[i].LlTab = LlTab;
        for (int j = 0; j < 16; j++) {
            data[i].m[j] = m1[j];
        }
        for (int j = 0; j < 16; j++) {
            data[i].fin[j] = currentFin[j];
        }
        data[i].mutex = &mutex;
        pthread_create(&threads[i], NULL, searchCollision, &data[i]);
        incr(currentFin);
        for (int j = 0; j < 16; j++) {
            m1[j] = currentFin[j];
        }
        opAdd(m1, fin, currentFin);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    free(LlTab);
    return 0;
}
