#include"AES_functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void InvShiftRows(u_int8_t buffer[4][4]) {
    u_int8_t temp = buffer[1][2];
    buffer[1][2] = buffer[1][1];
    buffer[1][1] = buffer[1][0];
    buffer[1][0] = buffer[1][3];
    buffer[1][3] = temp;

    temp = buffer[2][0];
    u_int8_t temp2 = buffer[2][1];
    buffer[2][0] = buffer[2][2];
    buffer[2][1] = buffer[2][3];
    buffer[2][2] = temp;
    buffer[2][3] = temp2;

    temp = buffer[3][0];
    buffer[3][0] = buffer[3][1];
    buffer[3][1] = buffer[3][2];
    buffer[3][2] = buffer[3][3];
    buffer[3][3] = temp;
}