#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ht48.h"
#include "smht48.h"

// Renvoie le nb de clés trouvées
int keyrec(uint64_t blen,const uint64_t msg[blen], uint8_t h_attendu[static 6]  );
