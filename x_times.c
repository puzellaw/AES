#include"AES_functions.h"
#include<stdio.h>

u_int8_t XTimes(u_int8_t b){
    if ((int)(b & 0b10000000) == (int)(0b10000000)) {
        b = (b<<1)^0b00011011;
    }
    else {
        b = b<<1;
    }
    return b;
}
