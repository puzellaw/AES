#include"AES_functions.h"
#include<stdio.h>



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
