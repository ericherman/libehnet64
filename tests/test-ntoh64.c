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
	unsigned char bytes[4];
	uint32_t n;
};

int main(void)
{
	union endian_test_u et = { {0x11, 0x22, 0x33, 0x44} };
	uint32_t value = 0x11 << 3 | 0x22 << 2 | 0x33 << 1 | 0x44;
	int big_endian = (et.n == value);
	uint64_t as_le = 0x554E49584C4F5645;
	uint64_t as_be = 0x45564F4C58494E55;
	uint64_t hostv = big_endian ? as_be : as_le;
	uint64_t actual;

	actual = hton64(hostv);

	if (actual != as_be) {
		fprintf(stderr, "%0llx = hton64(%0llx)",
			(unsigned long long)actual, (unsigned long long)hostv);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
