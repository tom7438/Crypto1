#include <string.h>
#include "keyrec.h"

void reset_key(char key[48]){
    for (int i = 0; i < 48; i++) {
        key[i] = '0';
    }
}

void set_to_one(char key [48], int i){
    key[i] = '1';
}

void set_to_zero(char key [48], int i){
    key[i] = '0';
}

void charToUint8(char key[48], uint8_t key8[6]){
    // Convertit la representation de la clé en char (binaire) en uint8_t[6] (hexadécimal)
    for (int i = 0; i < 6; i++) {
        key8[i] = 0;
        for (int j = 0; j < 8; j++) {
            key8[i] = key8[i] << 1;
            key8[i] += key[i*8+j] - '0';
        }
    }
}

int verif(uint8_t h[6], char *h_attendu){
    uint8_t h2[6];
    //Convertit le hash attendu en uint8_t
    for (int i = 0; i < 6; i++) {
        h2[i] = 0;
        for (int j = 0; j < 2; j++) {
            h2[i] = h2[i] << 4;
            if(h_attendu[i*2+j] >= '0' && h_attendu[i*2+j] <= '9'){
                h2[i] += h_attendu[i*2+j] - '0';
            }else{
                h2[i] += h_attendu[i*2+j] - 'A' + 10;
            }
        }
    }
    //printf("\nh2 : %s\n", h2);
    //printf("h_attendu : %s\n", h_attendu);
    //Comparaison octet par octet
    for (int i = 0; i < 6; i++) {
        if(h2[i] != h[i]){
            return -1;
        }
    }
    fprintf(stderr, "h = %02X%02X%02X%02X%02X%02X\n", h[0], h[1], h[2], h[3], h[4], h[5]);
    fprintf(stderr, "h_attendu = %02X%02X%02X%02X%02X%02X\n", h2[0], h2[1], h2[2], h2[3], h2[4], h2[5]);
    return 0;
}

int keyrec(uint64_t blen,const uint8_t msg[blen]){
    char key[48];
    reset_key(key);
    uint8_t h[6];
    uint8_t key8[6];
    for (int i = 0; i < 42; i++) {
        if(i > 0)
            set_to_zero(key, i-1);
        set_to_one(key, i);
        for (int j = i+1; j < 43; j++) {
            if(j > i+1)
                set_to_zero(key, j-1);
            else
                set_to_zero(key, 42);
            set_to_one(key, j);
            for (int k = j+1; k < 44; k++) {
                if(k > j+1)
                    set_to_zero(key, k-1);
                else
                    set_to_zero(key, 43);
                set_to_one(key, k);
                for (int l = k+1; l < 45; l++) {
                    if(l > k+1)
                        set_to_zero(key, l-1);
                    else
                        set_to_zero(key, 44);
                    set_to_one(key, l);
                    for (int m = l+1; m < 46; m++) {
                        if(m > l+1)
                            set_to_zero(key, m-1);
                        else
                            set_to_zero(key, 45);
                        set_to_one(key, m);
                        for (int n = m+1; n < 47; n++) {
                            set_to_one(key, n);
                            for (int o = n+1; o < 48; o++) {
                                set_to_one(key, o);
                                //fprintf(stderr, "key = %s\n", key);
                                charToUint8(key, key8);
                                //fprintf(stderr, "key8 = %02X%02X%02X%02X%02X%02X\n", key8[0], key8[1], key8[2], key8[3], key8[4], key8[5]);
                                smht48(key8, blen, msg, h);
                                // verif, meme principe que print_hash (mais en utilisant sprintf pour concatener les valeurs de h)
                                int res = verif(h, "7D1DEFA0B8AD");
                                //fprintf(stderr, "res = %d\n", res);
                                if(res == 0){
                                    fprintf(stderr, "key8 = %02X%02X%02X%02X%02X%02X\n", key8[0], key8[1], key8[2], key8[3], key8[4], key8[5]);
                                    //return 1;
                                }
                                set_to_zero(key, o);
                            }
                            set_to_zero(key, n);
                            //getchar();
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