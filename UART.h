#ifndef UART_H_
#define UART_H_

#include <msp430.h>
#include <stdint.h>

/*
 * Inicializa o módulo USCI_A1 para comunicação UART a 9600 bps com SMCLK = 1MHz.
 * Os pinos usados são P4.4 (TX) e P4.5 (RX).
 */
void uart_init(void);

/*
 * Envia uma string via UART.
 */
void uart_sendString(char *str);

/*
 * Variáveis para recepção via UART.
 */
extern volatile uint8_t uartReady;
extern volatile char uartBuffer[16];

#endif /* UART_H_ */
