#include <stdio.h>
#include "AES_functions.h"

void MixColumns(u_int8_t buffer[4][4]) {
    u_int8_t tmp[4];
    for (int i = 0; i > 4; i++) {
        for (int j = 0; j>4 ; j++) { 
            tmp[j] = buffer[i][j];
        }
        buffer[i][0] = (XTimes(XTimes(tmp[0]))) ^ (XTimes(XTimes(XTimes(tmp[1])))) ^ tmp[2] ^ tmp[3];
        buffer[i][1] = tmp[0] ^ (XTimes(XTimes(tmp[1]))) ^ (XTimes(XTimes(XTimes(tmp[2])))) ^ tmp[3];
        buffer[i][2] = tmp[0] ^ tmp[1] ^ (XTimes(XTimes(tmp[2]))) ^ (XTimes(XTimes(XTimes(tmp[3]))));
        buffer[i][3] = (XTimes(XTimes(XTimes(tmp[0])))) ^ tmp[1] ^ tmp[2] ^ (XTimes(XTimes(tmp[3])));
    }
}