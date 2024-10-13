/*
#include "unity.h"
#include "file_to_test.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_should_doBlahAndBlah(void) {
    //test stuff
}

void test_function_should_doAlsoDoBlah(void) {
    //more test stuff
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_function_should_doAlsoDoBlah);
    return UNITY_END();
}
*/ 

// TO TEST: gcc function_testing.c  ./Unity-master/src/unity.c -o Testing

#include "Unity-master/src/unity.h"
#include "AES_functions.h"
#include "encryption.c"
#include "key_expansion_EIC.c"
#include "inv_cipher.c"
#include "inv_sub_bytes.c"
#include "inv_shift_rows.c"

#define debugextra 1

void setUp(void) {
    //set up any required variables
}

void tearDown(void) {

}

void test_AddRoundKey_correctOutput(void) { //Done: Passing as of 10/9/24
    u_int8_t input[4][4] = {{0x32, 0x88, 0x31, 0xe0}, 
                            {0x43, 0x5a, 0x31, 0x37},
                            {0xf6, 0x30, 0x98, 0x07},
                            {0xa8, 0x8d, 0xa2, 0x34}};
    u_int8_t expandedKey[4][4] = {{0x2b,0x7e,0x15,0x16},
                                {0x28,0xae,0xd2,0xa6},
                                {0xab,0xf7,0x15,0x88},
                                {0x09,0xcf,0x4f,0x3c}};
    u_int8_t expectedOutput[4][4] = {{0x19, 0xa0, 0x9a, 0xe9}, 
                                     {0x3d, 0xf4, 0xc6, 0xf8},
                                     {0xe3, 0xe2, 0x8d, 0x48},
                                     {0xbe, 0x2b, 0x2a, 0x08}};
    AddRoundKey(input, expandedKey);
    for (int i=0; i < 4; i++) {
        if (debugextra) TEST_MESSAGE("Checking Row");
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedOutput[i], input[i], 4);
    }
}

void test_AES_128_correctOutput(void) {
    u_int8_t input[4][4] = {{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00}};
    u_int8_t key [] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    AES_128(input, key);
    u_int8_t expectedOutput[4][4]= {
    {0xa1,0x87,0x89,0x38},
    {0xf6,0x7d,0x64,0xbf},
    {0x25,0x5f,0x48,0xc9},
    {0x8c,0xcd,0x45,0x2c}};
    for (int i=0; i < 4; i++) {
        if (debugextra) TEST_MESSAGE("Checking Row");
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedOutput[i], input[i], 4);
    }
}

void test_AES_192_correctOutput(void) {
    u_int8_t input[4][4] = {{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00},{0x00, 0x00, 0x00, 0x00}};
    u_int8_t key [] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    AES_192(input, key);
    u_int8_t expectedOutput[4][4]= {
    {0xdd,0x14,0x56,0xc4},
    {0x8a,0x23,0xec,0x08},
    {0x49,0x1c,0xce,0x89},
    {0x35,0xbf,0xe4,0xfb}};
    for (int i=0; i < 4; i++) {
        if (debugextra) TEST_MESSAGE("Checking Row");
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedOutput[i], input[i], 4);
    }
}

void test_AES_256_correctOutput(void) {

}

void test_Cipher_correctOutput(void) {

}

void test_EqinvCipher_correctOutput(void) {

} 

void test_InvCipher_correctOutput(void) {
    // u_int8_t expectedOutput[4][4] = {{0x32, 0x88, 0x31, 0xe0}, 
    //                                  {0x43, 0x5a, 0x31, 0x37},
    //                                  {0xf6, 0x30, 0x98, 0x07},
    //                                  {0xa8, 0x8d, 0xa2, 0x34}};
    // u_int8_t input[4][4] = {{0x39, 0x02, 0xdc, 0x19}, 
    //                         {0x25, 0xdc, 0x11, 0x6a},
    //                         {0x84, 0x09, 0x85, 0x0b},
    //                         {0x1d, 0xfb, 0x97, 0x32}};
    u_int8_t expectedOutput[4][4] = {{0x32, 0x43, 0xf6, 0xa8}, 
                                     {0x88, 0x5a, 0x30, 0x8d},
                                     {0x31, 0x31, 0x98, 0xa2},
                                     {0xe0, 0x37, 0x07, 0x34}};
    u_int8_t input[4][4] = {{0x39, 0x25, 0x84, 0x1d}, 
                            {0x02, 0xdc, 0x09, 0xfb},
                            {0xdc, 0x11, 0x85, 0x97},
                            {0x19, 0x6a, 0x0b, 0x32}};
    u_int8_t buffer[44][4];
    u_int8_t expandedKey[] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
    KeyExpansionEIC(buffer, expandedKey, 4, 10);
    InvCipher(input, 10, buffer);
    for (int i = 0; i < 4; i++) {
        if (debugextra) TEST_MESSAGE("Checking Row");
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedOutput[i], input[i], 4);
    }
    
}

