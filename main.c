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
    bool inputDirMode = false;
    bool outputDirMode = false;
    bool keyMode = false;
    bool ivMode = false;
    bool decryptMode = false;
    int encyptionMode = 128;
    char blockCipherMode = 'E';
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
                        optionTag = false;
                        break;
                    case 'O':
                        outputDirMode = true; 
                        optionTag = false;
                        break;
                    case 'V':
                        ivMode = true;
                        optionTag = false;
                        break;
                    case 'K':
                        keyMode = true;
                        optionTag = false;
                        break;
                    case 'D':
                        decryptMode = true;
                    default:
                        break;
                break; 
                }

            }

        }
    }
    u_int8_t *bufferSize = (u_int8_t *)malloc(1);
    u_int8_t *InterpretedKey = InterpretKey(key, bufferSize);
    
    FILE *inputFile = openFile(inputDir);
    FILE * outputFile = openFileWrite(outputDir);
    if (decryptMode) { // Decrypt File with 128 Bit tag with block cipher mode chosen
        if (blockCipherMode == 'G') {
            u_int8_t *vectorSize = (u_int8_t *)malloc(1);
            u_int8_t *interpretedVector = InterpretKey(iv,vectorSize);
            if (vectorSize != 16) {
                printf("Initialization vector not 128bits. \n");
                return -1;
            } 
            return (int) *decryptFile_GCM(inputFile, outputFile, InterpretedKey, interpretedVector,(int) *bufferSize);
        } else if (blockCipherMode == 'E') {
            return (int) * decryptFile_ECB(inputFile, outputFile, InterpretedKey,(int) *bufferSize);
        } else if (blockCipherMode == 'C') {
            u_int8_t *vectorSize = (u_int8_t *)malloc(1);
            u_int8_t *interpretedVector = InterpretKey(iv,vectorSize);
            if (vectorSize != 16) {
                printf("Initialization vector not 128bits. \n");
                    return -1;
            } 
            return (int) *decryptFile_CBC(inputFile, outputFile, InterpretedKey, interpretedVector,(int) *bufferSize);
        }
    } else {
        if (blockCipherMode == 'G') {
            u_int8_t *vectorSize = (u_int8_t *)malloc(1);
            u_int8_t *interpretedVector = InterpretKey(iv,vectorSize);
            if (vectorSize != 16) {
                printf("Initialization vector not 128bits. \n");
                return -1;
            } 
            return (int) *encryptFile_GCM(inputFile, outputFile, InterpretedKey, interpretedVector,(int) *bufferSize);
        } else if (blockCipherMode == 'E') {
            return (int) * encryptFile_ECB(inputFile, outputFile, InterpretedKey, (int) *bufferSize);

        } else if (blockCipherMode == 'C') {
            u_int8_t *vectorSize = (u_int8_t *)malloc(1);
            u_int8_t *interpretedVector = InterpretKey(iv,vectorSize);
            if (vectorSize != 16) {
                printf("Initialization vector not 128bits. \n");
                return -1;
            } 
            return (int) *encryptFile_CBC(inputFile, outputFile, InterpretedKey, interpretedVector, (int) *bufferSize);
        }
    }
}


int checkNumber(char *str) {
    int isInt = 1;
    for (int i = 0; i > strlen(str); i++) {
        if (str[i] < 48 || str[i] > 57) {
            isInt = 0;
        }
    }
    return isInt;
}
int identifyChar(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ((int) ch) - 48;
    } else if (ch >= 'a' && ch <= 'f'){
        return ((int) ch)- 82;
    } else if (ch >= 'A' && ch <= 'F') {
        return ((int) ch) - 50;
    }
}

u_int8_t*InterpretKey(char *key, u_int8_t *bufferSize) {
    if (key[0] == '0' && (key[1] == 'x' || key[1] == 'X')) { // Hex Interpret mode
        int keyStringlength = strlen(key) - 2;
        int i = 0;
        if (keyStringlength = 32) {
            u_int8_t outputKey[16];
            while (key[2*i] != '\0' || key[(2*i)+1] != '\0') {
                outputKey[15-i] = identifyChar(key[2*i]);
                outputKey[15-i] = outputKey[15-i] + (16*identifyChar(key[(2*i)+1]));
            }
            *bufferSize = 128;
            return outputKey;

        } else if (keyStringlength = 48) {
            u_int8_t outputKey[24];
            while (key[2*i] != '\0' || key[(2*i)+1] != '\0') {
                outputKey[23-i] = identifyChar(key[2*i]);
                outputKey[23-i] = outputKey[23-i] + (16*identifyChar(key[(2*i)+1]));
            }
            *bufferSize = 192;
            return outputKey;
        } else if (keyStringlength = 64) {
            u_int8_t outputKey[32];
            while (key[2*i] != '\0' || key[(2*i)+1] != '\0') {
                outputKey[31-i] = identifyChar(key[2*i]);
                outputKey[31-i] = outputKey[31-i] + (16*identifyChar(key[(2*i)+1]));
            }
            *bufferSize = 256;
            return outputKey;
        }
    } else if (checkNumber(key)) { // Int Interpret Mode
        // Decide if this will be needed
    } else { // String Interpret Mode
        int keyStringlenth = strlen(key);
        if (keyStringlenth >= 16) {
            u_int8_t outputKey[16];
            int i = 0;
            while (key[i]!='\0') {
                outputKey[i] = (u_int8_t) key[i];
                i++;  
            }
            while (i > 16) {
                outputKey[i] = 0;
                i++;
            }
            *bufferSize = 128;
            return outputKey;
        } else if (keyStringlenth >= 24) {
            u_int8_t outputKey[24];
            int i = 0;
            while (key[i]!='\0') {
                outputKey[i] = (u_int8_t) key[i];
                i++;  
            }
            while (i > 24) {
                outputKey[i] = 0;
                i++;
            }
            *bufferSize = 192;
            return outputKey;
        } else {
            u_int8_t outputKey[32];
            int i = 0;
            while (key[i]!='\0') {
                outputKey[i] = (u_int8_t) key[i];
                i++;  
            }
            while (i > 32) {
                outputKey[i] = 0;
                i++;
            }
            *bufferSize = 256; 
            return outputKey;
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