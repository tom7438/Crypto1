#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ht48.h"
#include "smht48.h"

// Set tous les bits à 0
void reset_key(char key[48]);

// Set le bit i à 1 (commence à 0)
void set_to_one(char key [48], int i);

// Set le bit i à 0 (commence à 0)
void set_to_zero(char key [48], int i);

// Convertit la representation de la clé en char (binaire) en uint8_t[6] (hexadécimal)
void charToUint8(char key[48], uint8_t key8[6]);

// Compare les hash
int verif(uint8_t h[static 6], char *h_attendu);

// Renvoie le nb de clés trouvées
int keyrec(uint64_t blen,const uint8_t msg[blen]);
