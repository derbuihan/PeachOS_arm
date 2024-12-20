#include "kheap.h"

#include "config.h"
#include "heap.h"
#include "kernel.h"
#include "memory/memory.h"

HEAP_BLOCK_TABLE_ENTRY entries[PEACHOS_HEAP_SIZE_BLOCKS];
struct heap_table kernel_heap_table = {
    .entries = entries,
    .total = PEACHOS_HEAP_SIZE_BLOCKS,
};
struct heap kernel_heap = {
    .table = &kernel_heap_table,
    .saddr = (void *)PEACHOS_HEAP_ADDRESS,
};

void kheap_init() {
  void *end = kernel_heap.saddr + PEACHOS_HEAP_SIZE_BYTES;

  int res = heap_create(&kernel_heap, kernel_heap.saddr, end,
                        PEACHOS_HEAP_BLOCK_SIZE);
  if (res < 0) {
    panic("Failed to create heap \r\n");
  }
}

void *kmalloc(size_t size) {
  void *ptr = heap_malloc(&kernel_heap, size);
  return ptr;
}

void *kzalloc(size_t size) {
  void *ptr = kmalloc(size);
  if (ptr) {
    memset(ptr, 0, size);
  }
  return ptr;
}

void kfree(void *ptr) {}
