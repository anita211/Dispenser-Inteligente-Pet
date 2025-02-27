#include <sensor.h>

// Para sensor de proximidade
volatile unsigned int temp[2];
volatile float diff = 0;
volatile float distance = 0;
volatile unsigned int i = 0;

// Configuração do Timer_A1 para PWM do Trigger no P2.0 (HC-SR04)
void ta1_config(void)
{
    TA1CTL = TASSEL__SMCLK | MC__UP; // Usa SMCLK e modo UP
    TA1CCR0 = 60000 - 1;             // Período de 60ms
    TA1CCR1 = 10;                    // Pulso de 10us
    TA1CCTL1 = OUTMOD_6;             // Modo Toggle/Set
    P2DIR |= BIT0;                   // P2.0 como saída (Trigger)
    P2SEL |= BIT0;                   // P2.0 dedicado ao PWM
}

// Configuração do Timer_A0 para Captura do Echo no P1.2
void ta0_config(void)
{
    TA0CTL = TASSEL__SMCLK | MC__CONTINUOUS; // Usa SMCLK e modo contínuo
    TA0CCTL1 = CM_3 | CCIS_0 | CAP | CCIE | SCS; // Captura borda de subida/descida
    P1DIR &= ~BIT2; // P1.2 como entrada (Echo)
    P1SEL |= BIT2;  // Conecta P1.2 ao Timer_A0
    __enable_interrupt(); // Habilita interrupções globais
}

// Interrupção do Timer_A0 para Captura do Echo
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
    if (TA0CCTL1 & CCI)  // Se capturamos a borda de subida
    {
        temp[0] = TA0CCR1;  // Salva o tempo da borda de subida
    }
    else  // Se capturamos a borda de descida
    {
        temp[1] = TA0CCR1;   // Salva o tempo da borda de descida
        diff = temp[1] - temp[0]; // Calcula o tempo do pulso
        if (diff < 0) diff += 65536; // Corrige estouro do timer
    }
    TA0CCTL1 &= ~CCIFG; // Limpa flag de interrupção
}

/*
// Configuração do LED no P1.0
void io_config(void)
{
    P1DIR |= BIT0;  // P1.0 como saída (LED)
    P1OUT &= ~BIT0; // Garante que o LED inicie apagado
}
*/
