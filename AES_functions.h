/* 
Header for Functions required to implement the AES cryptographic method.
Adopted from NIST AES standard.

Written by Will Puzella & Peter Kelly
For Carleton College Computer Science Comps 2024
*/

#include<stdio.h>


/* The transformation of the state in which a round key is combined
with the state. */
void AddRoundKey(u_int8_t state[4][4], u_int8_t roundKey[4][4]);

/* The block cipher specifed in this Standard with 128-bit keys. */
void AES_128(u_int8_t input[4][4],  u_int8_t key[]);

/* The block cipher specifed in this Standard with 192-bit keys. */
void AES_192(u_int8_t input[4][4],  u_int8_t key[]);

/* The block cipher specifed in this Standard with 256-bit keys. */
void AES_256(u_int8_t input[4][4],  u_int8_t key[]);

/* The transformation of blocks that underlies AES-128, AES-192,
and AES-256; the key schedule and the number of rounds are
parameters of the transformation. */
void Cipher(u_int8_t buffer[][4], int Nr, u_int8_t words[][4]);

/* The inverse of CIPHER() in which dw replaces w as the key schedule parameter. */
void EqinvCipher();

/* The inverse of CIPHER(). */
void InvCipher();

/* The inverse of MIXCOLUMNS().*/
void InvMixColumns();

/* The inverse of SBOX(). */
void InvSBox();

/* The inverse of SHIFTROWS(). */
void InvShiftRows();

/* The inverse of SUBBYTES(). */
void InvSubBytes();

/* The routine that generates the round keys from the key. */
void KeyExpansion(u_int8_t buffer[][4], u_int8_t key[], int Nk, int Nr);

/* The routine that generates the modifed round keys for the equivalent
inverse cipher. */
void KeyExpansionEIC();
/* The transformation of the state that takes all of the columns of the
state and mixes their data (independently of one another) to produce
new columns. */
void MixColumns(u_int8_t buffer[4][4]);
/* The transformation of words in which the four bytes of the word
are permuted cyclically. */
void RotWord(u_int8_t vec[4]);
/* The transformation of bytes defned by the S-box. */
u_int8_t SBox(u_int8_t a);
/* The transformation of the state in which the last three rows are
cyclically shifted by different offsets. */
void ShiftRows(u_int8_t buffer[][4]);
/* The transformation of the state that applies the S-box independently
to each byte of the state. */
void SubBytes();
/* The transformation of words in which the S-box is applied to each
of the four bytes of the word. */
void SubWord(u_int8_t vec[4]);
/* The transformation of bytes in which the polynomial representation
of the input byte is multiplied by x, modulo m(x), to produce the
polynomial representation of the output byte. */
u_int8_t XTimes(u_int8_t b);
