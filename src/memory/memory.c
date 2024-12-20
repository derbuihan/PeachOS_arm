#include "memory.h"

void *memset(void *ptr, int c, size_t size) {
  char *c_ptr = ptr;
  for (int i = 0; i < size; i++) {
    c_ptr[i] = c;
  }
  return ptr;
}

int memcmp(const void *s1, const void *s2, size_t count) {
  char *c1 = s1;
  char *c2 = s2;
  while (count-- > 0) {
    if (*c1++ != *c2++) return c1[-1] < c2[-1] ? -1 : 1;
  }
  return 0;
}

void *memcpy(void *dest, const void *src, size_t len) {
  char *d = dest;
  char *s = src;
  while (len--) *d++ = *s++;
  return dest;
}
