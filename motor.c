#include <motor.h>

void ta2_config(void) {
    // Configura��o do Timer A2
    TA2CTL = TASSEL_2 | ID_0 | MC_1 | TACLR;  // SMCLK, sem divis�o, modo UP, limpa contador
    TA2EX0 = TAIDEX_0;                        // Sem divis�o extra
    TA2CCR0 = T20ms;                          // Per�odo de 20 ms para PWM

    // Configura��o do canal 1 (P2.4) do Timer A2 para PWM
    TA2CCTL1 = OUTMOD_7;                      // Modo PWM Reset/Set
    TA2CCR1 = NEUTRAL_PWM;                    // Inicializa com pulso neutro (motor parado)

    // Configura��o do pino P2.4 para sa�da PWM
    P2DIR |= BIT4;      // Define P2.4 como sa�da
    P2SEL |= BIT4;      // Seleciona a fun��o do Timer A2 (PWM)
}

void motor_on(void) {
    // Liga o motor
    TA2CCR1 = MODO_PWM;
}

void motor_off(void) {
    // Desliga o motor
    TA2CCR1 = NEUTRAL_PWM;
}

