AM_YFLAGS =		-d
BUILT_SOURCES =		lib/dice_parse.h

lib_LTLIBRARIES =	libdice.la
libdice_la_SOURCES =	lib/dice.h \
			lib/dice.c \
			lib/dice_parse.y \
			lib/dice_lexer.l

AM_CFLAGS =		-Ilib

libdice_la_LIBADD =	${BSD_LIBS}

SUBDIRS	=		. tests
