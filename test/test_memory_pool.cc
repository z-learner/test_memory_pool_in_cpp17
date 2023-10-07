#include <benchmark/benchmark.h>

#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "memory_pool/map_memory_pool.hpp"
#include "memory_pool/pmr_memory_pool.hpp"

// #define FIRST
#define SECOND
// #define THIRD

void pmr_memory_pool_work_thread(size_t malloc_size) {
  size_t count = 2000;
  while (count-- > 0) {
    char* ptr =
        pmr_memory_pool::MemoryPool::GetMemoryPool().malloc(malloc_size);
    if (ptr == nullptr) {
      std::cout << "Get nullptr from MemoryPool" << std::endl;
      throw std::runtime_error("Get nullptr from pmr_memory_pool::MemoryPool");
    }
    // if (malloc_size == 2000) {
    //   std::cout << "pmr_memory_pool memory pointer "
    //             << reinterpret_cast<size_t>(ptr) << std::endl;
    // }

#ifdef FIRST
    std::memset(ptr, 0, malloc_size);
#endif

#ifdef SECOND
    for (size_t index = 0; index < malloc_size; ++index) {
      benchmark::DoNotOptimize(ptr[index]);
    }
#endif

    pmr_memory_pool::MemoryPool::GetMemoryPool().free(ptr, malloc_size);
  }
}

void map_memory_pool_work_thread(size_t malloc_size) {
  size_t count = 2000;
  while (count-- > 0) {
    char* ptr =
        map_memory_pool::MemoryPool::GetMemoryPool().malloc(malloc_size);
    if (ptr == nullptr) {
      std::cout << "Get nullptr from MemoryPool" << std::endl;
    }
    // if (malloc_size == 2000) {
    //   std::cout << "map_memory_pool memory pointer "
    //             << reinterpret_cast<size_t>(ptr) << std::endl;
    // }

#ifdef FIRST
    std::memset(ptr, 0, malloc_size);
#endif

#ifdef SECOND
    for (size_t index = 0; index < malloc_size; ++index) {
      benchmark::DoNotOptimize(ptr[index]);
    }
#endif

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
    // if (malloc_size == 2000) {
    //   std::cout << "malloc memory pointer " << reinterpret_cast<size_t>(ptr)
    //             << std::endl;
    // }
#ifdef FIRST
    std::memset(ptr, 0, malloc_size);
#endif

#ifdef SECOND
    for (size_t index = 0; index < malloc_size; ++index) {
      benchmark::DoNotOptimize(ptr[index]);
    }
#endif

    free(ptr);
  }
}

void vector_work_thread(size_t malloc_size) {
  size_t count = 2000;

  while (count-- > 0) {
    std::vector<char> data(malloc_size);
    // if (malloc_size == 2000) {
    //   std::cout << "vector memory pointer "
    //             << reinterpret_cast<size_t>(data.data()) << std::endl;
    // }
#ifdef FIRST
    std::memset(data.data(), 0, malloc_size);
#endif

#ifdef SECOND
    for (size_t index = 0; index < malloc_size; ++index) {
      benchmark::DoNotOptimize(data.data()[index]);
    }
#endif
  }
}

static void benchmark_map_memory_pool_work_thread(benchmark::State& state) {
  auto& init = map_memory_pool::MemoryPool::GetMemoryPool();
  for (auto _ : state) {
    std::thread thread0(&map_memory_pool_work_thread, 50);
    std::thread thread1(&map_memory_pool_work_thread, 50);
    std::thread thread2(&map_memory_pool_work_thread, 100);
    std::thread thread3(&map_memory_pool_work_thread, 100);
    std::thread thread4(&map_memory_pool_work_thread, 100);
    std::thread thread5(&map_memory_pool_work_thread, 500);
    std::thread thread6(&map_memory_pool_work_thread, 500);
    std::thread thread7(&map_memory_pool_work_thread, 1000);
    std::thread thread8(&map_memory_pool_work_thread, 1000);
    std::thread thread9(&map_memory_pool_work_thread, 2000);

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

static void benchmark_pmr_memory_pool_work_thread(benchmark::State& state) {
  auto& init = pmr_memory_pool::MemoryPool::GetMemoryPool();
  for (auto _ : state) {
    std::thread thread0(&pmr_memory_pool_work_thread, 50);
    std::thread thread1(&pmr_memory_pool_work_thread, 50);
    std::thread thread2(&pmr_memory_pool_work_thread, 100);
    std::thread thread3(&pmr_memory_pool_work_thread, 100);
    std::thread thread4(&pmr_memory_pool_work_thread, 100);
    std::thread thread5(&pmr_memory_pool_work_thread, 500);
    std::thread thread6(&pmr_memory_pool_work_thread, 500);
    std::thread thread7(&pmr_memory_pool_work_thread, 1000);
    std::thread thread8(&pmr_memory_pool_work_thread, 1000);
    std::thread thread9(&pmr_memory_pool_work_thread, 2000);

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
    std::thread thread7(&malloc_work_thread, 1000);
    std::thread thread8(&malloc_work_thread, 1000);
    std::thread thread9(&malloc_work_thread, 2000);

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
    std::thread thread7(&vector_work_thread, 1000);
    std::thread thread8(&vector_work_thread, 1000);
    std::thread thread9(&vector_work_thread, 2000);

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
BENCHMARK(benchmark_pmr_memory_pool_work_thread);
BENCHMARK(benchmark_malloc_work_thread);
BENCHMARK(benchmark_vector_work_thread);

BENCHMARK_MAIN();
