#ifndef _MINI_UART_H
#define _MINI_UART_H

void uart_init(void);

void uart_send(char c);

char uart_recv(void);

#endif /* _MINI_UART_H */