void test_InvMixColumns_correctOutput(void) {
    u_int8_t expectedOutput[4][4] = {{0xd4,0xe0,0xb8,0x1e},
                                     {0xbf,0xb4,0x41,0x27},
                                     {0x5d,0x52,0x11,0x98},
                                     {0x30,0xae,0xf1,0xe5}};
    u_int8_t input[4][4] = {{0x04,0xe0,0x48,0x28},
                            {0x66,0xcb,0xf8,0x06},
                            {0x81,0x19,0xd3,0x26},
                            {0xe5,0x9a,0x7a,0x4c}};
    InvMixColumns(input);
    for (int i = 0; i < 4; i++) {
        if (debugextra) TEST_MESSAGE("Checking Row");
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedOutput[i], input[i], 4);
    }
}

void test_InvSBox_correctOutput(void) {

}

void test_InvShiftRows_correctOutput(void) {
    u_int8_t input[][4] = {{0x00, 0x01, 0x02, 0x03}, {0x10, 0x11, 0x12, 0x13}, {0x20, 0x21, 0x22, 0x23}, {0x30, 0x31, 0x32, 0x33}};
    u_int8_t expectedOutput[][4] = {{0x00, 0x01, 0x02, 0x03}, {0x13, 0x10, 0x11, 0x12}, {0x22, 0x23, 0x20, 0x21}, {0x31, 0x32, 0x33, 0x30}};
    InvShiftRows(input);
    for (int i = 0; i < 4; i++) {
        if (debugextra) TEST_MESSAGE("Checking Row");
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedOutput[i], input[i], 4);
    }
}

void test_InvSubBytes_correctOutput(void) {
    u_int8_t input = 0x78;
    u_int8_t correctOut = 0xc1;
    TEST_ASSERT_EQUAL_MESSAGE(correctOut, InvSubBytes(input), "Output should have been 0xc1");
}

void test_KeyExpension_correctOutput(void) {
    
}

void test_KeyExpansionEIC_correctOutput(void) {

}

void test_MixColumns_correctOutput(void) { // Done: Passing as of 10/7/24
    u_int8_t input[4][4] = {{0xd4,0xe0,0xb8,0x1e},
                            {0xbf,0xb4,0x41,0x27},
                            {0x5d,0x52,0x11,0x98},
                            {0x30,0xae,0xf1,0xe5}};
    u_int8_t expectedOutput[4][4] = {{0x04,0xe0,0x48,0x28},
                                     {0x66,0xcb,0xf8,0x06},
                                     {0x81,0x19,0xd3,0x26},
                                     {0xe5,0x9a,0x7a,0x4c}};
    MixColumns(input);
    for (int i = 0; i < 4; i++) {
        if (debugextra) TEST_MESSAGE("Checking Row");
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedOutput[i], input[i], 4);
    }
}

void test_RotWord_correctOutput(void) { //Done: Passing as of 10/2/24
    u_int8_t input[4] = {1,2,3,4};
    u_int8_t expected[4] = {2,3,4,1};
    RotWord(input);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected, input, 4, "Output should have been [2,3,4,1]\n");
}

void test_SBox_correctOutput(void) { //Done: Passing as of 10/2/24
    u_int8_t input = 0x78;
    u_int8_t correctOut = 0xbc;
    TEST_ASSERT_EQUAL_MESSAGE(correctOut, SBox(input), "Output should have been 0xBC");
}

void test_ShiftRows_correctOutput(void) {

}

void test_SubBytes_correctOutput(void) { 
    
}

void test_SubWord_correctOutput(void) { //Done: Passing as of 10/2/24
    u_int8_t input[4] = {0x8a, 0x5f , 0x27, 0xff};
    u_int8_t expected[4] = {0x7e, 0xcf, 0xcc, 0x16};
    SubWord(input);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected, input, 4, "Output Should have been [0x7e, 0xcf,0x77, 0x16].\n");
}

void test_XTimes_correctOutput(void) { //Done: Passing as of 10/7/24
    u_int8_t input= 0x57;
    u_int8_t expected = 0xae;
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected, XTimes(input), "Expected output as defined in manuel is 0xfe");

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_SBox_correctOutput);
    RUN_TEST(test_SubWord_correctOutput);
    RUN_TEST(test_RotWord_correctOutput);
    RUN_TEST(test_SubWord_correctOutput);
    RUN_TEST(test_AddRoundKey_correctOutput);
    RUN_TEST(test_MixColumns_correctOutput);
    RUN_TEST(test_InvMixColumns_correctOutput);
    RUN_TEST(test_InvSubBytes_correctOutput);
    RUN_TEST(test_XTimes_correctOutput);
    RUN_TEST(test_AES_192_correctOutput);
    RUN_TEST(test_AES_128_correctOutput);
    RUN_TEST(test_InvCipher_correctOutput);
    RUN_TEST(test_InvShiftRows_correctOutput);
    return UNITY_END();
}