#include "acert.h"


ACERT_CASE(success_case)
{
	int x = 5;
	acert(x == 5, "x is %d, not equal to 5", x);
	return 0;
}

ACERT_CASE(failure_case)
{
	int x = 7;
	acert(x == 5, "x is %d, not equal to 5", x);
	return 0;
}

ACERT_CASE(segfault_case)
{
	int *p = 0;
	*p = 5;
	return 0;
}


ACERT_SUITE(code_suite)
{
	INCLUDE_ACERT_CASE(success_case);
	INCLUDE_ACERT_CASE(failure_case);
	INCLUDE_ACERT_CASE(segfault_case);
}


void include_suites()
{
	INCLUDE_ACERT_SUITE(code_suite);
}

int main(int argc, const char **argv)
{
	include_suites();
	return acert_main(argc, argv);
}

