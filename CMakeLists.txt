cmake_minimum_required(VERSION 3.14)
project(Sorting-Algorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/common)

# array_bench
add_executable(array_bench apps/array_bench/main.cpp)
target_include_directories(array_bench PRIVATE ${COMMON_DIR} ${INCLUDE_DIR})
find_package(benchmark QUIET)
if(benchmark_FOUND)
  target_link_libraries(array_bench PRIVATE benchmark::benchmark)
endif()

# list_bench
set(LIST_BENCH_SOURCES
  apps/list_bench/main.cpp
  apps/list_bench/Message.cpp
  apps/list_bench/myTime.cpp
  apps/list_bench/NodeList.cpp
  apps/list_bench/stringbin.cpp
)
add_executable(list_bench ${LIST_BENCH_SOURCES})
target_include_directories(list_bench PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/apps/list_bench
  ${INCLUDE_DIR}
  ${INCLUDE_DIR}/sorting/list
)
find_package(benchmark QUIET)
if(benchmark_FOUND)
  target_link_libraries(list_bench PRIVATE benchmark::benchmark)
endif()

# Google Test (for strategy_bench)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
set(GTEST_USE_OWN_CMAKE_BUILD_DIR OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# strategy_bench
set(STRATEGY_BENCH_SOURCES
  apps/strategy_bench/main.cpp
  apps/strategy_bench/tests.hpp
)
add_executable(strategy_bench ${STRATEGY_BENCH_SOURCES})
target_include_directories(strategy_bench PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/apps/strategy_bench
  ${INCLUDE_DIR}
)
target_link_libraries(strategy_bench PRIVATE GTest::gtest)
find_package(benchmark QUIET)
if(benchmark_FOUND)
  target_link_libraries(strategy_bench PRIVATE benchmark::benchmark)
endif()
