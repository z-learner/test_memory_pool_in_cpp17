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
#include <vector>

#include "aligned_allocator/aligned_allocator.hpp"

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
  MemoryPool();
  ~MemoryPool() = default;

  MemoryPool(const MemoryPool&) = delete;
  MemoryPool(MemoryPool&&) = delete;
  MemoryPool& operator=(const MemoryPool&) = delete;
  MemoryPool& operator=(MemoryPool&&) = delete;

 private:
  std::vector<uint8_t, aligned_allocator::AlignedAllocator<uint8_t, 64>>
      internal_buff_;

  std::unique_ptr<std::pmr::monotonic_buffer_resource> monotonic_resource_ptr{
      nullptr};

  std::unique_ptr<std::pmr::synchronized_pool_resource> pool_resource_ptr{
      nullptr};

  std::unique_ptr<std::pmr::polymorphic_allocator<char>> allocator_ptr{nullptr};
};

}  // namespace pmr_memory_pool