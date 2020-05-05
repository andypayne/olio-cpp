cmake_minimum_required (VERSION 3.17)
project (lst CXX)
# C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

enable_testing()
add_subdirectory(googletest)

set(headers
  lst.hpp
)

add_library(lst INTERFACE)
add_subdirectory(test)
target_include_directories (lst INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

