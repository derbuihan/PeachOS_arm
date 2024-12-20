#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x00

typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;

struct heap_table {
  HEAP_BLOCK_TABLE_ENTRY *entries;
  size_t total;
};

struct heap {
  struct heap_table *table;

  // Start address of the heap.
  void *saddr;
};

int heap_create(struct heap *heap, void *saddr, void *end, size_t block_size);

void *heap_malloc(struct heap *heap, size_t size);

#endif  // HEAP_H
