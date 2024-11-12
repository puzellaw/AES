#ifndef GCM
#define GCM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "encryption.c"
#include "decryption.c"
#include "CBM_functions.h"
#include "utilities.h"

// Computes y+1 step of GHASH function, returns result in A
void GHASH(u_int8_t A[16], u_int8_t B[16], u_int8_t H[16]) {
    
    for (int iter = 0; iter < 16; iter++)
    {
            B[iter] = A[iter]^B[iter];
     }
    blockMult(A, B, H);
    
}

void randomIntBlock(u_int8_t dest[4][4], u_int8_t previousBlock[4][4]) {
    if (previousBlock == NULL) {
        for (int i=0; i < 4; i++) {
            for (int j=0; j < 4; j++) {
                srand(time(NULL) + j + i);
                dest[i][j] = (u_int8_t) rand()%0xff;

            }
        }
        return;
    } else {
        bool changed = false;
        for (int i=3; i >= 0; i--) {
            if (changed) {
                break;
            }
            for (int j=3; j >= 0; j--) {
                if (changed) {
                    break;
                }
                if (previousBlock[j][i] != 0xff) {
                    previousBlock[j][i]++;
                    changed = true;
                }
                if (previousBlock[j][i] == 0xff) {
                    previousBlock[j][i] = 0; 
                }
            }
        }
        return; 
    }
} 

//  u_int8_t num1[16] = {0xac, 0xbe, 0xf2, 0x05, 0x79, 0xb4, 0xb8, 0xeb, 0xce, 0x88, 0x9b, 0xac, 0x87, 0x32, 0xda, 0xd7};
// u_int8_t num2[16] = {0xed, 0x95, 0xf8, 0xe1, 0x64, 0xbf, 0x32, 0x13, 0xfe, 0xbc, 0x74, 0x0f, 0x0b, 0xd9, 0xc4, 0xaf};
// expect 4DB870D37CB75FCB46097C36230D1612
/*
    Multiplies two blocks and puts the result in the buffer
*/
void blockMult(u_int8_t buffer[16], u_int8_t block1[16], u_int8_t block2[16]) {
    for (int i = 0; i < 16; i++)
    {
        buffer[i] = 0x00;
    }
    u_int8_t R[16] = {0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int iter = 0; iter < 128; iter++)
    {       
        if(getBit(block1[iter/8], 7 - iter%8) != 0) {
            for (int iter2 = 0; iter2 < 16; iter2++)
            {
                buffer[iter2] = buffer[iter2]^block2[iter2];
            }
        } 
        if(getBit(block2[15], 0) == 0) {
            moveRight(block2);
        } 
        else {
            moveRight(block2);
            for (int i = 0; i < 16; i++)
            {
                block2[i] = block2[i]^R[i];
            }
        }
    }
}

// Gets the bit specified by the index (starts from 0)
int getBit(u_int8_t ch, int index) {
    u_int8_t mask = ~((unsigned)~0 << (1));
    u_int8_t value = (ch >> index) & mask;
    return (int)value;
}

void moveRight(u_int8_t blocks[16]) {
    for (int i = 15; i > 0; i--)
    {
        if(getBit(blocks[i-1], 0) == 1) {
            blocks[i] = (blocks[i] >> 1)|0x80;
        }
        else {
            blocks[i] = (blocks[i] >> 1);
        }
    }
    blocks[0] = blocks[0]>>1;
}

void flatten(u_int8_t buffer[16], u_int8_t state[4][4]) {
    for (int iter = 0; iter < 16; iter++)
    {
        buffer[iter] = state[iter%4][iter/4];
    }
}


