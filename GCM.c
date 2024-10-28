#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "encryption.c"
#include "decryption.c"


FILE *openFile(char *file_name);
u_int8_t *encryptFile(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *n);
u_int8_t *decryptFile(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *n);
FILE *openFileWrite(char *file_name);
int getBit(u_int8_t ch, int index);
void moveRight(u_int8_t blocks[16]);

int main()
{
//    char *input_file = "CBC_input.txt";v cwz
//    char *output_file = "enc_output.txt";
//    u_int8_t buffer[4][4];
//    FILE *fp = openFile(input_file);
//    FILE *op = openFileWrite(output_file);

   
//    u_int8_t key [] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
//    u_int8_t testkey[] = {0x68, 0x6f, 0x77, 0x20, 0x6c, 0x6f, 0x6e, 0x67, 0x20, 0x69, 0x73, 0x20, 0x74, 0x68, 0x69, 0x73};
//    u_int8_t initializationVector[] = {0x68, 0x6f, 0x77, 0x20, 0x6c, 0x6f, 0x6e, 0x67, 0x20, 0x69, 0x73, 0x20, 0x74, 0x68, 0x69, 0x73};
//    encryptFile(fp, op, testkey, initializationVector);
//    fclose(fp);
//    fclose(op);

//    FILE *test_in = fopen(output_file, "rb");
//    FILE *test_out = fopen("denc_output.txt", "wb");

//    decryptFile(test_in, test_out, testkey, initializationVector);
    u_int8_t blocks[16] = {0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff};
    moveRight(blocks);
    for (int i = 0; i < 16; i++)
    {
        printf("%02x", blocks[i]);
    }
    

   return 0;
} 

void randomIntBlock(u_int8_t dest[4][4], u_int8_t previousBlock[4][4]) {
    /* srand(time(NULL));
    unsigned __int128 hi_num = 0xffffffffffffffffff;
    u_int16_t low_num = 0; 
    return (rand() % (hi_num - low_num)) + low_num;
    */
    if (previousBlock == NULL) {
        for (int i=0; i < 4; i++) {
            for (int j=0; j < 4; j++) {
                srand(time(NULL) + j + i);
                dest[j][i] = (u_int8_t) rand()%0xff;
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

void XOR(u_int8_t a[][4], u_int8_t b[][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            a[i][j] = a[i][j] ^ b[i][j];
        }
    }
}

FILE *openFile(char *file_name) {
    FILE *fp; 
    fp = fopen(file_name, "rb");

    if( fp == NULL ) //error checking
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
    return fp;
}

FILE *openFileWrite(char *file_name) {
    FILE *fp; 
    char ch;
    fp = fopen(file_name, "wb");

    if( fp == NULL ) //error checking
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
    return fp;
}

void blockMult(u_int8_t buffer[16], u_int8_t block1[16], u_int8_t block2[16]) {
    for (int i = 0; i < 16; i++)
    {
        buffer[i] = 0x00;
    }
    u_int8_t R[16] = {0xe1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int iter = 0; iter < 128; iter++)
    {
        if(getBit(block1[iter/16], iter%16) != 0) {
            for (int iter2 = 0; iter2 < 16; iter2++)
            {
                buffer[iter2] = buffer[iter2]^block2[iter2];
            }
        }
        if(getBit(block2[15], 15) != 0) {
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
    u_int8_t mask = ~(~0 << (1));
    u_int8_t value = (ch >> index) & mask;
    return (int)value;
}

void moveRight(u_int8_t blocks[16]) {
    for (int i = 16; i > 0; i--)
    {
        if(getBit(blocks[i-1], 7) == 1) {
            blocks[i] = (blocks[i] >> 1)|0x80;
        }
        else {
            blocks[i] = (blocks[i] >> 1);
        }
    }
    blocks[0] = blocks[0]>>1;
}




u_int8_t *encryptFile(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *iv) {
    int nk;
    int nr;
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
            AES_128(block, key);
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
    while (i < 16) {
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

u_int8_t *decryptFile(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *iv) {
    int nk;
    int nr;
    u_int8_t block[4][4];
    u_int8_t keyExp[44][4];
    KeyExpansionEIC(keyExp, key, 4, 10);
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
            InvCipher(block, 10, keyExp);
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
        InvCipher(block, 10, keyExp);
        XOR(block, previousVector);
        for (int j = 0; j < 16; j++) {
            fputc(block[j%4][j/4], outputFile);
        }
    }
    return NULL;
}