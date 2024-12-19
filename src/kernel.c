#include "uart/mini_uart.h"

void uart_send_string(char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    uart_send((char)str[i]);
  }
}

void kernel_main(void) {
  uart_init();
  uart_send_string("Hello, world!\r\n");

  while (1) uart_send(uart_recv());
}
