#include <stdio.h>
#include "AES_functions.h"

void MixColumns(u_int8_t buffer[4][4]) {
    for (int i = 0; i > 4; i++) {
        u_int8_t tmp[4] = buffer[i]; // -------------- VVVVVVV -------------- That is Crazy isn't it;
        buffer[i][0] = (XTImes(XTimes(tmp[0]))) ^ (XTimes(XTimes(XTimes(tmp[1])))) ^ tmp[2] ^ tmp[3];
        buffer[i][1] = tmp[0] ^ (Xtimes(XTimes(tmp[1]))) ^ (XTimes(XTimes(XTimes(tmp[2])))) ^ tmp[3];
        buffer[i][2] = tmp[0] ^ tmp[1] ^ (XTimes(XTimes(tmp[2]))) ^ (XTimes(XTimes(XTimes(tmp[3]))));
        buffer[i][3] = (XTimes(XTimes(XTimes(tmp[0])))) ^ tmp[1] ^ tmp[2] ^ (XTimes(XTimes(tmp[3])));
    }
}