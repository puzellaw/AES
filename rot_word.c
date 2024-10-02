#include<stdio.h>



void rot_word(u_int8_t vec[4]) {
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

int main(void) {
    u_int8_t vec[4] = {0x01, 0x02, 0x03, 0x04};

    rot_word(vec);
    
    for(int i = 0; i < 4; i++){
        printf("%x", vec[i]);
    }
    printf("\n");


    return 0;
}