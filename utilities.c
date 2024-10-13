#include"AES_functions.h"
#include<stdio.h>

u_int8_t XTimes(u_int8_t b){
    if ((int)(b & 0b10000000) == (int)(0b10000000)) {
        b = (b<<1)^0b00011011;
    }
    else {
        b = b<<1;
    }
    return b;
}

void AddRoundKey(u_int8_t state[4][4], u_int8_t roundKey[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = state[j][i]^roundKey[i][j];
        }
    }
}

void Rcon(u_int8_t buffer[4], int j) {
    u_int8_t roundConstants[][4] = {{0x01, 0x00, 0x00, 0x00},
    {0x02, 0x00, 0x00, 0x00},{0x04, 0x00, 0x00, 0x00},{0x08, 0x00, 0x00, 0x00},
    {0x10, 0x00, 0x00, 0x00},{0x20, 0x00, 0x00, 0x00},{0x40, 0x00, 0x00, 0x00},
    {0x80, 0x00, 0x00, 0x00},{0x1b, 0x00, 0x00, 0x00},{0x36, 0x00, 0x00, 0x00}};

    for (int iter = 0; iter < 4; iter++)
    {
        buffer[iter] = roundConstants[j-1][iter];
    }
}

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

void SubWord(u_int8_t vec[4]) {
    for (int i = 0; i < 4; i++)
    {
        vec[i] = SBox(vec[i]);
    }
}