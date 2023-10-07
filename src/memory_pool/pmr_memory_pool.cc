#include "memory_pool/pmr_memory_pool.hpp"

#include <iostream>
namespace pmr_memory_pool {

MemoryPool::MemoryPool() {
  internal_buff_.resize(10 * 1024 * 1024);

  monotonic_resource_ptr =
      std::make_unique<std::pmr::monotonic_buffer_resource>(
          internal_buff_.data(), internal_buff_.size());

  pool_resource_ptr = std::make_unique<std::pmr::synchronized_pool_resource>(
      monotonic_resource_ptr.get());

  allocator_ptr = std::make_unique<std::pmr::polymorphic_allocator<char>>(
      pool_resource_ptr.get());

  // std::cout << "pmr_memory_pool get pool ptr : " << std::hex
  //           << reinterpret_cast<size_t>(internal_buff_.data()) << std::endl;
}

char* MemoryPool::malloc(size_t memory_size) {
  char* ptr = allocator_ptr->allocate(memory_size);
  return ptr;
}

bool MemoryPool::free(char* ptr, size_t memory_size) {
  allocator_ptr->deallocate(ptr, memory_size);
  return true;
}

}  // namespace pmr_memory_pool