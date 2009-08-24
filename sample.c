#include "acert.h"


ACERT_CASE(big_data_case)
{
	printf("exec big_data_case\n");
	int x = 5;
	acert(x == 5, "x is not equal 5");
	return 0;
}


ACERT_SUITE(code_suite)
{
	printf("code_suite\n");
	INCLUDE_ACERT_CASE(big_data_case);
}


void include_suites()
{
	printf("include_suites\n");
	INCLUDE_ACERT_SUITE(code_suite);
}

int main(int argc, const char **argv)
{
	include_suites();
	return acert_main(argc, argv);
}

