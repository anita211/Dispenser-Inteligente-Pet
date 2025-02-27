#include <3H.h>

// Flag global: setada quando 1 minuto se completa.
volatile unsigned char minuteFlag = 0;

// Variável estática para contar os segundos (não exposta externamente)
static unsigned int sec = 0;

/*
Relógio com segundos e minutos usando ACLK (32.768 Hz)
Configura o TimerB0 para disparar uma interrupção a cada 1 segundo.
Exemplo: alterna o LED verde a cada segundo e o LED vermelho a cada minuto.
Quando 1 minuto é alcançado, a flag 'minuteFlag' é setada para sinalizar o evento.
*/
void tb0_config(void) {
    // Configura o TimerB0 para usar ACLK em modo UP
    TB0CTL = TBSSEL_1 | MC_1;
    TB0CCR0 = SEC_COUNT - 1;    // TB0 dispara a cada 1 segundo
    // Habilita a interrupção para TB0.0
    TB0CCTL0 = CCIE;
    __enable_interrupt(); // Habilita interrupções globais
}

// Função para resetar o contador de segundos, para ser chamada quando o usuário aciona a alimentação manual.
void reset_sec(void) {
    sec = 0;
}

// Rotina de interrupção do TimerB0 para CCR0
#pragma vector = 59
__interrupt void TB0_CCR0_ISR(void) {
    // Aguarda a flag CCIFG de TB0.0 indicando 1 segundo
    // (A flag é automaticamente gerada a cada ciclo do timer em modo UP)

    sec++;  // Incrementa o contador de segundos

    if (sec == 60) {      // 60 segundos = 1 minuto; 3 horas = 10800 segundos
        sec = 0;          // Reinicia a contagem de segundos
        // Seta a flag para indicar que 1 minuto se passou
        minuteFlag = 1;
        led_GREEN();
    }
    TB0CCTL0 &= ~CCIFG; // Limpa flag de interrupção
}
