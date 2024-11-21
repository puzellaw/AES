# An Implementation of the Advanced Encryption Standard
 ***Written by Peter Kelly & Will Puzella***  
Carleton College, Computer Science, Fall Comps 2024

This project was the culminating senior thesis for Will Puzella and Peter Kelly, where they implemented the Advanced Encryption Standard with three different block cipher modes (ECB, CBC, & GCM). A further description of the project can be found at the link below. 

[Full Project Write-up](https://docs.google.com/document/d/e/2PACX-1vRGgC6vZzd487ZTYaiDn7aN-Bs_wYo5Czh3vawfzxOB2f_ZgL0ERrotfO2ej3H7fcIqcX-0wUDyJ1JY/pub) 

## Installation
All Code required to run the files is located within the git repository. All libraries used are included in the standard C installation. 

**Required Libraries**
- stdio.h
- stdlib.h
- assert.h
- stdbool.h
- string.h
- time.h 

### Compilation
To compile the source code go to directory that code was dowloaded to and type `make`. This will execute the make file which should compile the code for you. 

If you instead would like to compile the testing suite type `make test`. This will compile a testing executable. 

## Running our encryption software. 
To run the encryption/decryption software run:

`./PK_AES -E/-D -I [input file directory] -O [Output File directory] [additional arguments]`

The style of the arguments is such that they can be put in any order as long as the format is: 

 `<argument tag> | <argument input> | <argument tag>`

This can be seen in the sample command above. 

**All Arguments**
- `-I [input file]` Input file
- `-O [output file]` Output file
- `-D` Decrypt mode (by default it will encrypt a file)
- `-E` Encrypts in Electronic Code Book (ECB) block cipher mode
- `-C` Encrypts in Counter Block Cipher (CBC) mode
- `-G` Encrypts in Galois Counter Mode (GCM)

A tag of `-I` and `-O` is required for all running of `PK_AES`. Additionally `-E`, `-C`, or `-G`must be chosen to indicate which block cipher mode is being used. Each block cipher mode has the additional arguments below. **Unless marked otherwise all arguments below are required for their respective block cipher mode.**

**`-E` Arguments**
- `-K [Key String]` Input string can either be in hex 0xXXXXX format or a regular string. Key needs to be 128, 192, or 256 bits long. 

**`-C` Arguments**
- `-K [Key String]` Input string can either be in hex 0xXXXXX... format or a regular string. Key needs to be 128, 192, or 256 bits long. 
- `-V [Initialization Vector]` Input string can either be in hex 0xXXXXX... format or a regular string. Initialization vector needs to be 128 bits long.  

**`-G` Arguments**
- `-K [Key String]` Input string can either be in hex 0xXXXXX format or a regular string. Key needs to be 128, 192, or 256 bits long. 
- `-v [seed for n]` (Optional) Input string can either be in hex 0xXXXXX... format or a regular string. n seed needs to be 128 bits long.  

