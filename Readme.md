## test_memory_pool

> 多线程，阅后即焚式的内存分配

### define FIRST

#### 默认编译

``` bash
--------------------------------------------------------------------------------
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
benchmark_map_memory_pool_work_thread   16604361 ns       841918 ns          957
benchmark_malloc_work_thread              661054 ns       540500 ns         1070
benchmark_vector_work_thread             1354636 ns       897550 ns          779
```

> benchmark_pmr_memory_pool_work_thread 无法运行完成（OOM killed）

#### Release
``` bash
--------------------------------------------------------------------------------
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
benchmark_map_memory_pool_work_thread    5293829 ns       650829 ns         1001
benchmark_malloc_work_thread              551418 ns       466669 ns         1292
benchmark_vector_work_thread              653284 ns       504335 ns         1399
```


- benchmark_map_memory_pool_work_thread 的执行时间相对较低，表明使用内存池的内存分配和管理方法在多线程工作负载下表现良好。
- benchmark_pmr_memory_pool_work_thread 的执行时间相对较高，表明使用 C++17 的 std::pmr::synchronized_pool_resource 进行内存分配和管理的方法在多线程工作负载下可能开销较大。这个结果可能是由于 std::pmr::synchronized_pool_resource 内部实现较复杂或与多线程的互斥操作有关。
- benchmark_malloc_work_thread 的执行时间比使用内存池的方法更短，表明标准的 malloc 函数在多线程工作负载下的性能仍然很好。这可能是因为 malloc 使用了更低级别的系统调用来进行内存分配，通常不涉及大规模的互斥操作。
- benchmark_vector_work_thread 的执行时间相对较低，这表明标准库的 std::vector 在多线程工作负载下的性能也不错。

### define SECOND

#### 默认编译
```bash
--------------------------------------------------------------------------------
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
benchmark_map_memory_pool_work_thread   38856434 ns       778654 ns          100
benchmark_pmr_memory_pool_work_thread   42743256 ns       978191 ns          100
benchmark_malloc_work_thread            34493015 ns      1193394 ns          100
benchmark_vector_work_thread            38920446 ns      1243032 ns          100
```

#### Release
```bash
--------------------------------------------------------------------------------
Benchmark                                      Time             CPU   Iterations
--------------------------------------------------------------------------------
benchmark_map_memory_pool_work_thread    8452090 ns       913377 ns          896
benchmark_malloc_work_thread             2062216 ns       665071 ns          958
benchmark_vector_work_thread             2195356 ns       633343 ns         1115
```
> benchmark_pmr_memory_pool_work_thread 无法运行完成（OOM killed）

#### 总结
realse better when use mallic and vector

### How to test cache missing ? 
```bash
perf stat -e cache-references,cache-misses ./test_memory_pool
```

> 阅后即焚式的内存分配，单线程，相同大小的分配模式下，map_memory_pool总能得到相同的内存地址，pmr_memory_pool的地址是随机的，vector/malloc在一定时间内拿到的地址是唯一的