#include"AES_functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void AES_192(u_int8_t input[4][4],  u_int8_t key[]) {
    u_int8_t buffer[52][4];
    KeyExpansion(buffer, key, 6, 12);
    Cipher(input, 12, buffer);
}