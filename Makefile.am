AM_YFLAGS =		-d
BUILT_SOURCES =		lib/dice_parse.h

lib_LTLIBRARIES =	libdice.la
libdice_la_SOURCES =	lib/dice_lexer.l \
			lib/dice_parse.y \
			lib/dice.h \
			lib/dice.c \
			lib/diceexpr.c

include_HEADERS =	lib/dice.h

AM_CFLAGS =		-Ilib

libdice_la_LIBADD =	${BSD_LIBS}

SUBDIRS	=		. tests
