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

int verif(uint8_t h[static 6], char *h_attendu){
    char h2[12];
    snprintf(h2, 12, "%02X%02X%02X%02X%02X%02X", h[0], h[1], h[2], h[3], h[4], h[5]);
    printf("\nh2 : %s\n", h2);
    printf("h_attendu : %s\n", h_attendu);
    return strcmp(h2, h_attendu);
}

void convert(char key[48], uint8_t res[6]){
    for (int i = 0; i < 6; i++) {
        res[i] = 0;
        for (int j = 0; j < 8; j++) {
            res[i] += key[i*8+j] << (7-j);
        }
    }
}

int keyrec(uint64_t blen,const uint64_t msg[blen], char *h_attendu){
    int tries = 0;
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
                                tries++;
                                printf("Tries : %d\n", tries);
                                if (verif(h, h_attendu)==0) {
                                    printf("Key found : ");
                                    for (int i = 0; i < 48; i++) {
                                        printf("%d", key[i]);
                                    }
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