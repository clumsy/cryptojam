#include <sha1.h>
#include <utils.h>
#include <string.h>
#include <stdio.h>
#include "CuTest.h"

void TestSha1(CuTest *tc) {
    char* value = "A Test";
    CuAssertStrEquals(tc, "8f0c0855915633e4a7de19468b3874c8901df043", hex(sha1(value, strlen(value)), 20));
}

CuSuite* CuGetSha1Suite(void) {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestSha1);
    return suite;
}
