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
#include "sbox.c"
#include "sub_word.c"
#include "rot_word.c"
#include "x_times.c"
#include "add_round_key.c"
#include "mix_columns.c"

#define debugextra 0

void setUp(void) {
    //set up any required variables
}

void tearDown(void) {

}

void test_AddRoundKey_correctOutput(void) { //Done: Passing as of 10/6/24
    u_int8_t input[4][4] = {{0x6a, 0xef, 0xff, 0x77}, 
                            {0x88, 0x89, 0x77, 0x66},
                            {0x66, 0x22, 0x84, 0x92},
                            {0x85, 0x78, 0xbd, 0xe7}};
    u_int32_t expandedKey[4] = {0x10141819,
                                0xaabbccdd,
                                0x2b7c8910,
                                0x112c048f};
    u_int8_t expectedOutput[4][4] = {{0x7a, 0xfb, 0xe7, 0x6e}, 
                                     {0x22, 0x33, 0xbb, 0xbb},
                                     {0x6d, 0x5e, 0x0d, 0x32},
                                     {0x94, 0x54, 0xb9, 0x68}};
    AddRoundKey(input, expandedKey);
    for (int i; i < 4; i++) {
        TEST_ASSERT_EQUAL_UINT8_ARRAY(expectedOutput[i], input[i], 4);
    }
}

void test_AES_128_correctOutput(void) {

}

void test_AES_192_correctOutput(void) {

}

void test_AES_256_correctOutput(void) {

}

void test_Cipher_correctOutput(void) {

}

void test_EqinvCipher_correctOutput(void) {

} 

void test_InvCipher_correctOutput(void) {

}

void test_InvMixColumns_correctOutput(void) {

}

void test_InvSBox_correctOutput(void) {

}

void test_InvShiftRows_correctOutput(void) {

}

void test_InvSubBytes_correctOutput(void) {

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
    RUN_TEST(test_XTimes_correctOutput);
    return UNITY_END();
}