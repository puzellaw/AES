#ifndef CBC
#define CBC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CBM_functions.h"
#include "AES_functions.h"
#include "utilities.h"
#include "encryption.c"
#include "decryption.c"




/* int main()
{
   char *input_file = "CBC_input.txt";
   char *output_file = "enc_output.txt";
   u_int8_t buffer[4][4];
   FILE *fp = openFile(input_file);
   FILE *op = openFileWrite(output_file);

   
   u_int8_t key [] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
   u_int8_t testkey[] = {0x68, 0x6f, 0x77, 0x20, 0x6c, 0x6f, 0x6e, 0x67, 0x20, 0x69, 0x73, 0x20, 0x74, 0x68, 0x69, 0x73};
   u_int8_t initializationVector[] = {0x68, 0x6f, 0x77, 0x20, 0x6c, 0x6f, 0x6e, 0x67, 0x20, 0x69, 0x73, 0x20, 0x74, 0x68, 0x69, 0x73};
   encryptFile(fp, op, testkey, initializationVector);
   fclose(fp);
   fclose(op);

   FILE *test_in = fopen(output_file, "rb");
   FILE *test_out = fopen("denc_output.txt", "wb");

   decryptFile(test_in, test_out, testkey, initializationVector);

   return 0;
}
*/

u_int8_t *encryptFile_CBC(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *iv, int encryptionScheme) {
    int nk;
    int nr;
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
    u_int8_t previousVector[4][4];
    char ch;
    int i = 0;
    for (int q = 0; q < 16; q++) {
        previousVector[q%4][q/4] = iv[q]; 
    }
    
    while (feof(inputFile) == 0) {
        ch = fgetc(inputFile);

        if (i == 15) {
            block[i%4][i/4] = (u_int8_t)ch;
            XOR(block, previousVector);
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
                previousVector[j%4][j/4] = block[j%4][j/4];
                fputc(block[j%4][j/4], outputFile);
            }
            i = 0; 
        } else {
            block[i%4][i/4] = (u_int8_t)ch;
            i++;
        }
    }
    while (i < 16 && (i != 0)) {
        block[i%4][i/4] = 0x00;
        i++;
    }
    XOR(block, previousVector);
    AES_128(block, key);
    for (int j = 0; j < 16; j++) {
        fputc(block[j%4][j/4], outputFile);
    }
    return NULL;
}
 
u_int8_t *decryptFile_CBC(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *iv, int encryptionScheme) {
    int nk;
    int nr;
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
    u_int8_t previousVector[4][4];
    u_int8_t initialVector[4][4];
    ch = fgetc(inputFile);
    for (int q = 0; q < 16 ; q++) {
        initialVector[q%4][q/4] = iv[q]; 
    }
    while (feof(inputFile) == 0) {
        if (i == 15) {
            block[i%4][i/4] = (u_int8_t)ch;
            for (int iter = 0; iter < 4; iter++)
            {
                for (int iter2 = 0; iter2 < 4; iter2++)
                {
                    previousVector[iter][iter2] = initialVector[iter][iter2];
                    initialVector[iter][iter2] = block[iter][iter2];
                }    
            }
            InvCipher(block, nr, keyExp);
            XOR(block,previousVector);
            for (int j = 0; j < 16; j++) {
                fputc(block[j%4][j/4], outputFile);
            }
            i = 0; 
        }
        else {
            block[i%4][i/4] = (u_int8_t)ch;
            i++;
        }
        ch = fgetc(inputFile);
    }
    while (i < 16 && (i != 0)) {
        block[i%4][i/4] = 0x00;
        i++;
    }
    if (i == 16) {
        InvCipher(block, nr, keyExp);
        XOR(block, previousVector);
        for (int j = 0; j < 16; j++) {
            if (block[j%4][j/4] != 0) {
                fputc(block[j%4][j/4], outputFile);
            }
        }
    }
    return NULL;
}

#endif