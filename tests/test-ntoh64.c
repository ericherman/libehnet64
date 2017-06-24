/* test-ntoh64.c
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
	union endian_test_u as_le, as_be;
	uint64_t val, hostv, actual;
	size_t i;
	char *end;

	val = (argc > 1) ? strtoull(argv[1], &end, 10) : 0x1122334455667788ULL;

	for (i = 0; i < 8; ++i) {
		as_le.bytes[i] = ((val & (0xFFULL << (8 * i))) >> (8 * i));
		as_be.bytes[7 - i] = as_le.bytes[i];
	}

	hostv = (as_be.n == val) ? as_be.n : as_le.n;

	actual = ntoh64(as_be.n);

	if (actual != hostv) {
		fprintf(stderr, "%0llx = ntoh64(%0llx), expected: %0llx\n",
			(unsigned long long)actual, (unsigned long long)as_be.n,
			(unsigned long long)hostv);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
