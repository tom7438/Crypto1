#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ht48.h"
#include "smht48.h"
#include <string.h>

// Renvoie le nb de clés trouvées
int keyrec(uint64_t blen,const uint64_t msg[blen],char *h_attendu);
