/**
 * @file map_memory_pool.hpp
 * @author Zplearner@163.com
 * @brief  base on unordered_map to implement memory_pool
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
namespace map_memory_pool {

class MemoryPool {
 public:
  static constexpr size_t kMinMemoryBlockSize = 8;
  static constexpr size_t kPageSize = 4 * 1024;

  static MemoryPool& GetMemoryPool() {
    static MemoryPool memory_pool;
    return memory_pool;
  }

  char* malloc(size_t memory_size);
  bool free(char* ptr, size_t memory_size);

 private:
  struct mem_node {
    mem_node* next = nullptr;
  };

  char* malloc_page(size_t page_num);

  size_t get_memory_block_size(size_t mem_size);

 private:
  MemoryPool() = default;
  ~MemoryPool();

  MemoryPool(const MemoryPool&) = delete;
  MemoryPool(MemoryPool&&) = delete;
  MemoryPool& operator=(const MemoryPool&) = delete;
  MemoryPool& operator=(MemoryPool&&) = delete;

 private:
  std::mutex global_map_mutex_;
  std::mutex global_page_map_mutex_;
  std::unordered_map<size_t, std::unique_ptr<std::mutex>> memory_node_mutexs_;
  std::unordered_map<size_t, mem_node> memory_nodes_;
  std::unordered_map<char*, size_t> page_memory_map_;
};

}  // namespace map_memory_pool