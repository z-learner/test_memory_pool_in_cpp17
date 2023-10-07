#include "memory_pool/pmr_memory_pool.hpp"

namespace pmr_memory_pool {

char* MemoryPool::malloc(size_t memory_size) {
  char* ptr = allocator.allocate(memory_size);
  return ptr;
}

bool MemoryPool::free(char* ptr, size_t memory_size) {
  allocator.deallocate(ptr, memory_size);
  return true;
}

}  // namespace pmr_memory_pool