#include"AES_functions.h"
#include<stdio.h>

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
        SBox(buffer);
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
    SBox(buffer);
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