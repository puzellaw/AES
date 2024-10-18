#include"AES_functions.h"


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
    printf("AFTER ADD ROUND KEY\n");
    for (int iter = 0; iter < 4; iter++)
    {
        for (int iter2 = 0; iter2 < 4; iter2++)
        {
            printf("%02x ", buffer[iter][iter2]);
        }
        printf("\n");
    }
    
    for (int round = Nr - 1; round >= 1; round--)
    {
        for (int iter1 = 0; iter1 < 4; iter1++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                buffer[iter1][iter2] = InvSubBytes(buffer[iter1][iter2]);
            }
        }
        printf("AFTER ADD SubBytes\n");
        for (int iter = 0; iter < 4; iter++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                printf("%02x ", buffer[iter][iter2]);
            }
            printf("\n");
        }
        InvShiftRows(buffer);
        printf("AFTER SHIFT ROWS\n");
        for (int iter = 0; iter < 4; iter++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                printf("%02x ", buffer[iter][iter2]);
            }
            printf("\n");
        }
        for (int iter = 0; iter < 4; iter++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                wordSlice[iter][iter2] = words[4*round + iter][iter2];
            }
        }
        printf("ROUND KEY FOR THIS ROUND\n");
        for (int iter = 0; iter < 4; iter++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                printf("%02x ", wordSlice[iter][iter2]);
            }
            printf("\n");
        }
        AddRoundKey(buffer, wordSlice);
        printf("AFTER ADD ROUND KEY\n");
        for (int iter = 0; iter < 4; iter++)
        {
            for (int iter2 = 0; iter2 < 4; iter2++)
            {
                printf("%02x ", buffer[iter][iter2]);
            }
            printf("\n");
        }
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
