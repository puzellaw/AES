#include "AES_functions.h"
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>


void AddRoundKey(u_int8_t state[4][4], u_int8_t roundKey[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = state[j][i]^roundKey[i][j];
        }
    }
}

void AES_128(u_int8_t input[4][4],  u_int8_t key[]) {
    u_int8_t buffer[44][4];
    KeyExpansion(buffer, key, 4, 10);
    Cipher(input, 10, buffer);
}

void AES_192(u_int8_t input[4][4],  u_int8_t key[]) {
    u_int8_t buffer[52][4];
    KeyExpansion(buffer, key, 6, 12);
    Cipher(input, 12, buffer);
}

void AES_256(u_int8_t input[4][4],  u_int8_t key[]) {
    u_int8_t buffer[60][4];
    KeyExpansion(buffer, key, 8, 14);
    Cipher(input, 14, buffer);
}

void Cipher(u_int8_t buffer[][4], int Nr, u_int8_t words[][4]) {
    u_int8_t wordSlice[4][4];
    for (int iter = 0; iter < 4; iter++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                wordSlice[iter][iter2] = words[iter][iter2];
            }
            
        }
    AddRoundKey(buffer, wordSlice);
    for (int round = 1; round <= Nr-1; round++)
    {
        for (int iter1 = 0; iter1 < 4; iter1++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                buffer[iter1][iter2] = SBox(buffer[iter1][iter2]);
            }
        }
        ShiftRows(buffer);
        MixColumns(buffer);
        for (int iter = 0; iter < 4; iter++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                wordSlice[iter][iter2] = words[4*round + iter][iter2];
            }
        }
        AddRoundKey(buffer, wordSlice);
    }
    for (int iter1 = 0; iter1 < 4; iter1++)
    {
        for (int iter2 = 0; iter2 < 4; iter2++)
        {
            buffer[iter1][iter2] = SBox(buffer[iter1][iter2]);
        } 
    }
    ShiftRows(buffer);
    for (int iter = 0; iter < 4; iter++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                wordSlice[iter][iter2] = words[4*Nr+ iter][iter2];
            }
            
        }
    AddRoundKey(buffer, wordSlice);
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


//Buffer in column major order
void KeyExpansion(u_int8_t buffer[][4], u_int8_t key[], int Nk, int Nr) {
    int i = 0;
    // TODO add Nk to the args needed for the function probably
    while (i <= Nk-1)
    {
        for (int iter = 0; iter < 4; iter++)
        {
            buffer[i][iter] = key[4*i + iter];
        }
        i++;
    }
    while (i <= 4*Nr + 3) {
        u_int8_t temp[4];
        for (int iter = 0; iter < 4; iter++)
        {
            temp[iter] = buffer[i-1][iter];
        }
        if(i % Nk == 0) {
            RotWord(temp);
            SubWord(temp);
            u_int8_t rCon[4];
            Rcon(rCon, (i/Nk));
            for (int iter = 0; iter < 4; iter++)
            {
                temp[iter] = temp[iter]^rCon[iter];
            }
        }
        else if (Nk > 6 && i % Nk == 4) {
            SubWord(temp);
        }
        for (int iter = 0; iter < 4; iter++)
        {
            buffer[i][iter] = buffer[i-Nk][iter]^temp[iter];
            
        }
        i++;
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

void RotWord(u_int8_t vec[4]) {
    u_int8_t first = vec[3];
    u_int8_t second = vec[2];
    for(int i = 2; i > 0; i--) {
        vec[i] = first;
        first = second;
        second = vec[i-1];
    }
    vec[0] = first;
    vec[3] = second;
}

u_int8_t SBox(u_int8_t a) {
    u_int8_t sbox[16][16] = 
    {{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

    return sbox[a/16][a%16];
}

void ShiftRows(u_int8_t buffer[][4]) {
    u_int8_t temp = buffer[1][3];
    buffer[1][3] = buffer[1][0];
    buffer[1][0] = buffer[1][1];
    buffer[1][1] = buffer[1][2];
    buffer[1][2] = temp;

    temp = buffer[2][0];
    u_int8_t temp2 = buffer[2][1];
    buffer[2][0] = buffer[2][2];
    buffer[2][1] = buffer[2][3];
    buffer[2][2] = temp;
    buffer[2][3] = temp2;

    temp = buffer[3][0];
    temp2 = buffer[3][1];
    buffer[3][0] = buffer[3][3];
    buffer[3][1] = temp;
    temp = buffer[3][2];
    buffer[3][2] = temp2;
    buffer[3][3] = temp;
}

void SubWord(u_int8_t vec[4]) {
    for (int i = 0; i < 4; i++)
    {
        vec[i] = SBox(vec[i]);
    }
}

u_int8_t XTimes(u_int8_t b){
    if ((int)(b & 0b10000000) == (int)(0b10000000)) {
        b = (b<<1)^0b00011011;
    }
    else {
        b = b<<1;
    }
    return b;
}