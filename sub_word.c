#include<stdio.h>
#include "AES_functions.h"

void SubWord(u_int8_t vec[4]) {
    for (int i = 0; i < 4; i++)
    {
        vec[i] = SBox(vec[i]);
    }
    
}
