#Makefile.am
#Copyright (C) 2017 Eric Herman <eric@freesa.org>
#
#This work is free software: you can redistribute it and/or modify it
#under the terms of the GNU Lesser General Public License as published by
#the Free Software Foundation, either version 3 of the License, or (at
#your option) any later version.
#
#This work is distributed in the hope that it will be useful, but WITHOUT
#ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
#License for more details.

# typical builds:
#CSTD_CFLAGS=-std=c89
DEBUG_CFLAGS=-ggdb -O2 -fomit-frame-pointer
NOISY_CFLAGS=-Wall -Wextra -pedantic -Werror
# if debugging, these flags may be better:
# CSTD_CFLAGS=-std=gnu11
# DEBUG_CFLAGS=-ggdb -O0 -D_GNU_SOURCE
# NOISY_CFLAGS=-Wall -Wextra -Werror

TESTS=$(check_PROGRAMS)
check_PROGRAMS=test-ntoh64 test-hton64

test_ntoh64_SOURCES=src/ehnet64.h tests/test-ntoh64.c
test_hton64_SOURCES=src/ehnet64.h tests/test-ntoh64.c

ACLOCAL_AMFLAGS=-I m4 --install

EXTRA_DIST=COPYING.GPL3 misc

AM_CFLAGS=$(CSTD_CFLAGS) $(DEBUG_CFLAGS) $(NOISY_CFLAGS)

# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

tidy:
	patch -Np1 -i misc/pre-tidy.patch
	$(LINDENT) \
		-T uint64_t \
		-T uint32_t \
		`find src tests -name '*.h' -o -name '*.c'`
	patch -Rp1 -i misc/pre-tidy.patch
