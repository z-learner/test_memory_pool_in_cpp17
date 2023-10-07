/**
 * @file pmr_memory_pool.hpp
 * @author Zplearner@163.com
 * @brief base on  monotonic_buffer_resource to implement memory_pool
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once
#include <array>
#include <memory_resource>

namespace pmr_memory_pool {

class MemoryPool {
 public:
  static MemoryPool& GetMemoryPool() {
    static MemoryPool memory_pool;
    return memory_pool;
  }

  char* malloc(size_t memory_size);
  bool free(char* ptr, size_t memory_size);

 private:
  MemoryPool()
      : monotonic_resource(static_buff_.data(), static_buff_.size()),
        pool_resource(&monotonic_resource),
        allocator(&pool_resource) {}
  ~MemoryPool() = default;

  MemoryPool(const MemoryPool&) = delete;
  MemoryPool(MemoryPool&&) = delete;
  MemoryPool& operator=(const MemoryPool&) = delete;
  MemoryPool& operator=(MemoryPool&&) = delete;

 private:
  alignas(alignof(
      std::max_align_t)) std::array<uint8_t, 20 * 1024 * 1024> static_buff_;

  std::pmr::monotonic_buffer_resource monotonic_resource;

  std::pmr::synchronized_pool_resource pool_resource;

  std::pmr::polymorphic_allocator<char> allocator;
};

}  // namespace pmr_memory_pool