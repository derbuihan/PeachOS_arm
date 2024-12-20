#include "heap.h"

#include <stdbool.h>
#include <stdint.h>

#include "config.h"
#include "memory/memory.h"
#include "status.h"

static bool heap_validate_alignment(void *ptr) {
  return (unsigned int)ptr % PEACHOS_HEAP_BLOCK_SIZE == 0;
}

static int heap_validate_table(void *saddr, void *end,
                               struct heap_table *table) {
  int res = 0;
  size_t total_blocks = (end - saddr) / PEACHOS_HEAP_BLOCK_SIZE;
  if (total_blocks != table->total) {
    res = -EINVARG;
    goto out;
  }
out:
  return res;
}

int heap_create(struct heap *heap, void *saddr, void *end, size_t block_size) {
  int res = 0;

  if (!heap_validate_alignment(saddr)) {
    res = -EINVARG;
    goto out;
  }

  res = heap_validate_table(saddr, end, heap->table);
  if (res < 0) {
    goto out;
  }

  size_t total_blocks = (end - saddr) / block_size;
  memset(heap->table->entries, HEAP_BLOCK_TABLE_ENTRY_FREE, total_blocks);
out:
  return res;
}

static uint32_t heap_align_value_to_upper(uint32_t value) {
  if (value % PEACHOS_HEAP_BLOCK_SIZE == 0) {
    return value;
  }
  value = value - (value % PEACHOS_HEAP_BLOCK_SIZE);
  value += PEACHOS_HEAP_BLOCK_SIZE;
  return value;
}

int heap_get_start_block(struct heap *heap, size_t total_blocks) {
  struct heap_table *table = heap->table;

  int start_block = -1;
  for (int i = 0; i < table->total; i++) {
    if (table->entries[i] == HEAP_BLOCK_TABLE_ENTRY_FREE) {
      start_block = i;
      break;
    }
  }

  if (start_block < 0) {
    return -ENOMEM;
  }

  return start_block;
}

void heap_mark_blocks_taken(struct heap *heap, int start_block,
                            size_t total_blocks) {
  struct heap_table *table = heap->table;
  for (int i = start_block; i < start_block + total_blocks; i++) {
    table->entries[i] |= HEAP_BLOCK_TABLE_ENTRY_TAKEN;
  }
}

void *heap_block_to_address(struct heap *heap, int block) {
  return heap->saddr + (block * PEACHOS_HEAP_BLOCK_SIZE);
}

void *heap_malloc(struct heap *heap, size_t size) {
  void *address;
  struct heap_table *table = heap->table;

  int start_block = heap_get_start_block(heap, size);
  if (start_block < 0) {
    goto out;
  }

  address = heap_block_to_address(heap, start_block);
  heap_mark_blocks_taken(heap, start_block, 1);
out:
  return address;
}