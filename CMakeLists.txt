cmake_minimum_required(VERSION 3.10)
project(test_memory_pool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE "Release")

find_package(benchmark REQUIRED)

include_directories(include)
add_library( memory_pool "src/memory_pool/map_memory_pool.cc"  "src/memory_pool/pmr_memory_pool.cc")
add_library( timer "src/timer/timer.cc")

add_executable( test_memory_pool "test/test_memory_pool.cc" )
target_link_libraries(test_memory_pool pthread memory_pool benchmark)

add_executable( test_timer "test/test_timer.cc" )
target_link_libraries(test_timer pthread timer benchmark)

add_executable( test_timer_memory_pool "test/test_timer_memory_pool.cc" )
target_link_libraries(test_timer_memory_pool pthread timer memory_pool benchmark)