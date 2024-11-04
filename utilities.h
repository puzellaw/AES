#include <stdlib.h>
#include <stdio.h>

/* Function that computes a Galois finite field multiplication against 02 */
u_int8_t XTimes(u_int8_t b);

/* Function to add round key to transformed state */
void AddRoundKey(u_int8_t state[4][4], u_int8_t roundKey[4][4]);

/* Helper function for the key expansion step */
void Rcon(u_int8_t buffer[4], int j);

/* Finite field multiplication of two values */
u_int8_t Multiply(u_int8_t a, u_int8_t b);

/* Encrption helper function that subs a whole row using an Sbox on each term*/
void SubWord(u_int8_t vec[4]); 

/* Open File helper function */
FILE *openFile(char *file_name);

/* Open file helperfunction with write capabilities */
FILE *openFileWrite(char *file_name);

/* Xor of two blocks */
void XOR(u_int8_t a[][4], u_int8_t b[][4]);