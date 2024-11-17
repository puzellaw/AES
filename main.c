/* 
 * Implementation of AES Encryption Tool. See README for running details.  
 * Written by Will Puzella & Peter Kelly
 * Carleton College; Computer Science Department; Comps 2024
 */

#include"AES_functions.h"
#include"CBM_functions.h"
#include"utilities.h"

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

#include"GCM.c"
#include"ECB.c"
#include"CBC.c"


/*
    clang main.c utilites.c
*/

/* 
 * Helper function for printing matrices. 
 */
void print_matrix(u_int8_t mat[4][4]);

/* 
 * Function that takes in a string and converts it to its proper integer form. 
 */
u_int8_t *InterpretKey(char *key, int *bufferSize);


int main(int argc, char *argv[]){
    bool optionTag = false; 
    bool inputDirMode = false;
    bool outputDirMode = false;
    bool keyMode = false;
    bool ivMode = false;
    bool decryptMode = false;
    bool tagMode = false;
    char blockCipherMode = 'E';
    char *inputDir;
    char *outputDir;
    char *key = NULL;
    char *iv = NULL;
    char *tag = NULL;
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
        if (tagMode) {
            tag = argv[i];
            tagMode = false;
            continue;
        }
        for (int j = 0; j < strlen(argv[i]); j++) {
            
            if ((argv[i][j] == '-') && (j == 0)) {
                
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
                    case 'T':
                        tagMode = true;
                        optionTag = false;
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
    printf("Input: %s\nOutput: %s\nKey: %s\nEncyption Mode: %c\n", inputDir, outputDir, key, blockCipherMode);
    if (blockCipherMode == 'C' && iv == NULL) {
        printf("No Initialization vector found please include using the -V argument\n");
        exit(EXIT_FAILURE);
    }
    if (blockCipherMode == 'C' || (blockCipherMode == 'G' && iv != NULL)) {
        printf("Initialization Vector: %s\n", iv);
    }
    if (blockCipherMode == 'G' && decryptMode && tag == NULL) {
        printf("No tag found please include using the -T argument\n");
        exit(EXIT_FAILURE);
    }
    if (blockCipherMode == 'G' && decryptMode) {
        printf("Tag: %s\n", tag);
    }
    if (key == NULL) {
        printf("Key must be provided using the -K argument\n");
        exit(EXIT_FAILURE);
    }
    if (inputDir == NULL) {
        printf("Please include inputFile using the -I argument\n");
        exit(EXIT_FAILURE);
    }
    if (outputDir == NULL) {
        printf("Please include outputFile using the -O argument\n");
        exit(EXIT_FAILURE);
    }
    int *bufferSize = (int *)malloc(sizeof(int));
    assert(bufferSize);
    u_int8_t *InterpretedKey = InterpretKey(key, bufferSize);
    FILE *inputFile = openFile(inputDir);
    FILE * outputFile = openFileWrite(outputDir);
    if (decryptMode) { // Decrypt File with 128 Bit tag with block cipher mode chosen
        if (blockCipherMode == 'G') {
            int *vectorSize = (int *)malloc(4);
            assert(vectorSize);
            u_int8_t *interpretedVector = InterpretKey(iv,vectorSize);
            if (*vectorSize != 128) {
                printf("Initialization vector not 128bits. \n");
                free(bufferSize);
                free(vectorSize);
                free(InterpretedKey);
                return -1;
            }
            int *vectorSize2 = (int *)malloc(4);
            assert(vectorSize2);
            u_int8_t *interpretedTag = InterpretKey(tag,vectorSize2);
            if (*vectorSize2 != 128) {
                printf("Initialization vector not 128bits. \n");
                free(bufferSize);
                free(vectorSize);
                free(vectorSize2);
                free(InterpretedKey);
                free(interpretedTag);
                return -1;
            } 
            decryptFile_GCM(inputFile, outputFile, InterpretedKey, interpretedVector, interpretedTag, *bufferSize);
            fclose(inputFile);
            fclose(outputFile);
            free(bufferSize);
            free(vectorSize);
            free(vectorSize2);
            free(InterpretedKey);
            free(interpretedTag);
            return 1;
        } else if (blockCipherMode == 'E') {
            decryptFile_ECB(inputFile, outputFile, InterpretedKey, *bufferSize);
            fclose(inputFile);
            fclose(outputFile);
            free(bufferSize);
            free(InterpretedKey);
            return 1;
        } else if (blockCipherMode == 'C') {
            int *vectorSize = (int *)malloc(4);
            assert(vectorSize);
            u_int8_t *interpretedVector = InterpretKey(iv,vectorSize);
            if (*vectorSize != 128) {
                printf("Initialization vector not 128bits. \n");
                    free(bufferSize);
                    free(vectorSize);
                    free(InterpretedKey);
                    free(interpretedVector);
                    return -1;
            } 
            decryptFile_CBC(inputFile, outputFile, InterpretedKey, interpretedVector, *bufferSize);
            fclose(inputFile);
            fclose(outputFile);
            free(bufferSize);
            free(vectorSize);
            free(InterpretedKey);
            free(interpretedVector);
            return 1;
        }
    } else {
        if (blockCipherMode == 'G') {
            int *vectorSize = (int *)malloc(4);
            assert(vectorSize);
            u_int8_t *interpretedVector;
            if (iv != NULL) {
                interpretedVector = InterpretKey(iv,vectorSize);
            } else {
                interpretedVector = NULL;
                *vectorSize = 128;
            }
            
            if (*vectorSize != 128) {
                printf("Initialization vector not 128bits. \n");
                free(bufferSize);
                free(vectorSize);
                free(InterpretedKey);
                free(interpretedVector);
                return -1;
            } 
            encryptFile_GCM(inputFile, outputFile, InterpretedKey, interpretedVector, *bufferSize);
            fclose(inputFile);
            fclose(outputFile);
            free(bufferSize);
            free(vectorSize);
            free(InterpretedKey);
            free(interpretedVector);
            return 1;
        } else if (blockCipherMode == 'E') {
            encryptFile_ECB(inputFile, outputFile, InterpretedKey, *bufferSize);
            fclose(inputFile);
            fclose(outputFile);
            free(bufferSize);
            free(InterpretedKey);
            return 1;
        } else if (blockCipherMode == 'C') {
            int *vectorSize = (int *)malloc(4);
            assert(vectorSize);
            u_int8_t *interpretedVector = InterpretKey(iv,vectorSize);
            if (*vectorSize != 128) {
                printf("Initialization vector not 128bits. \n");
                free(bufferSize);
                free(vectorSize);
                free(InterpretedKey);
                free(interpretedVector);
                return -1;
            } 
            encryptFile_CBC(inputFile, outputFile, InterpretedKey, interpretedVector, *bufferSize);
            fclose(inputFile);
            fclose(outputFile);
            free(bufferSize);
            free(vectorSize);
            free(InterpretedKey);
            free(interpretedVector);
            return 1;
        }
    }
}

/* 
 * Helper Function that checks if a string only contains ints
 */
int checkNumber(char *str) {
    int isInt = 1;
    for (int i = 0; i > strlen(str); i++) {
        if (str[i] < 48 || str[i] > 57) {
            isInt = 0;
        }
    }
    return isInt;
}

/* 
 * Helper function for interpret key that given a char value interprets it as its numerical value in hex. 
 */
u_int8_t identifyChar(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ((u_int8_t) ch) - 48;
    } else if (ch >= 'a' && ch <= 'f'){
        return ((u_int8_t) ch)- 87;
    } else if (ch >= 'A' && ch <= 'F') {
        return ((u_int8_t) ch) - 55;
    } else {
        return (u_int8_t) -1;
    }
}

u_int8_t *InterpretKey(char *key, int *bufferSize) {
    
    if (key[0] == '0' && (key[1] == 'x' || key[1] == 'X')) { // Hex Interpret mode
        
        int keyStringlength = strlen(key) - 2;
        int i = 1;
        
        if (keyStringlength == 32) {
            u_int8_t *outputKey = (uint8_t *) malloc(16);
            assert(outputKey);
            while (i != 17) {
                
                outputKey[i-1] = identifyChar(key[2*i]);
                outputKey[i-1] = outputKey[i-1] << 4;
                outputKey[i-1] = outputKey[i-1] + identifyChar(key[(2*i)+1]);
                i++;
            }
            *bufferSize = 128;
            return outputKey;

        } else if (keyStringlength == 49) {
            u_int8_t *outputKey = (uint8_t *) malloc(24);
            assert(outputKey);
            while (i != 24) {
                outputKey[i-1] = identifyChar(key[2*i]);
                outputKey[i-1] = outputKey[i-1] << 4;
                outputKey[i-1] = outputKey[i-1] + identifyChar(key[(2*i)+1]);
                i++;
            }
            *bufferSize = 192;
            return outputKey;

        } else if (keyStringlength == 65) {
            u_int8_t *outputKey = (uint8_t *) malloc(32);
            assert(outputKey);
            while (i != 32) {

                outputKey[i-1] = identifyChar(key[2*i]);
                outputKey[i-1] = outputKey[i-1] << 4;
                outputKey[i-1] = outputKey[i-1] + identifyChar(key[(2*i)+1]);
                i++;
            }
            *bufferSize = 256;
            return outputKey;
        }
    } else if (checkNumber(key)) { // Int Interpret Mode
        // Decide if this will be needed
        return NULL;
    } else { // String Interpret Mode
        int keyStringlenth = strlen(key);
        if (keyStringlenth >= 16) {
            u_int8_t *outputKey = malloc(16);
            assert(outputKey);
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
            u_int8_t *outputKey =  malloc(24);
            assert(outputKey);
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
            u_int8_t *outputKey =  malloc(32);
            assert(outputKey);
            int i = 0;
            while (key[i]!='\0') {
                outputKey[i] = (u_int8_t) key[i];
                i++;  
            }
            while (i > 32) {
                outputKey[i] = 0;
                i++;
            }
            *bufferSize =  256; 
            return outputKey;
        }
        
    }
    return NULL;
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
