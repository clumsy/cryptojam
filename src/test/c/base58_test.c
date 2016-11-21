#include <stdio.h>
#include <base58.h>
#include <string.h>
#include <utils.h>
#include "CuTest.h"

void TestBase58Encode(CuTest *tc) {
    char* payload1 = "3429289555";
    CuAssertStrEquals(tc, "3srK5HZhkvBbfJ", base58_encode(payload1, strlen(payload1)));
    char* payload2 = "This is a test string";
    CuAssertStrEquals(tc, "6C3QbYGU2SHs7TronoE7Fb6fH2mgz", base58_encode(payload2, strlen(payload2)));
}

CuSuite* CuGetBase58Suite(void) {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestBase58Encode);
    return suite;
}
