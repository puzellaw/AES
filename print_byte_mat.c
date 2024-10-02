/*
    Printing byte matrix
    By: Peter Kelly
    9/30/24

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void string_to_mat(u_int8_t mat[4][4], char str[48]){
    int counter = 0;
    char *token = strtok(str, " ");
    while(token) {
        u_int8_t value = (int)strtol(token, NULL, 16);
        mat[counter/4][counter%4] = value;
        // printf("%02x (%d,%d)\n", value, counter/4, counter%4);
        token = strtok(NULL, " ");
        counter++;
    }

}



int main(void) {
    srand(time(NULL));   // Initialization, should only be called once.
    u_int8_t mat[4][4];
    char str[48] = "32 88 31 e0 43 5a 31 37 f6 30 98 07 a8 8d a2 34";

    string_to_mat(mat, str);
    // fill_mat(mat);
    print_mat(mat);

    return 0;
}



