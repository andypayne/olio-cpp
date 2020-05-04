cmake_minimum_required (VERSION 3.17)
project (stk CXX)
# C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()
add_subdirectory(googletest)

set(headers
  stk.hpp
)

#add_library(stk STATIC ${headers})
add_library(stk INTERFACE)
add_subdirectory(test)
target_include_directories (stk INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# -fsanitize=address for AddressSanitizer memory leak reporting
# -g for debugging info
# -O1 for basic optimizations -- can help with more complicated asan reporting
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
#add_executable(stk main.cpp)
#target_include_directories (stk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

