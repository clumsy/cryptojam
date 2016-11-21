#include <sha2.h>
#include <utils.h>
#include <string.h>
#include "CuTest.h"

void TestSha2(CuTest *tc) {
    char* value = "A Test";
    CuAssertStrEquals(tc, "3445f19bb7bb8de4bdad54ec2871b1ca5a761de0115f6f741e298e4cc8f633ee", hex(sha2(value, strlen(value)), 32));
}

CuSuite* CuGetSha2Suite(void) {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestSha2);
    return suite;
}
