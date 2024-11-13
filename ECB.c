/* 
 * Implementation of AES-ECB Block Cipher Mode Functions. 
 * Written by Will Puzella & Peter Kelly
 * Carleton College; Computer Science Department; Comps 2024
 */


#ifndef ECB
#define ECB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CBM_functions.h"
#include "AES_functions.h"
#include "utilities.h"
#include "encryption.c"
#include "decryption.c"


int encryptFile_ECB(FILE *inputFile, FILE *outputFile, u_int8_t *key, int encryptionScheme) {
    u_int8_t block[4][4];
    char ch;
    int i = 0;
    while (feof(inputFile) == 0) {
        ch = fgetc(inputFile);
        if (i == 15) {
            block[i%4][i/4] = (u_int8_t)ch;
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
            for (int j = 0; j < 16; j++) {
                fputc(block[j%4][j/4], outputFile);
            }
            i = 0; 
        } else {
            block[i%4][i/4] = (u_int8_t)ch;
            i++;
        }
    }
    if (i != 0) {
        while (i < 16 && (i != 0)) {
            block[i%4][i/4] = 0x00;
            i++;
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
        for (int j = 0; j < 16; j++) {
            if (block[j%4][j/4] != 0 || block[j%4][j/4] != 0xff) {
                    fputc(block[j%4][j/4], outputFile);
            }
        }
    }
    return 1;
}

int decryptFile_ECB(FILE *inputFile, FILE *outputFile, u_int8_t *key, int encryptionScheme) {
    int nk = 0;
    int nr = 0;
    if (encryptionScheme == 128) {
        nk = 4;
        nr = 10;
    } else if (encryptionScheme == 192) {
        nk = 6;
        nr = 12;
    } else if (encryptionScheme == 256) {
        nk = 8;
        nr = 14;
    }
    
    u_int8_t block[4][4];
    u_int8_t keyExp[(nr + 1)*nk][4];
    KeyExpansionEIC(keyExp, key, nk, nr);
    char ch;
    int i = 0;
    ch = fgetc(inputFile);
    while (feof(inputFile) == 0) {  
        if (i == 15) {
            block[i%4][i/4] = (u_int8_t)ch;
            InvCipher(block, nr, keyExp);
            ch = fgetc(inputFile);
            for (int j = 0; j < 16; j++) {
                if (feof(inputFile) != 0 && block[j%4][j/4] != 0 && block[j%4][j/4] != 0xff) {
                    fputc(block[j%4][j/4], outputFile);
                } else if (feof(inputFile) == 0) {
                    fputc(block[j%4][j/4], outputFile);
                }
                
            }
            i = 0; 
        } else {
            block[i%4][i/4] = (u_int8_t)ch;
            i++;
            ch = fgetc(inputFile);
        }
        
    }
    if (i != 0) {
        while (i < 16 && (i != 0)) {
            block[i%4][i/4] = 0x00;
            i++;
        }
        if (i == 16) {
            InvCipher(block, nr, keyExp);
            for (int j = 0; j < 16; j++) {
                if (block[j%4][j/4] != 0 || block[j%4][j/4] != 0xff) {
                    fputc(block[j%4][j/4], outputFile);
                }
            }
        }
    }
    return 1;
}

#endif