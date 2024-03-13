#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ht48.h"

#ifndef SMHT48_H
#define SMHT48_H

void smht48(const uint8_t k[static 6], uint64_t blen, const uint8_t m[blen], uint8_t h[static 6]);

#endif