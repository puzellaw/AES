#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.c"



FILE *openFile(char *file_name);
u_int8_t *encryptFile(FILE *inputFile, FILE *outputFile, u_int8_t *key);
FILE *openFileWrite(char *file_name);

int main()
{
   char *input_file = "test.txt";
   char *output_file = "encrypted.txt";
   u_int8_t buffer[4][4];
   FILE *fp = openFile(input_file);
   FILE *op = openFileWrite(output_file);
   u_int8_t key [] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
   encryptFile(fp, op, key);

   return 0;
}

FILE *openFile(char *file_name) {
    FILE *fp; 
    char ch;
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
            for (int j; j < 16; j++) {
                fwrite(&block[j%4][j/4], 1, 1, outputFile);
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
    AES_128(block, key);
    for (int j; j < 16; j++) {
        fwrite(block[i%4], 4, 1, outputFile);
        // int res = fputc(block[j%4][j/4], outputFile);
        // printf("RESULT %d\n", res);
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
