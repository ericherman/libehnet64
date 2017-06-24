#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libehnet64], [1.0.0], [eric@freesa.org])
AC_CONFIG_SRCDIR([src/ehnet64.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AC_USE_SYSTEM_EXTENSIONS

# Checks for programs.
AC_PROG_CC
AC_PROG_LN_S

# Checks for header files.
AC_CHECK_HEADERS([byteswap.h endian.h stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([bswap_32 bswap_64])

AM_INIT_AUTOMAKE([subdir-objects -Werror -Wall])
AM_PROG_AR
LT_INIT

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
