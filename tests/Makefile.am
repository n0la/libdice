check_PROGRAMS =	test_dice_simple_roll \
			test_dice_parse \
			test_dice_evaluate \
			test_expr_parse

AM_CFLAGS =	-I../lib ${CMOCKA_CFLAGS}
AM_LDFLAGS =	${CMOCKA_LIBS} ../libdice.la

TESTS =		$(check_PROGRAMS)
