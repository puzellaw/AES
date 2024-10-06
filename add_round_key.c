#include "AES_functions.h"
#include<stdio.h>

void AddRoundKey(u_int8_t state[4][4], u_int32_t roundKey[4]) {
    u_int8_t partialRoundKey;
    u_int8_t shiftedMask;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            partialRoundKey = roundKey[i];
            shiftedMask = (partialRoundKey >> (j * 8)) & 0xff;
            state[i][j] = state [i][j] ^ shiftedMask;
        }
    }
}