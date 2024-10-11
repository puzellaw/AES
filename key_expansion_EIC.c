#include "AES_functions.h"


void KeyExpansionEIC(u_int8_t buffer[][4], u_int8_t key[], int Nk, int Nr) {
    int i = 0; 
    
    while (i <= (Nk - 1)) {

    }
}

void InvMixColumns(u_int8_t buffer[4][4]) {
    u_int8_t tmp[4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j<4 ; j++) { 
            tmp[j] = buffer[j][i];
        }
        buffer[0][i] = (Multiply(tmp[0], 0x0e)) ^ (Multiply(tmp[1], 0x0b)) ^ (Multiply(tmp[2], 0x0d)) ^ (Multiply(tmp[3], 0x09));
        buffer[1][i] = (Multiply(tmp[0], 0x09)) ^ (Multiply(tmp[1], 0x0e)) ^ (Multiply(tmp[2], 0x0b)) ^ (Multiply(tmp[3], 0x0d));
        buffer[2][i] = (Multiply(tmp[0], 0x0d)) ^ (Multiply(tmp[1], 0x09)) ^ (Multiply(tmp[2], 0x0e)) ^ (Multiply(tmp[3], 0x0b));
        buffer[3][i] = (Multiply(tmp[0], 0x0b)) ^ (Multiply(tmp[1], 0x0d)) ^ (Multiply(tmp[2], 0x09)) ^ (Multiply(tmp[3], 0x0e));
    }
}