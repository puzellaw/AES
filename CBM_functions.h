#ifndef CBM_functions
#define CBM_functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/* 
 * Open file function that takes in a file name as a char* and opens the file in 
 * byte mode; reurning an active file stream pointer
 * Args: char *file_name
 * Return: FILE* pointer
 */
FILE *openFile(char *file_name);

/* 
 * Open file function that opens the file in write bytes mode. 
 * Args: char *file_name
 * Return: FILE* pointer
 */
 FILE *openFileWrite(char *file_name);

/* 
 * Encrypts file using CBC block ciphering. 
 * Args: FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *iv
 * Return: u_int8_t *
 */
int encryptFile_CBC(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *iv, int encryptionScheme);

/* 
 * Encrypts file using GCM block ciphering. 
 * Args: FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *n
 * Return: u_int8_t *
 */
int encryptFile_GCM(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *n, int encryptionScheme);

/* 
 * Encrypts file using ECM block ciphering. 
 * Args: FILE *inputFile, FILE *outputFile, u_int8_t *key
 * Return: u_int8_t *
 */
int encryptFile_ECB(FILE *inputFile, FILE *outputFile, u_int8_t *key, int encryptionScheme);

/* 
 * Decrypts file using GCM block ciphering. 
 * Args: FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *n
 * Return: u_int8_t *
 */
int decryptFile_GCM(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *n, u_int8_t* tag, int encryptionScheme);
/* 
 * Decrypts file using CBC block ciphering. 
 * Args: FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *iv
 * Return: u_int8_t *
 */
int decryptFile_CBC(FILE *inputFile, FILE *outputFile, u_int8_t *key, u_int8_t *iv, int encryptionScheme);

/* 
 * Decrypts file using ECB block ciphering. 
 * Args: FILE *inputFile, FILE *outputFile, u_int8_t *key
 * Return: u_int8_t *
 */
int decryptFile_ECB(FILE *inputFile, FILE *outputFile, u_int8_t *key, int encryptionScheme);

/* 
 * Utility function for blockMult() function, takes a byte and returns the bit at the given index. Zero Indexed. 
 * Args: u_int8_t ch, int index
 * Return: int
 */
int getBit(u_int8_t ch, int index);

/* 
 * Utility function for blockMult() function, takes a block and shifts it to the right by one bit.  
 * Args: u_int8_t blocks[16]
 * Return: void
 */
void moveRight(u_int8_t blocks[16]);

/* 
 * Galois finite field multiplaction function. Saves the resulting product into buffer argument.
 * Args: u_int8_t buffer[16], u_int8_t block1[16], u_int8_t block2[16]
 * Return: void
 */
void blockMult(u_int8_t buffer[16], u_int8_t block1[16], u_int8_t block2[16]);


#endif