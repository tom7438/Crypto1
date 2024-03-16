#include "keyrec.h"

void reset_key(char key [48]){
    for (int i = 0; i < 48; i++) {
        key[i] = 0;
    }
}

void set_to_one(char key [48], int i){
    key[i] = 1;
}

void set_to_zero(char key [48], int i){
    key[i] = 0;
}

int verif(uint8_t h[static 6], uint8_t h_attendu[static 6]){
    for (int i = 0; i < 6; i++) {
        if (h[i] != h_attendu[i]) {
            return 0;
        }
    }
    return 1;
}

void convert(char key[48], uint8_t res[6]){
    for (int i = 0; i < 6; i++) {
        res[i] = 0;
        for (int j = 0; j < 8; j++) {
            res[i] += key[i*8+j] << (7-j);
        }
    }
}

int keyrec(uint64_t blen,const uint64_t msg[blen], uint8_t h_attendu[static 6]){
    char key[48];
    uint8_t c[6];
    reset_key(key);
    uint8_t h[6];
    for (int i = 0; i < 42; i++) {
        set_to_one(key, i);
        for (int j = i+1; j < 43; j++) {
            set_to_one(key, j);
            for (int k = j+1; k < 44; k++) {
                set_to_one(key, k);
                for (int l = k+1; l < 45; l++) {
                    set_to_one(key, l);
                    for (int m = l+1; m < 46; m++) {
                        set_to_one(key, m);
                        for (int n = m+1; n < 47; n++) {
                            set_to_one(key, n);
                            for (int o = n+1; o < 48; o++) {
                                set_to_one(key, o);
                                convert(key, c);
                                smht48(c, blen, (uint8_t*)msg, h);
                                verif (h, h_attendu);
                                if (verif(h, h_attendu)) {
                                    return 1;
                                }
                                set_to_zero(key, o);
                            }
                            set_to_zero(key, n);
                        }
                        set_to_zero(key, m);
                    }
                    set_to_zero(key, l);
                }
                set_to_zero(key, k);
            }
            set_to_zero(key, j);
        }
        set_to_zero(key, i);
        
    }
    return 0;

}