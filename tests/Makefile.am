bin_PROGRAMS =	test_dice_simple_roll \
		test_dice_parse \
		test_dice_evaluate

AM_CFLAGS =	-I../lib ${CMOCKA_CFLAGS}
AM_LDFLAGS =	${CMOCKA_LIBS} ../libdice.la

TESTS =		$(bin_PROGRAMS)
