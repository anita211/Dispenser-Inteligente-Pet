#include <gpio.h>

void gpio_config(void){

    P1DIR |=  BIT0;
    P1OUT &= ~BIT0;      // Red led
    P4DIR |=  BIT7;
    P4OUT &= ~BIT7;      // green led

    P2DIR &= ~BIT1;     // S1 como entrada
    P2REN |= BIT1;      // Habilitar resistor de pull-up
    P2OUT |= BIT1;      // Configura pull-up

    P1DIR &= ~BIT1;     // S2 como entrada
    P1REN |= BIT1;      // Habilitar resistor de pull-up
    P1OUT |= BIT1;      // Configura pull-up
}

int mon_s1(void){
    static int ps1 = ABERTA;
    if ((P2IN & BIT1) == 0 ){
        if (ps1 == ABERTA){
            debounce(DBC);
            ps1 = FECHADA;
            return TRUE;
        }
    }
    else{
        if(ps1 == FECHADA){
            debounce(DBC);
            ps1 = ABERTA;
            return FALSE;
        }
    }
    return FALSE;
}

int mon_s2(void){
    static int ps2 = ABERTA;
    if((P1IN & BIT1) == 0){
        if(ps2 == ABERTA){
            debounce(DBC);
            ps2 = FECHADA;
            return TRUE;
        }
    }
    else{
        if(ps2 == FECHADA){
            debounce(DBC);
            ps2 = ABERTA;
            return FALSE;
        }
    }
    return FALSE;
}

void led_green(void)   {P4OUT &= ~BIT7;}   // Turn off green led
void led_GREEN(void)   {P4OUT |=  BIT7;}   // Turn on green led
void led_red(void)   {P1OUT &= ~BIT0;}   // Turn off red led
void led_RED(void)   {P1OUT |=  BIT0;}   // Turn on red led
