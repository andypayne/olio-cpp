cmake_minimum_required(VERSION 3.17)
project (stk_tests CXX)

set(sources
  stk_tests.cpp
)

add_executable(stk_tests ${sources})
target_link_libraries(stk_tests PUBLIC
  gtest_main
)

add_test(
  NAME stk_tests
  COMMAND stk_tests
)
