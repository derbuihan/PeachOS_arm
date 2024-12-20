#include <config.h>

#include "memory/heap/kheap.h"
#include "memory/memory.h"
#include "uart/mini_uart.h"

void print(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    uart_send((char)str[i]);
  }
}

void panic(char *message) {
  print(message);
  while (1) {
  }
}

void kernel_main(void) {
  uart_init();
  kheap_init();

  char *str = kzalloc(15 * sizeof(char));
  memcpy(str, "Hello, world!\r\n", 15);
  print(str);

  char *str2 = kzalloc(15 * sizeof(char));
  memcpy(str2, "Hello, world!\r\n", 15);
  char *str3 = kzalloc(15 * sizeof(char));
  memcpy(str3, "Hello, world!\r\n", 15);

  print(str);
  while (1) uart_send(uart_recv());
}
