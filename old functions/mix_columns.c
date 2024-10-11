#include <stdio.h>
#include "AES_functions.h"
//#include "x_times.c"

u_int8_t Multiply(u_int8_t a, u_int8_t b) {
    u_int8_t result = 0;
    u_int8_t carry = 0;
    for (int i = 0; i < 8; i++) {
        if (b & 1) {
            result = result ^ a;
        }
        b = b >> 1;
        carry = a & 0b10000000;
        a = a << 1; 
        if (carry) {
            a = a ^ 0x1b;
        }
    }
    return result;
}

void MixColumns(u_int8_t buffer[4][4]) {
    u_int8_t tmp[4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j<4 ; j++) { 
            tmp[j] = buffer[j][i];
        }
        buffer[0][i] = (XTimes(tmp[0])) ^ (Multiply(tmp[1], 0x3)) ^ tmp[2] ^ tmp[3];
        buffer[1][i] = tmp[0] ^ (XTimes(tmp[1])) ^ (Multiply(tmp[2], 0x3)) ^ tmp[3];
        buffer[2][i] = tmp[0] ^ tmp[1] ^ (XTimes(tmp[2])) ^ (Multiply(tmp[3], 0x3));
        buffer[3][i] = (Multiply(tmp[0], 0x3)) ^ tmp[1] ^ tmp[2] ^ (XTimes(tmp[3]));
    }
}