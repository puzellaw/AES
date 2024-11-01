#include"AES_functions.h"
#include"CBM_functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include"GCM.c"
#include"ECB.c"
#include"ECB.c"


/*
    clang main.c encryption.c decryption.c utilites.c
*/

void print_matrix(u_int8_t mat[4][4]);

void test_decrypt();

void test_encrypt();

int main(int argc, char *argv[]){
    bool optionTag = false; 
    char blockCipherMode = 'E';
    int encyptionMode = 128;
    bool inputDirMode = false;
    bool outputDirMode = false;
    bool keyMode = false;
    bool ivMode = false;
    char *inputDir;
    char *outputDir;
    char *key;
    char *iv;
    for (int i = 1; i < argc; i++) {
        if (outputDirMode) {
            outputDir = argv[i];
            outputDirMode = false;
            continue;
        }
        if (inputDirMode) {
            inputDir = argv[i];
            inputDirMode = false;
            continue;
        }
        if (keyMode) {
            key = argv[i];
            keyMode = false;
            continue;
        }
        if (ivMode) {
            iv = argv[i];
            ivMode = false;
            continue;
        }
        for (int j = 0; j < strlen(argv[argc]); j++) {
            if (argv[i][j] == '-' && j == 0) {
                optionTag = true; 
            }
            if (optionTag) {
                switch(argv[i][j]) {
                    case 'G':
                        blockCipherMode = 'G';
                        break;
                    case 'E':
                        blockCipherMode = 'E';
                        break;
                    case 'C':
                        blockCipherMode = 'C';
                        break;

                    case 'I':
                        inputDirMode = true;
                        break;
                    case 'O':
                        outputDirMode = true; 
                        break;
                    case 'V':
                        ivMode = true;
                        break;
                    case 'K':
                        keyMode = true;
                        break;
                    default:
                        break;
                break; 
                }
            }
        }
    }
}

void print_matrix(u_int8_t mat[4][4])  {
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