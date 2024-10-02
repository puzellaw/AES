#include"AES_functions.h"
#include<stdio.h>


int main(void){

    u_int8_t myChar = 0x7f;
    printf("%02x\n", sbox(myChar));


    u_int8_t vec[4] = {0x01, 0x02, 0x03, 0x04};
    rot_word(vec);
    for(int i = 0; i < 4; i++){
        printf("%x", vec[i]);
    }
    printf("\n");


    u_int16_t byte = 0b00010000;
    byte = x_times(byte);
    printf("%02x\n", byte);


    return 0;
}