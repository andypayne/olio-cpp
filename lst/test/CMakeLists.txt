cmake_minimum_required(VERSION 3.17)
project (lst_tests CXX)

set(sources
  lst_tests.cpp
)

add_executable(lst_tests ${sources})
target_link_libraries(lst_tests PUBLIC
  gtest_main
)

add_test(
  NAME lst_tests
  COMMAND lst_tests
)
