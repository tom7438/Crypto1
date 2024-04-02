//
// Created by tom on 13/03/24.
//
#include <stdio.h>

#include "ht48.h"
#include "smht48.h"
#include "keyrec.h"
#include "ColSearch.h"

int main(int argc, char **argv) {
    //smht48_test();
    //uint8_t m[6] = {9, 8, 7, 6, 5, 4};
    //uint8_t blen = sizeof(m);

    //keyrec(blen, m);

    ColSearch();



    // Calcule le hash de m1="D14B0A00000000000000000000000000"
    uint8_t m1[16] = {0xD1, 0x4B, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,};
    uint8_t h1[6] = {IVB0, IVB1, IVB2, IVB3, IVB4, IVB5};

    // Calcule le hash de m2="218F3E00000000000000000000000000"
    uint8_t m2[16] = {0x21, 0x8F, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,};
    uint8_t h2[6] = {IVB0, IVB1, IVB2, IVB3, IVB4, IVB5};

    tcz48_dm(m1, h1);
    printf("Hash de m1 : ");
    printhash(h1);

    printf("\n");
    printf("Hash de m2 : ");
    tcz48_dm(m2, h2);
    printhash(h2);
    printf("\n");







    return 0;
}