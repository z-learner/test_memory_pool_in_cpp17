#include <benchmark/benchmark.h>

#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "memory_pool/map_memory_pool.hpp"

void map_memory_pool_work_thread(size_t malloc_size) {
  size_t count = 2000;
  while (count-- > 0) {
    char* ptr =
        map_memory_pool::MemoryPool::GetMemoryPool().malloc(malloc_size);
    if (ptr == nullptr) {
      std::cout << "Get nullptr from MemoryPool" << std::endl;
    }
    // std::cout << "map_memory_pool memory point "
    //           << reinterpret_cast<size_t>(ptr) << std::endl;
    std::memset(ptr, 0, malloc_size);

    map_memory_pool::MemoryPool::GetMemoryPool().free(ptr, malloc_size);
  }
}

void malloc_work_thread(size_t malloc_size) {
  size_t count = 2000;
  while (count-- > 0) {
    char* ptr = reinterpret_cast<char*>(malloc(malloc_size));
    if (ptr == nullptr) {
      std::cout << "Get nullptr from MemoryPool" << std::endl;
    }
    // std::cout << "malloc memory point " << reinterpret_cast<size_t>(ptr)
    //           << std::endl;
    std::memset(ptr, 0, malloc_size);

    free(ptr);
  }
}

void vector_work_thread(size_t malloc_size) {
  size_t count = 2000;

  while (count-- > 0) {
    std::vector<char> data(malloc_size);
    // std::cout << "vector memory point " <<
    // reinterpret_cast<size_t>(data.data())
    //           << std::endl;

    std::memset(data.data(), 0, malloc_size);
  }
}

static void benchmark_map_memory_pool_work_thread(benchmark::State& state) {
  for (auto _ : state) {
    std::thread thread0(&map_memory_pool_work_thread, 50);
    std::thread thread1(&map_memory_pool_work_thread, 50);
    std::thread thread2(&map_memory_pool_work_thread, 100);
    std::thread thread3(&map_memory_pool_work_thread, 100);
    std::thread thread4(&map_memory_pool_work_thread, 100);
    std::thread thread5(&map_memory_pool_work_thread, 500);
    std::thread thread6(&map_memory_pool_work_thread, 500);
    std::thread thread7(&map_memory_pool_work_thread, 500);
    std::thread thread8(&map_memory_pool_work_thread, 1000);
    std::thread thread9(&map_memory_pool_work_thread, 1000);

    thread0.join();
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();
    thread9.join();
  }
}

static void benchmark_malloc_work_thread(benchmark::State& state) {
  for (auto _ : state) {
    std::thread thread0(&malloc_work_thread, 50);
    std::thread thread1(&malloc_work_thread, 50);
    std::thread thread2(&malloc_work_thread, 100);
    std::thread thread3(&malloc_work_thread, 100);
    std::thread thread4(&malloc_work_thread, 100);
    std::thread thread5(&malloc_work_thread, 500);
    std::thread thread6(&malloc_work_thread, 500);
    std::thread thread7(&malloc_work_thread, 500);
    std::thread thread8(&malloc_work_thread, 1000);
    std::thread thread9(&malloc_work_thread, 1000);

    thread0.join();
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();
    thread9.join();
  }
}

static void benchmark_vector_work_thread(benchmark::State& state) {
  for (auto _ : state) {
    std::thread thread0(&vector_work_thread, 50);
    std::thread thread1(&vector_work_thread, 50);
    std::thread thread2(&vector_work_thread, 100);
    std::thread thread3(&vector_work_thread, 100);
    std::thread thread4(&vector_work_thread, 100);
    std::thread thread5(&vector_work_thread, 500);
    std::thread thread6(&vector_work_thread, 500);
    std::thread thread7(&vector_work_thread, 500);
    std::thread thread8(&vector_work_thread, 1000);
    std::thread thread9(&vector_work_thread, 1000);

    thread0.join();
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();
    thread9.join();
  }
}

BENCHMARK(benchmark_map_memory_pool_work_thread);
BENCHMARK(benchmark_malloc_work_thread);
BENCHMARK(benchmark_vector_work_thread);

BENCHMARK_MAIN();
