#include "memory_pool/map_memory_pool.hpp"

#include <sys/mman.h>

namespace map_memory_pool {

MemoryPool::~MemoryPool() {
  for (auto& key : page_memory_map_) {
    munmap(key.first, key.second);
  }
}

size_t MemoryPool::get_memory_block_size(size_t mem_size) {
  if (mem_size <= kMinMemoryBlockSize) {
    return kMinMemoryBlockSize;
  }

  --mem_size;
  mem_size |= mem_size >> 1;
  mem_size |= mem_size >> 2;
  mem_size |= mem_size >> 4;
  mem_size |= mem_size >> 8;
  mem_size |= mem_size >> 16;
  mem_size |= mem_size >> 32;

  return mem_size + 1;
}

char* MemoryPool::malloc(size_t memory_size) {
  auto memory_block_size = get_memory_block_size(memory_size);
  {
    std::lock_guard<std::mutex> lk(global_map_mutex_);
    if (memory_nodes_.find(memory_block_size) == memory_nodes_.end()) {
      memory_nodes_.insert(std::make_pair(memory_block_size, mem_node()));
      memory_node_mutexs_.insert(
          std::make_pair(memory_block_size, std::make_unique<std::mutex>()));
    }
  }

  std::lock_guard<std::mutex> lk(*memory_node_mutexs_[memory_block_size]);
  auto& mem_node_ref = memory_nodes_[memory_block_size];
  if (mem_node_ref.next != nullptr) {
    char* reuslt_ptr = reinterpret_cast<char*>(mem_node_ref.next);
    mem_node_ref.next = mem_node_ref.next->next;
    return reuslt_ptr;
  }

  // allocate page memory
  size_t page_num = (memory_block_size - 1) / kPageSize + 1;
  char* memory_blocks_ptr = malloc_page(page_num);

  if (memory_blocks_ptr == nullptr) {
    return nullptr;
  }

  size_t memory_block_num = page_num * kPageSize / memory_block_size;

  mem_node* now_mem_node = &mem_node_ref;
  for (size_t memory_block_index = 0; memory_block_index < memory_block_num - 1;
       ++memory_block_index) {
    now_mem_node->next = reinterpret_cast<mem_node*>(
        &memory_blocks_ptr[memory_block_index * memory_block_size]);
    now_mem_node->next->next = nullptr;
    now_mem_node = now_mem_node->next;
  }

  return &memory_blocks_ptr[(memory_block_num - 1) * memory_block_size];
}

bool MemoryPool::free(char* ptr, size_t memory_size) {
  auto memory_block_size = get_memory_block_size(memory_size);
  std::lock_guard<std::mutex> lk(*memory_node_mutexs_[memory_block_size]);
  auto& mem_node_ref = memory_nodes_[memory_block_size];
  mem_node* free_mem_node = reinterpret_cast<mem_node*>(ptr);
  // Inserting the mem_node at the Head
  free_mem_node->next = mem_node_ref.next;
  mem_node_ref.next = free_mem_node;
  return true;
}

char* MemoryPool::malloc_page(size_t page_num) {
  void* ptr = mmap(NULL, page_num * kPageSize, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  {
    std::lock_guard<std::mutex> lk(global_page_map_mutex_);
    page_memory_map_.insert(
        {reinterpret_cast<char*>(ptr), page_num * kPageSize});
  }
  return reinterpret_cast<char*>(ptr);
}

}  // namespace map_memory_pool