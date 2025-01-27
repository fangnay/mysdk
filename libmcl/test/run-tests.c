/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
# include <io.h>
#else
# include <unistd.h>
#endif

#include "uv.h"
#include "runner.h"
#include "task.h"

/* Actual tests and helpers are defined in test-list.h */
#include "test-list.h"


static int maybe_run_test(int argc, char **argv) {
	if (strcmp(argv[1], "--list") == 0) {
		print_tests(stdout);
		return 0;
	}

	if (strcmp(argv[1], "spawn_helper") == 0) {
		printf("hello world\n");
		return 42;
	}

	return run_test(argv[1], 1, 1);
}


int main(int argc, char **argv) {
	if (platform_init(argc, argv))
		return EXIT_FAILURE;

	argv = uv_setup_args(argc, argv);
	return run_test_hello();

	switch (argc) {
	case 1: return run_tests(0);
	case 2: return maybe_run_test(argc, argv);
	case 3: return run_test_part(argv[1], argv[2]);
	case 4: return maybe_run_test(argc, argv);
	default:
		fprintf(stderr, "Too many arguments.\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
