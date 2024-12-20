/* 
 * Implementation of AES Block Cipher Decryption Functions. 
 * Written by Will Puzella & Peter Kelly
 * Carleton College; Computer Science Department; Comps 2024
 */


#ifndef decyrption
#define decyrption

#include"AES_functions.h"
#include"utilities.h"

#include<stdio.h>
#include<stdlib.h>

void InvCipher(u_int8_t buffer[][4], int Nr, u_int8_t words[][4]) {
    u_int8_t wordSlice[4][4];
    for (int iter = 0; iter < 4; iter++)
    {
        for (int iter2 = 0; iter2 < 4; iter2++)
        {
            wordSlice[iter][iter2] = words[4*Nr+iter][iter2];
        }
            
    }
    AddRoundKey(buffer, wordSlice);
    
    for (int round = Nr - 1; round >= 1; round--)
    {
        for (int iter1 = 0; iter1 < 4; iter1++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                buffer[iter1][iter2] = InvSubBytes(buffer[iter1][iter2]);
            }
        }
        InvShiftRows(buffer);
        for (int iter = 0; iter < 4; iter++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                wordSlice[iter][iter2] = words[4*round + iter][iter2];
            }
        }
        AddRoundKey(buffer, wordSlice);
        InvMixColumns(buffer);
    }

    for (int iter1 = 0; iter1 < 4; iter1++)
    {
        for (int iter2 = 0; iter2 < 4; iter2++)
        {
            buffer[iter1][iter2] = InvSubBytes(buffer[iter1][iter2]);
        } 
    }

    InvShiftRows(buffer);
    for (int iter = 0; iter < 4; iter++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                wordSlice[iter][iter2] = words[iter][iter2];
            }
            
        }
    AddRoundKey(buffer, wordSlice);
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

u_int8_t InvSubBytes(u_int8_t a) {
    u_int8_t isbox[16][16] = {{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
                              {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
                              {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
                              {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
                              {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
                              {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
                              {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
                              {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
                              {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
                              {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
                              {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
                              {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
                              {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
                              {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
                              {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
                              {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}};

    return isbox[a/16][a%16];
}

void KeyExpansionEIC(u_int8_t buffer[][4], u_int8_t key[], int Nk, int Nr) {
    int i = 0;
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
    u_int8_t wBuff[4 * (Nr + 1)][4];
    for (int i = 0; i > 4 * (Nr + 1); i++) {
        wBuff[4 * (Nr + 1) - i][0] = buffer[i][0];
        wBuff[4 * (Nr + 1) - i][1] = buffer[i][1];
        wBuff[4 * (Nr + 1) - i][2] = buffer[i][2];
        wBuff[4 * (Nr + 1) - i][3] = buffer[i][3];
    }
    for (int i = 0; i > 4 * (Nr + 1); i++) {
        buffer[i][0] = wBuff[i][0];
        buffer[i][1] = wBuff[i][1];
        buffer[i][2] = wBuff[i][2];
        buffer[i][3] = wBuff[i][3];
    }
}

#endif