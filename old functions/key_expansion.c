#include"AES_functions.h"
#include<stdio.h>
#include<stdlib.h>

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