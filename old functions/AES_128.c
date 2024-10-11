#include"AES_functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void AES_128(u_int8_t input[4][4],  u_int8_t key[]) {
    u_int8_t buffer[44][4];
    KeyExpansion(buffer, key, 4, 10);
    Cipher(input, 10, buffer);
}