void encryptFile_GCM(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *n, int encryptionScheme) {
    u_int8_t block[4][4];
    u_int8_t counter[4][4];
    u_int8_t counterCopy[4][4];
    u_int8_t h[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u_int8_t hash[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u_int8_t *flatblock = (u_int8_t *) malloc(16);
    u_int64_t length = 0;
    char ch = fgetc(inputFile);
    int i = -1;
    if (n != NULL) {
        for (int q = 0; q < 16; q++) {
            counter[q%4][q/4] = n[q]; 
            counterCopy[q%4][q/4] = n[q]; 
        }
    } else {
        randomIntBlock(counter, NULL);
        printf("N Created for GCM Scheme: ");
        for (int q = 0; q < 16; q++) {
            counterCopy[q%4][q/4] = counter[q%4][q/4];
            printf("%c", counter[q%4][q/4]);
        }
        printf("\n");
    }
    
    
    while (feof(inputFile) == 0) {
        if (i == -1) {
            for (int q =0; q < 16; q++) {
                block[q%4][q/4] = 0;
            }
            switch (encryptionScheme) {
                case 128:
                    AES_128(block, key);
                    break;
                case 192:
                    AES_192(block, key);
                    break;
                case 256:
                    AES_256(block, key);
                    break;
                default:
                    break;
            }
            flatten(h, block);
            i = 0; 
        }
        if (i == 15) {
            block[i%4][i/4] = (u_int8_t)ch;
            switch (encryptionScheme) {
                case 128:
                    AES_128(counter, key);
                    break;
                case 192:
                    AES_192(counter, key);
                    break;
                case 256:
                    AES_256(counter, key);
                    break;
                default:
                    break;
            }
            XOR(block, counter);
            flatten(flatblock, block);
            GHASH(hash, flatblock, h);
            randomIntBlock(counterCopy,counterCopy);
            length = length + 8;
            for (int j = 0; j < 16; j++) {
                counter[j%4][j/4] = counterCopy[j%4][j/4];
                fputc(block[j%4][j/4], outputFile);
            }
            i = 0;
            ch = fgetc(inputFile);
        } else {
            block[i%4][i/4] = (u_int8_t)ch;
            i++;
            ch = fgetc(inputFile);
        }
    }
    if (i != 0) {
        length = length + 8;    
        while (i < 16) {
            block[i%4][i/4] = 0x00;
            i++;
        }
        switch (encryptionScheme) {
            case 128:
                AES_128(counter, key);
                break;
            case 192:
                AES_192(counter, key);
                break;
            case 256:
                AES_256(counter, key);
                break;
            default:
                break;
        }
        XOR(block, counter);
        flatten(flatblock, block);
        GHASH(hash, flatblock, h);
        for (int j = 0; j < 16; j++) {
            if (block[j%4][j/4] != 0 && block[j%4][j/4] != 0xff) {
                fputc(block[j%4][j/4], outputFile);
            }
        }
        printf("\n");
    }

    for (int i = 0; i < 16; i++) {
        if (i > 8) {
            flatblock[i] = 0;
        } else {
            flatblock[i] = 0xff & length;
            length = length >> 8;
        }
    }
    GHASH(hash, flatblock, h);
    printf("Authentication Tag: 0x");
    for (int i =0; i < 16; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

void decryptFile_GCM(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *n, u_int8_t* tag, int encryptionScheme) {
    u_int8_t block[4][4];
    u_int8_t counter[4][4];
    u_int8_t counterCopy[4][4];
    u_int8_t h[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u_int8_t hash[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    u_int8_t flatblock[16];
    u_int64_t length = 0;
    char ch = fgetc(inputFile);
    int i = -1;
    for (int q = 0; q < 16; q++) {
        counter[q%4][q/4] = n[q]; 
        counterCopy[q%4][q/4] = n[q]; 
    }
    
    
    while (feof(inputFile) == 0) {
        if (i == -1) {
            for (int q =0; q < 16; q++) {
                block[q%4][q/4] = 0;
            }
            switch (encryptionScheme) {
                case 128:
                    AES_128(block, key);
                    break;
                case 192:
                    AES_192(block, key);
                    break;
                case 256:
                    AES_256(block, key);
                    break;
                default:
                    break;
            }
            flatten(h, block);
            i = 0; 
        }
        if (i == 15) {
            block[i%4][i/4] = (u_int8_t)ch;
            flatten(flatblock, block);
            GHASH(hash, flatblock, h);
            switch (encryptionScheme) {
                case 128:
                    AES_128(counter, key);
                    break;
                case 192:
                    AES_192(counter, key);
                    break;
                case 256:
                    AES_256(counter, key);
                    break;
                default:
                    break;
            }
            XOR(block, counter);
            randomIntBlock(counterCopy,counterCopy);
            length = length + 8;
            ch = fgetc(inputFile);
            for (int j = 0; j < 16; j++) {
                counter[j%4][j/4] = counterCopy[j%4][j/4];
                if (feof(inputFile) != 0 && block[j%4][j/4] != 0 && block[j%4][j/4] != 0xff) {
                    fputc(block[j%4][j/4], outputFile);
                } else if (feof(inputFile) == 0) {
                    fputc(block[j%4][j/4], outputFile);
                }
            }
            i = 0;
            
        } 
        else {
            block[i%4][i/4] = (u_int8_t)ch;
            i++;
            ch = fgetc(inputFile);

        }
        
    }
    
    if (i != 0) {
        length = length + 8;
        while (i < 16) {
            block[i%4][i/4] = 0x00;
            i++;
        }
        flatten(flatblock, block);
        GHASH(hash, flatblock, h);
        switch (encryptionScheme) {
            case 128:
                AES_128(counter, key);
                break;
            case 192:
                AES_192(counter, key);
                break;
            case 256:
                AES_256(counter, key);
                break;
            default:
                break;
        }
        XOR(block, counter);
        
        for (int j = 0; j < 16; j++) {
            if (block[j%4][j/4] != 0 && block[j%4][j/4] != 0xff) {
                fputc(block[j%4][j/4], outputFile);
            }
        }
    }
    
    for (int i = 0; i < 16; i++) {
        if (i > 8) {
            flatblock[i] = 0;
        } else {
            flatblock[i] = 0xff & length;
            length = length >> 8;
        }
    }
    GHASH(hash, flatblock, h);
    printf("DECRYPT AUTHENTICATION TAG\n");
    for (int iter = 0; iter < 16; iter++)
    {
        printf("%02x", hash[iter]);
    }
    printf("\n");
    printf("Input AUTHENTICATION TAG\n");
    for (int iter = 0; iter < 16; iter++)
    {
        printf("%02x", tag[iter]);
    }
    printf("\n");
    
    for (int i = 0; i < 16; i++) {
        if (tag[i] != hash[i]) {
            printf("Tag did not Authenticate. File has been tampered with. \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("TAG AUTHENTICATED\n");
}

#endif