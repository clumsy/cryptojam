#include <stdio.h>
#include "CuTest.h"

CuSuite* CuGetBase58Suite();
CuSuite* CuGetBase58CheckSuite();
CuSuite* CuGetSha1Suite();
CuSuite* CuGetSha2Suite();
CuSuite* CuGetHexSuite();

void RunAllTests(void) {
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, CuGetBase58Suite());
	CuSuiteAddSuite(suite, CuGetBase58CheckSuite());
	CuSuiteAddSuite(suite, CuGetSha1Suite());
	CuSuiteAddSuite(suite, CuGetSha2Suite());
	CuSuiteAddSuite(suite, CuGetHexSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main(void) {
	RunAllTests();
}
