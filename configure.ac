AC_PREREQ([2.69])
AC_INIT([libdice], [0.1], [florian@n0la.org])
AM_INIT_AUTOMAKE([subdir-objects])
LT_INIT()
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

AC_PROG_LEX
AC_PROG_YACC

PKG_CHECK_MODULES([CMOCKA], [cmocka])

AC_CHECK_HEADER_STDBOOL()

AC_CHECK_FUNCS([arc4random arc4random_uniform strlcat strlcpy],,
   [PKG_CHECK_MODULES([BSD], [libbsd])])

AC_CONFIG_FILES([Makefile tests/Makefile])

AC_OUTPUT
