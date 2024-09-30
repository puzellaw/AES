/*
    Printing byte matrix
    By: Peter Kelly
    9/30/24

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_mat(u_int8_t mat[4][4])  {
    for (int i = 0; i < 4; i++) {
        for (int i2 = 0; i2 < 4; i2++) {
            if (i2== 0){
                printf("|");
            }
            printf("(%02x)", mat[i][i2]);
            if(i2 == 3) {
                printf("|\n");
            }
        }
    }
}

void fill_mat(u_int8_t mat[4][4]) {
    for (int i = 0; i < 4; i++) {
            for (int i2 = 0; i2 < 4; i2++) {
                mat[i][i2] = rand() % (256); 
            }
        }
}



int main(void) {
    srand(time(NULL));   // Initialization, should only be called once.
    u_int8_t mat[4][4];

    fill_mat(mat);
    print_mat(mat);

    return 0;
}



