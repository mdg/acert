#ifndef ACERT_H
#define ACERT_H

#include <stdlib.h>
#include <stdio.h>



#define acert(expression, text)


/** Primary macro for declaring test cases. */
#define ACERT_CASE(case_func) \
	int case_func(); \
	void case_func##_info(struct acert_case *); \
	void case_func##_info(struct acert_case *test) { \
		test->case_name = #case_func; \
		test->file_name = __FILE__; \
		test->file_line = __LINE__; \
		test->func = case_func; \
		} \
	int case_func()

#define ACERT_SUITE(suite_func) \
	int suite_func(); \
	int suite_func##_info(); \
	int suite_func##_info() \
		{ printf("suite %s %s %d", #suite_func, __FILE__, __LINE__); } \
	int suite_func()

#define INCLUDE_ACERT_SUITE(suite) \
	include_acert_suite(#suite, suite)

#define INCLUDE_ACERT_CASE(func) \
	include_acert_case(func##_info)


/** Typedef for the acert case & suite functions. */
typedef int acert_case_func();
typedef int acert_suite_func();


struct acert_case
{
	const char *suite_name;
	const char *case_name;
	const char *file_name;
	int file_line;
	acert_case_func *func;
	// acert_case_info_func *info;
	struct acert_case *next;
};


typedef void acert_case_info_func(struct acert_case *);
typedef void acert_suite_info_func();


/**
 * Register the acert test case function.
 */
void include_acert_suite(const char *suite_name, acert_suite_func func);

void include_acert_case(acert_case_info_func info);


/**
 * Run a specific test case.
 */
int run_acert_case(const char *casename);
/**
 * Run all test cases.
 */
int run_acert_cases();
/**
 * Print all test cases to stdout.
 */
void print_acert_cases();

int acert_main(int argc, const char **argv);

#endif

