#include "smht48.h"


void smht48(const uint8_t k[static 6], uint64_t blen, const uint8_t m[blen], uint8_t h[static 6]) {
    uint8_t *mk = (uint8_t *) malloc(blen * 2);
    for (uint64_t i = 0; i < blen; i++) {
        mk[i] = m[i];
    }

    for (uint64_t i = 0; i < blen; i++) {
        mk[blen + i] = k[i];
    }

    ht48(blen, mk, h);
    free(mk);
}