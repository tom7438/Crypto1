#include "smht48.h"


void smht48(const uint8_t k[static 6], uint64_t blen, const uint8_t m[blen], uint8_t h[static 6]) {
    uint8_t *mk = (uint8_t *) malloc(blen + 6);
    for (uint64_t i = 0; i < blen; i++) {
        mk[i] = m[i];
    }

    for (uint64_t i = 0; i < 6; i++) {
        mk[blen + i] = k[i];
    }

    ht48(blen + 6, mk, h);
    free(mk);
}

void smht48_test() {
    uint8_t h1[6];
    uint8_t h2[6];
    uint8_t m[6] = {9, 8, 7, 6, 5, 4};
    uint8_t key1[6] = {0, 1, 2, 3, 4, 5};
    uint8_t key2[6] = {0xE4, 0x16, 0x9F, 0x12, 0xD3, 0xBA};
    uint64_t blen = sizeof(m);

    printf("blen = %llu\n", blen);

    smht48(key1, blen, m, h1);
    printhash(h1);
    printf(" (Attendue : EE75794547B8)\n");

    smht48(key2, blen, m, h2);
    printhash(h2);
    printf(" (Attendue : 5F265B72B5EC)\n");
}