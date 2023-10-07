cmake_minimum_required(VERSION 3.10)
project(test_memory_pool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(benchmark REQUIRED)

include_directories(include)
add_library( memory_pool "src/memory_pool/map_memory_pool.cc"  "src/memory_pool/pmr_memory_pool.cc")
add_library( timer_manager "src/timer_manager/timer.cc"  "src/timer_manager/timer_manager.cc")

add_executable( test_memory_pool "test/test_memory_pool.cc" )
target_link_libraries(test_memory_pool pthread memory_pool benchmark)