#include "kheap.h"

#include "config.h"
#include "heap.h"
#include "kernel.h"

struct heap kernel_heap;

void kheap_init() {
  kernel_heap.start_addr = (void *)PEACHOS_HEAP_ADDRESS;
  kernel_heap.end_addr =
      (void *)(PEACHOS_HEAP_ADDRESS + PEACHOS_HEAP_SIZE_BYTES);
  kernel_heap.current_addr = (void *)PEACHOS_HEAP_ADDRESS;
}

void *kmalloc(size_t size) {
  void *allocation = kernel_heap.current_addr;
  if (kernel_heap.current_addr + size > kernel_heap.end_addr) {
    print("Kernel heap out of memory!\r\n");
    return NULL;
  }
  kernel_heap.current_addr += size;
  return allocation;
}

void kfree(void *ptr) {}
