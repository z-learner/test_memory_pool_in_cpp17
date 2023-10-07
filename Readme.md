## test_memory_pool

> 多线程，阅后即焚式的内存分配

``` bash
--------------------------------------------------------------------------------
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
benchmark_map_memory_pool_work_thread   16043924 ns       796833 ns          878
benchmark_pmr_memory_pool_work_thread   25692071 ns      1034459 ns          100
benchmark_malloc_work_thread              574050 ns       495415 ns         1390
benchmark_vector_work_thread             1303749 ns       860483 ns          922
```

- benchmark_map_memory_pool_work_thread 的执行时间相对较低，表明使用内存池的内存分配和管理方法在多线程工作负载下表现良好。
- benchmark_pmr_memory_pool_work_thread 的执行时间相对较高，表明使用 C++17 的 std::pmr::synchronized_pool_resource 进行内存分配和管理的方法在多线程工作负载下可能开销较大。这个结果可能是由于 std::pmr::synchronized_pool_resource 内部实现较复杂或与多线程的互斥操作有关。
- benchmark_malloc_work_thread 的执行时间比使用内存池的方法更短，表明标准的 malloc 函数在多线程工作负载下的性能仍然很好。这可能是因为 malloc 使用了更低级别的系统调用来进行内存分配，通常不涉及大规模的互斥操作。
- benchmark_vector_work_thread 的执行时间相对较低，这表明标准库的 std::vector 在多线程工作负载下的性能也不错。