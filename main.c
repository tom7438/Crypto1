//
// Created by tom on 13/03/24.
//
#include <stdio.h>

#include "ht48.h"

int main(int argc, char **argv) {
    uint8_t h1[6];
    //uint8_t h2[6];
    uint8_t m1[6] = {9, 8, 7, 6, 5 , 4};
    uint32_t m2[6] = {0xE4, 0x16, 0x9F, 0x12, 0xD3, 0xBA};
    uint8_t key[6] = {0, 1, 2, 3, 4, 5};
    uint64_t blen1 = sizeof(m1);
    uint64_t blen2 = sizeof(m2);

    printf("blen1 = %lu\n", blen1);
    printf("blen2 = %lu\n", blen2);

    smht48(key, blen1, m1, h1);
    printhash(h1);
    printf("\n");

    return 0;
}