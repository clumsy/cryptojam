#include <utils.h>
#include "CuTest.h"

void TestStrhex(CuTest *tc) {
    CuAssertStrEquals(tc, "40", strhex("@"));
}

void TestHex(CuTest *tc) {
    CuAssertStrEquals(tc, "0040", hex("\0@", 2));
}

void TestUnhex(CuTest *tc) {
    CuAssertStrEquals(tc, "@", unhex("40", 2));
}

CuSuite* CuGetHexSuite(void) {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestStrhex);
    SUITE_ADD_TEST(suite, TestHex);
    SUITE_ADD_TEST(suite, TestUnhex);
    return suite;
}
