#include "UART.h"
#include <string.h>

volatile uint8_t uartReady = 0;
volatile char uartBuffer[16];

void uart_init(void) {
    // Configure o clock para 1MHz, se ainda não estiver configurado.

    UCA1CTL1 = UCSWRST;         // Coloca o módulo em reset para configuração
    UCA1CTL1 |= UCSSEL_2;       // Seleciona SMCLK como fonte (1MHz)

    /*
       Para 9600 bps com SMCLK = 1MHz e oversampling (UCOS16=1):
       N = 1e6 / (16 * 9600) ≈ 6.51 → UCA1BRW = 6
       Parte fracionária: 0.51 * 16 ≈ 8.17 → UCBRF = 8
       (UCBRS é 0 neste exemplo, mas pode ser ajustado conforme o datasheet)
    */
    UCA1BRW = 6;
    UCA1MCTL = UCBRF_8 | UCOS16; // Ajuste fino para 9600 bps

    // Configura os pinos para UCA1: P4.4 (TX) e P4.5 (RX)
    P4SEL |= BIT4 | BIT5;
    P4DIR |= BIT4;      // TX como saída
    P4DIR &= ~BIT5;     // RX como entrada

    UCA1CTL1 &= ~UCSWRST; // Sai do modo reset

    // Habilita a interrupção de recepção
    UCA1IE |= UCRXIE;
    __enable_interrupt();
}

void uart_sendString(char *str) {
    while(*str) {
        while (!(UCA1IFG & UCTXIFG));  // Aguarda o buffer de transmissão estar pronto
        UCA1TXBUF = *str++;           // Envia o caractere e incrementa o ponteiro
    }
}

/*
 * Rotina de interrupção para USCI_A1.
 * Aqui, um buffer é preenchido com os caracteres recebidos. Quando um caractere de
 * fim de linha (0x0D – CR) é recebido, a flag uartReady é setada.
 */
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void) {
    static uint8_t i = 0;
    uint8_t c = UCA1RXBUF;

#ifdef _ECHO_ON
    UCA1TXBUF = c; // Opcional: faz eco do caractere recebido
#endif

    if (c == 0x0D) { // CR indica fim do comando
        uartBuffer[i] = 0;
        uartReady = 1;
        i = 0;
    } else {
        uartBuffer[i] = c;
        i = (i + 1) & 0x0F; // Limita o índice a 16 bytes
    }
}
