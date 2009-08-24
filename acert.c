#include "acert.h"

#include <stdlib.h>
#include <stdio.h>


/*
struct acert_suite
{
	const char *suite_name;
	const char *file_name;
	int file_line;
	acert_suite_func *func;
	struct acert_suite *next;
};
*/

static struct acert_case *g_tests = 0;
static const char *g_loading_suite = 0;


void include_acert_suite(const char *suite_name, acert_suite_func func)
{
	g_loading_suite = suite_name;
	func();
	g_loading_suite = 0;
}

void include_acert_case(acert_case_info_func info)
{
	struct acert_case *test = (struct acert_case *) \
				  malloc(sizeof(struct acert_case));
	info(test);
	test->suite_name = g_loading_suite;
	test->next = g_tests;
	g_tests = test;
}


int run_acert_cases()
{
	struct acert_case *test = g_tests;
	while (test) {
		test->func();
		test = test->next;
	}
	return 0;
}

int run_acert_case(const char *target)
{
	struct acert_case *test = g_tests;
	int result = 0;
	int found = 0;
	while (test) {
		if (strcmp(target, test->case_name) == 0
				|| strcmp(target, test->suite_name) == 0)
		{
			result = test->func();
			found = 1;
		}
		test = test->next;
	}

	if (!found) {
		printf("No matching testcase for '%s'\n", target);
		result = -1;
	}

	return result;
}

void print_acert_cases()
{
	struct acert_case *test = g_tests;
	while (test) {
		printf("%s\n", test->case_name);
		test = test->next;
	}
}


void print_usage(const char *bin)
{
	printf("%s [options] [<test-case>]\n", bin);
	printf("Options:\n");
	printf("\t-l\t--list\tList all available test cases.\n\n");
}

int acert_main(int argc, const char **argv)
{
	int result = 0;
	if (argc == 1) {
		result = run_acert_cases();
	} else if (argc > 2) {
		print_usage(argv[0]);
	} else if (strcmp(argv[1], "--list") == 0) {
		print_acert_cases();
	} else {
		result = run_acert_case(argv[1]);
	}
	return result;
}

