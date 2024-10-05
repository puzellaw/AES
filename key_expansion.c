#include"AES_functions.h"
#include<stdio.h>

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
void KeyExpansion(u_int8_t buffer[][4], u_int8_t key[]) {
    int i = 0;
    // TODO add Nk to the args needed for the function probably
    int Nk = 4;
    int Nr = 10;
    u_int8_t words[4*Nr+1][4];
    while (i <= Nk-1)
    {
        for (int iter = 0; iter < 4; iter++)
        {
            words[i][iter] = key[4*i + iter];
        }
        i++;
    }
    while (i <= 4*Nr + 3) {
        u_int8_t temp[4];
        for (int iter = 0; iter < 4; iter++)
        {
            temp[iter] = words[i-1][iter];
        }
        if(i % Nk == 0) {
            RotWord(temp);
            SubWord(temp); //xor Rcon[i/Nk] but change def of SubWord and RotWord to return
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
            words[i][iter] = words[i-Nk][iter]^temp[iter];
        }
        i++;
    }
    for (int iter = 0; iter < 4*Nr+1; iter++)
    {
        for (int iter2 = 0; iter2 < 4; iter2++)
        {
            buffer[iter][iter2] = words[iter][iter2];
        } 
    }
}