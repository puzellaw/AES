#include <stdlib.h>
#include <stdio.h>

/*
* Computes a Galois finite field multiplication between b and 0x2
* Args: u_int8_t b
* Return: u_int8_t result
*/
u_int8_t XTimes(u_int8_t b);

/* 
* XOR round key with the state
* Args: u_int8_t state[4][4], u_int8_t roundKey[4][4]
* Return: void
*/
void AddRoundKey(u_int8_t state[4][4], u_int8_t roundKey[4][4]);

/* 
* Helper function for key expansion that puts the jth round constant in the buffer
* Args: u_int8_t buffer[4], int j
* Return: void
*/
void Rcon(u_int8_t buffer[4], int j);

/* 
* Finite field multiplication of two 8-bit values
* Args: u_int8_t a, u_int8_t b
* Return: u_int8_t result
*/
u_int8_t Multiply(u_int8_t a, u_int8_t b);

/* 
* Helper function that subs a whole row using an Sbox on each term
* Args: u_int8_t vec
* Return: void
*/
void SubWord(u_int8_t vec[4]); 

/* 
* Open File helper function with read capabilites
* Args: char *file_name
* Return: File* pointer
*/
FILE *openFile(char *file_name);

/* 
* Open file helper function with write capabilities
* Args: char* file_name
* Return File* pointer
*/
FILE *openFileWrite(char *file_name);

/* 
* XOR two blocks and place result in a
* Args: u_int8_t a[4][4], u_int8_t b[4][4]
* Return void
*/
void XOR(u_int8_t a[][4], u_int8_t b[][4]);