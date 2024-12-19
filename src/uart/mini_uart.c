#include "peripherals/mini_uart.h"

#include "peripherals/gpio.h"
#include "utils/utils.h"

void uart_send(char c) {
  // wait until the UART transmit buffer is empty.
  // until the bit 5 of AUX_MU_LSR_REG is 1.
  while (1) {
    if (get32(AUX_MU_LSR_REG) & 0x20) break;
  }
  // write the character to the I/O buffer of the UART.
  put32(AUX_MU_IO_REG, c);
}

char uart_recv(void) {
  // wait until the UART receive buffer is not empty.
  // until the bit 0 of AUX_MU_LSR_REG is 1.
  while (1) {
    if (get32(AUX_MU_LSR_REG) & 0x01) break;
  }
  // read the character from the I/O buffer of the UART.
  return get32(AUX_MU_IO_REG) & 0xFF;
}

void uart_init(void) {
  unsigned int selector;

  // configure the GPIO pins for UART.
  // set GPIO14 and GPIO15 to set for UART.
  selector = get32(GPFSEL1);
  selector &= ~(7 << 12); // clear gpio14
  selector |= 2 << 12; // set gpio14 to alt5
  selector &= ~(7 << 15); // clear gpio15
  selector |= 2 << 15; // set gpio15 to alt5
  put32(GPFSEL1, selector);

  // disable pull-up/down for all GPIO pins
  put32(GPPUD, 0); // disable pull-up/down
  delay(150); // wait 150 cycles
  put32(GPPUDCLK0, (1 << 14) | (1 << 15)); // enable clock for gpio14, gpio15
  delay(150); // wait 150 cycles
  put32(GPPUDCLK0, 0); // disable clock

  // initialize the mini UART.
  put32(AUX_ENABLES, 1); // enable mini UART
  put32(AUX_MU_CNTL_REG, 0); // disable tx, rx
  put32(AUX_MU_IER_REG, 0); // disable interrupt
  put32(AUX_MU_LCR_REG, 3); // set the data size to 8 bits
  put32(AUX_MU_MCR_REG, 0); // set uart to normal mode
  put32(AUX_MU_BAUD_REG, 270); // set baud rate to 115200
  put32(AUX_MU_CNTL_REG, 3); // enable tx, rx
}
