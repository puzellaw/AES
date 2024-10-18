#include "AES_functions.h"
#include"utilities.c"

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
// void KeyExpansionEIC(u_int8_t buffer[][4], u_int8_t key[], int Nk, int Nr) {
//     int i = 0;
//     u_int8_t wBuff[4 * (Nr + 1)][4];
//     while (i <= (Nk - 1)) {
//         for (int iter = 0; iter < 4; iter++) {
//             wBuff[i][iter] = key[4*i + iter];
//             buffer[i][iter] = wBuff[i][iter];
//         }
//         i++; 
//     }
//     while (i <= (4 * Nr + 3)) {
//         u_int8_t temp[4];
//         for (int iter = 0; iter < 4; iter++) {
//             temp[iter] = wBuff[i-1][iter];
//         }
//         if (i%Nk == 0)
//         {
//             RotWord(temp);
//             SubWord(temp);
//             u_int8_t rCon[4];
//             Rcon(rCon, (i/Nk));
//             for (int iter = 0; iter < 4; iter++)
//             {
//                 temp[iter] = temp[iter]^rCon[iter];
//             }
//         }
//         else if (Nk > 6 && i%Nk == 4) {
//             SubWord(temp);            
//         }
//         for (int iter = 0; iter < 4; iter++)
//         {
//             wBuff[i][iter] = wBuff[i-Nk][iter]^temp[iter];
//             buffer[i][iter] = wBuff[i][iter];
//         }
//         i++;
//     }
    
//     for (int iter = 1; iter <= Nr -1; iter++)
//     {
//         i = 4*iter;
//         u_int8_t temp[4][4];
//         for (int iter1 = 0; iter1 < 4; iter1++)
//         {
//             for (int iter2 = 0; iter2 < 4; iter2++)
//             {
//                 temp[iter1][iter2] = buffer[i + iter1][iter2];
//             }
//         }
//         InvMixColumns(temp);
//         for (int iter1 = 0; iter1 < 4; iter1++)
//         {
//             for (int iter2 = 0; iter2 < 4; iter2++)
//             {
//                 buffer[i+ iter1][iter2] = temp[iter1][iter2];
//             }
//         }
//     }
// }

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