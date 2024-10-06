#include"AES_functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


/*
    clang main.c sub_word.c sbox.c rot_word.c x_times.c key_expansion.c
*/

int main(void){

    // u_int8_t myChar = 0x7f;
    // printf("%02x\n", sbox(myChar));


    // u_int8_t vec[4] = {0x01, 0x02, 0x03, 0x04};
    // rot_word(vec);
    // for(int i = 0; i < 4; i++){
    //     printf("%x", vec[i]);
    // }
    // printf("\n");


    // u_int16_t byte = 0b00010000;
    // byte = x_times(byte);
    // printf("%02x\n", byte);

    // u_int8_t vec[4] = {0xa3, 0x4f, 0x85, 0xea};
    // SubWord(vec);
    // for (size_t i = 0; i < 4; i++)
    // {
    //     printf("%02x\n", vec[i]);
    // }
    
    u_int8_t key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    u_int8_t buffer[44][4];
    
    KeyExpansion(buffer, key);
    for (int i = 0; i < 44; i++)
    {
        for (int i2 = 0; i2 < 4; i2++)
        {
            printf("%02x ", buffer[i][i2]);
        }
        printf("\n");
    }



    return 0;
}