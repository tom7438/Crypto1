#include "keyrec.h"

char[48] reset_key(){
    char key[48];
    for (int i = 0; i < 48; i++) {
        key[i] = 0;
    }
    return key;
}

char[48] set_to_one(char key [48], int i){
    key[i] = 1;
    return key;
}

int keyrec(uint64_t blen,const uint64_t msg[blen]){
    char key[48];
    key = reset_key();
    for (int i = 0; i < 42; i++) {
        key = set_to_one(key, i);
        for (int j = i+1; j < 43; j++) {
            key = set_to_one(key, j);
            for (int k = j+1; k < 44; k++) {
                key = set_to_one(key, k);
                for (int l = k+1; l < 45; l++) {
                    key = set_to_one(key, l);
                    for (int m = l+1; m < 46; m++) {
                        key = set_to_one(key, m);
                        for (int n = m+1; n < 47; n++) {
                            key = set_to_one(key, n);
                            for (int o = n+1; o < 48; o++) {
                                key = set_to_one(key, o);
                                smht48(key, blen, msg, h);
                                // verif, meme principe que print_hash (mais en utilisant sprintf pour concatener les valeurs de h)
                            }
                        }
                    }
                }
            }
        }
        
    }

}