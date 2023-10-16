#include <benchmark/benchmark.h>

#include <atomic>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "memory_pool/map_memory_pool.hpp"
#include "memory_pool/pmr_memory_pool.hpp"
#include "timer/timer.hpp"

thread_local std::vector<char*> packets;
static constexpr size_t repeat_time = 60000;

template <size_t PakcetSize>
void map_memory_pool_timer_work_func() {
  char* ptr = map_memory_pool::MemoryPool::GetMemoryPool().malloc(PakcetSize);

  std::memset(ptr, 12, PakcetSize);
  packets.push_back(ptr);

  if (packets.size() > 150) {
    for (auto ptr_tmp : packets) {
      map_memory_pool::MemoryPool::GetMemoryPool().free(ptr_tmp, PakcetSize);
    }
    packets.clear();
  }
}

template <size_t PakcetSize>
void pmr_memory_pool_timer_work_func() {
  char* ptr = pmr_memory_pool::MemoryPool::GetMemoryPool().malloc(PakcetSize);

  std::memset(ptr, 12, PakcetSize);
  packets.push_back(ptr);

  if (packets.size() > 150) {
    for (auto ptr_tmp : packets) {
      pmr_memory_pool::MemoryPool::GetMemoryPool().free(ptr_tmp, PakcetSize);
    }
    packets.clear();
  }
}

template <size_t PakcetSize>
void malloc_timer_work_func() {
  char* ptr = reinterpret_cast<char*>(std::malloc(PakcetSize));

  std::memset(ptr, 12, PakcetSize);
  packets.push_back(ptr);

  if (packets.size() > 150) {
    for (auto ptr_tmp : packets) {
      std::free(ptr_tmp);
    }
    packets.clear();
  }
}

int test_map_memory_pool() {
  std::cout << "-----test_map_memory_pool-----" << std::endl;
  timer::Timer time1(repeat_time);                               // repeat
  time1.Start(1000000, &map_memory_pool_timer_work_func<8820>);  // 1ms

  timer::Timer time2(repeat_time);                               // repeat
  time2.Start(1000000, &map_memory_pool_timer_work_func<8820>);  // 1ms

  timer::Timer time3(repeat_time);                               // repeat
  time3.Start(1000000, &map_memory_pool_timer_work_func<8820>);  // 1ms

  timer::Timer time4(repeat_time);                               // repeat
  time4.Start(1000000, &map_memory_pool_timer_work_func<1000>);  // 1ms

  timer::Timer time5(repeat_time);                               // repeat
  time5.Start(1000000, &map_memory_pool_timer_work_func<1000>);  // 1ms

  timer::Timer time6(repeat_time);                               // repeat
  time6.Start(1000000, &map_memory_pool_timer_work_func<4000>);  // 1ms

  timer::Timer time7(repeat_time);                               // repeat
  time6.Start(1000000, &map_memory_pool_timer_work_func<4000>);  // 1ms

  while (time1.IsActive() || time2.IsActive() || time3.IsActive() ||
         time4.IsActive() || time5.IsActive() || time6.IsActive() ||
         time7.IsActive()) {  // run....
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}

int test_pmr_memory_pool() {
  std::cout << "-----test_pmr_memory_pool-----" << std::endl;
  timer::Timer time1(repeat_time);                               // repeat
  time1.Start(1000000, &pmr_memory_pool_timer_work_func<8820>);  // 1ms

  timer::Timer time2(repeat_time);                               // repeat
  time2.Start(1000000, &pmr_memory_pool_timer_work_func<8820>);  // 1ms

  timer::Timer time3(repeat_time);                               // repeat
  time3.Start(1000000, &pmr_memory_pool_timer_work_func<8820>);  // 1ms

  timer::Timer time4(repeat_time);                               // repeat
  time4.Start(1000000, &pmr_memory_pool_timer_work_func<1000>);  // 1ms

  timer::Timer time5(repeat_time);                               // repeat
  time5.Start(1000000, &pmr_memory_pool_timer_work_func<1000>);  // 1ms

  timer::Timer time6(repeat_time);                               // repeat
  time6.Start(1000000, &pmr_memory_pool_timer_work_func<4000>);  // 1ms

  timer::Timer time7(repeat_time);                               // repeat
  time6.Start(1000000, &pmr_memory_pool_timer_work_func<4000>);  // 1ms

  while (time1.IsActive() || time2.IsActive() || time3.IsActive() ||
         time4.IsActive() || time5.IsActive() || time6.IsActive() ||
         time7.IsActive()) {  // run....
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}

int test_malloc() {
  std::cout << "-----test_malloc-----" << std::endl;
  timer::Timer time1(repeat_time);                      // repeat
  time1.Start(1000000, &malloc_timer_work_func<8820>);  // 1ms

  timer::Timer time2(repeat_time);                      // repeat
  time2.Start(1000000, &malloc_timer_work_func<8820>);  // 1ms

  timer::Timer time3(repeat_time);                      // repeat
  time3.Start(1000000, &malloc_timer_work_func<8820>);  // 1ms

  timer::Timer time4(repeat_time);                      // repeat
  time4.Start(1000000, &malloc_timer_work_func<1000>);  // 1ms

  timer::Timer time5(repeat_time);                      // repeat
  time5.Start(1000000, &malloc_timer_work_func<1000>);  // 1ms

  timer::Timer time6(repeat_time);                      // repeat
  time6.Start(1000000, &malloc_timer_work_func<4000>);  // 1ms

  timer::Timer time7(repeat_time);                      // repeat
  time6.Start(1000000, &malloc_timer_work_func<4000>);  // 1ms

  while (time1.IsActive() || time2.IsActive() || time3.IsActive() ||
         time4.IsActive() || time5.IsActive() || time6.IsActive() ||
         time7.IsActive()) {  // run....
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}

int main(int argc, char** argv) {
  test_map_memory_pool();
  test_pmr_memory_pool();
  test_malloc();
}