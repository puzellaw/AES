#include"AES_functions.h"
#include<stdio.h>

#define DEBUG 1

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
    if (DEBUG) {
        printf("FOR ADD ROUND KEY\n");
        for (int iter = 0; iter < 4; iter++)
            {
                for (int iter2 = 0; iter2 < 4; iter2++)
                {
                    printf("%02x ", buffer[iter][iter2]);
                }
                printf("\n");
                
            }
        printf("------------------\n");
    }
    for (int round = 1; round <= Nr-1; round++)
    {
        // SBox(buffer);
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