cmake_minimum_required(VERSION 3.10)
project(test_memory_pool)

find_package(benchmark REQUIRED)

include_directories(include)
add_library( map_memory_pool "src/map_memory_pool.cc")

add_executable( test_memory_pool "test/test_memory_pool.cc" )
target_link_libraries(test_memory_pool pthread map_memory_pool benchmark)