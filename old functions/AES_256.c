#include"AES_functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void AES_256(u_int8_t input[4][4],  u_int8_t key[]) {
    u_int8_t buffer[60][4];
    KeyExpansion(buffer, key, 8, 14);
    Cipher(input, 14, buffer);
}