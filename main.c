//
// Created by tom on 13/03/24.
//
#include <stdio.h>

#include "ht48.h"
#include "smht48.h"
#include "keyrec.h"

int main(int argc, char **argv) {
    //smht48_test();
    uint8_t m[6] = {9, 8, 7, 6, 5, 4};
    uint8_t blen = sizeof(m);

    keyrec(blen, m);
    return 0;
}