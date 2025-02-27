#ifndef UART_H_
#define UART_H_

#include <msp430.h>
#include <stdint.h>

/*
 * Inicializa o m�dulo USCI_A1 para comunica��o UART a 9600 bps com SMCLK = 1MHz.
 * Os pinos usados s�o P4.4 (TX) e P4.5 (RX).
 */
void uart_init(void);

/*
 * Envia uma string via UART.
 */
void uart_sendString(char *str);

/*
 * Vari�veis para recep��o via UART.
 */
extern volatile uint8_t uartReady;
extern volatile char uartBuffer[16];

#endif /* UART_H_ */
