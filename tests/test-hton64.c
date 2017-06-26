/* test-hton64.c
Copyright (C) 2017 Eric Herman <eric@freesa.org>

This work is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This work is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "src/ehnet64.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

union endian_test_u {
	uint8_t bytes[8];
	uint64_t n;
};

int main(int argc, char **argv)
{
	union endian_test_u litend, bigend;
	uint64_t val, hostv, result;
	size_t i;
	int verbose;
	char *end;

	verbose = (argc > 1) ? atoi(argv[1]) : 0;
	val = (argc > 2) ? strtoull(argv[2], &end, 10) : 0x1122334455667788ULL;

	if (verbose) {
		printf("value  = %016llx (%llu)\n", (unsigned long long)val,
		       (unsigned long long)val);
	}

	for (i = 0; i < 8; ++i) {
		litend.bytes[i] = ((val & (0xFFULL << (8 * i))) >> (8 * i));
		bigend.bytes[7 - i] = litend.bytes[i];
	}

	if (verbose) {
		printf("litend = %016llx (%llu)\n",
		       (unsigned long long)litend.n,
		       (unsigned long long)litend.n);
	}
	if (verbose) {
		printf("bigend = %016llx (%llu)\n",
		       (unsigned long long)bigend.n,
		       (unsigned long long)bigend.n);
	}

	hostv = (bigend.n == val) ? bigend.n : litend.n;

	if (verbose) {
		printf("host v = %016llx (%llu)\n", (unsigned long long)hostv,
		       (unsigned long long)hostv);
	}

	result = hton64(hostv);
	if (verbose) {
		printf("result = hton64(%016llx)\n", (unsigned long long)hostv);
		printf("result = %016llx (%llu)\n", (unsigned long long)result,
		       (unsigned long long)result);
	}

	if (result != bigend.n) {
		fprintf(stderr, "%0llx = hton64(%016llx), expected: %016llx\n",
			(unsigned long long)result, (unsigned long long)hostv,
			(unsigned long long)bigend.n);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
