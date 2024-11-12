#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.c"
#include "decryption.c"


FILE *openFile(char *file_name);
u_int8_t *encryptFile(FILE *inputFile, FILE *outputFile, u_int8_t *key);
u_int8_t *decryptFile(FILE *inputFile, FILE *outputFile, u_int8_t *key);
FILE *openFileWrite(char *file_name);

int main()
{
   char *input_file = "test.txt";
   char *output_file = "encrypted.txt";
   u_int8_t buffer[4][4];
   FILE *fp = openFile(input_file);
   FILE *op = openFileWrite(output_file);

   FILE *test_in = fopen(output_file, "rb");
   FILE *test_out = fopen("output.txt", "wb");
   
   u_int8_t key [] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
   u_int8_t testkey[] = {0x68, 0x6f, 0x77, 0x20, 0x6c, 0x6f, 0x6e, 0x67, 0x20, 0x69, 0x73, 0x20, 0x74, 0x68, 0x69, 0x73};
   encryptFile(fp, op, testkey);
   decryptFile(test_in, test_out, testkey);

   return 0;
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

u_int8_t *encryptFile(FILE *inputFile, FILE *outputFile, u_int8_t *key) {
    int nk;
    int nr;
    u_int8_t block[4][4];
    char ch;
    int i = 0;
    while (( ch = fgetc(inputFile) ) != EOF) {

        if (i == 15) {
            block[i%4][i/4] = (u_int8_t)ch;
            AES_128(block, key);
            for (int j = 0; j < 16; j++) {
                printf("got here instead");
                fputc(block[j%4][j/4], outputFile);
                // fwrite(&block[j%4][j/4], 1, 1, outputFile);
                //int res = fputc(block[i%4][i/4], outputFile);
                //printf("RESULT %d", res);
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
    for (int iter = 0; iter < 4; iter++)
    {
        for (int iter2 = 0; iter2 < 4; iter2++)
        {
            printf("%02x ", block[iter][iter2]);
        }
        printf("\n");   
    }
    AES_128(block, key);
    for (int j = 0; j < 16; j++) {
        fputc(block[j%4][j/4], outputFile);
    }


    for (int iter = 0; iter < 4; iter++)
    {
        for (int iter2 = 0; iter2 < 4; iter2++)
        {
            printf("%02x ", block[iter][iter2]);
        }
        printf("\n");   
    }
    
    
    return NULL;
}

u_int8_t *decryptFile(FILE *inputFile, FILE *outputFile, u_int8_t *key) {
    int nk;
    int nr;
    u_int8_t block[4][4];
    u_int8_t keyExp[44][4];
    KeyExpansionEIC(keyExp, key, 4, 10);
    char ch;
    int i = 0;
    while (( ch = fgetc(inputFile) ) != EOF) {

        if (i == 15) {
            block[i%4][i/4] = (u_int8_t)ch;
            InvCipher(block, 10, keyExp);
            for (int j = 0; j < 16; j++) {
                fputc(block[j%4][j/4], outputFile);
                // fwrite(&block[j%4][j/4], 1, 1, outputFile);
                //int res = fputc(block[i%4][i/4], outputFile);
                //printf("RESULT %d", res);
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
    for (int iter = 0; iter < 4; iter++)
    {
        for (int iter2 = 0; iter2 < 4; iter2++)
        {
            printf("%02x ", block[iter][iter2]);
        }
        printf("\n");   
    }
    InvCipher(block, 10, keyExp);
    for (int j = 0; j < 16; j++) {
        fputc(block[j%4][j/4], outputFile);
    }


    for (int iter = 0; iter < 4; iter++)
    {
        for (int iter2 = 0; iter2 < 4; iter2++)
        {
            printf("%02x ", block[iter][iter2]);
        }
        printf("\n");   
    }
    
    
    return NULL;
}