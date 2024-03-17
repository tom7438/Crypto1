//
// Created by tom on 13/03/24.
//
#include <stdio.h>

#include "ht48.h"
#include "smht48.h"
#include "keyrec.h"

int main(int argc, char **argv) {
    smht48_test();
    char* h_attendu = "7D1DEFA0B8AD";
    uint64_t blen = 6;
    uint64_t msg[6] = {9, 8, 7, 6, 5, 4};
    keyrec(blen, msg, h_attendu);
    return 0;
}