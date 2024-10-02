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

void setUp(void) {
    //set up any required variables
}

void tearDown(void) {

}

void test_AddRoundKey_correctOutput(void) {

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

void test_MixColumns_correctOutput(void) {

}

void test_RotWord_correctOutput(void) {
    
}

void test_SBox_correctOutput(void) {
    u_int8_t input = 0x78;
    u_int8_t correctOut = 0xbc;
    TEST_ASSERT_EQUAL_MESSAGE(correctOut, sbox(input), "Output should have been 0xBC");
}

void test_ShiftRows_correctOutput(void) {

}

void test_SubBytes_correctOutput(void) {

}

void test_SubWord_correctOutput(void) {

}

void test_XTimes_correctOutput(void) {
    
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_SBox_correctOutput);
    return UNITY_END();
}