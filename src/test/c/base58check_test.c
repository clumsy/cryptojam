#include <stdio.h>
#include <base58.h>
#include <base58check.h>
#include <utils.h>
#include <string.h>
#include "CuTest.h"

void TestBase58CheckEncode(CuTest *tc) {
    char* value = "\x01\x09\x66\x77\x60\x06\x95\x3D\x55\x67\x43\x9E\x5E\x39\xF8\x6A\x0D\x27\x3B\xEE";
    const char* result = base58check_encode(bitcoin_address, value, 20);
    CuAssertStrEquals(tc, "16UwLL9Risc3QfPqBUvKofHmBQ7wMtjvM", result);
}

CuSuite* CuGetBase58CheckSuite(void) {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestBase58CheckEncode);
    return suite;
}
