CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

SET(TESTS
  "test_dice_evaluate"
  "test_dice_fudge"
  "test_dice_parse"
  "test_dice_simple_roll"
  "test_expr_parse"
  )

INCLUDE_DIRECTORIES(
  "${CMAKE_CURRENT_SOURCE_DIR}/../lib/"
  ${CMOCKA_INCLUDE_DIRS}
  )

FOREACH(TEST ${TESTS})
  ADD_EXECUTABLE(${TEST} ${TEST}.c)
  TARGET_LINK_LIBRARIES(${TEST} dice ${CMOCKA_LIBRARIES})
  ADD_TEST(NAME "${TEST}" COMMAND ${TEST})
ENDFOREACH()
