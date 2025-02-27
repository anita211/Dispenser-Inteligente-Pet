
#include <msp430.h>
#include <string.h>   // Necessário para strcpy
#include <utils.h>
#include <gpio.h>
#include <i2c.h>
#include <lcd.h>
#include <motor.h>
#include <sensor.h>
#include <3H.h>
#include <UART.h>

char frases[FRASES_TAMANHO][LCD_LINHA_MAX] = {
   "Modo P",
   "Modo M",
   "Modo G",
   "Liberar racao"
};
unsigned int modo;
unsigned long delay;

char buffer[50];

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    __enable_interrupt();

    gpio_config();
    i2c_config();
    ta0_config();
    ta1_config();
    ta2_config();
    tb0_config();
    uart_init();

    if (pcf_teste(PCF_ADR)==FALSE){
        led_RED();           // No ACK
        while(TRUE);         // Freeze
    }
    //else    led_GREEN();     // ACK

    lcd_init();
    pcf_write(PCF_ADR, 8);   // Turn on back light

    // Exibe a mensagem de boas-vindas
    lcd_clear2();
    lcdWriteString("Bem vindo(a)!");
    __delay_cycles(2000000);  // Aguarda um tempo para exibir a mensagem

    volatile int S1 = 0, S2 = 0, index_frase = FRASES_TAMANHO - 1;
    int previous_S1 = ABERTA, previous_S2 = ABERTA;
    int frase_changed = FALSE;

    while(TRUE) {
        S1 = (P2IN & BIT1) == 0;
        S2 = (P1IN & BIT1) == 0;

        if (S1 == ABERTA) {
            if (previous_S1 ==  FECHADA) {
                if (index_frase + 1 >= FRASES_TAMANHO) {
                    index_frase = 0;
                } else {
                    index_frase++;
                }
                previous_S1 = ABERTA;
                frase_changed = TRUE;
                debounce(DBC);
            }
        } else {
            previous_S1 = FECHADA;
            debounce(DBC);
        }

        if (S2 == ABERTA) {
            if (previous_S2 ==  FECHADA) {
                lcd_clear2();

                if (index_frase != FRASES_TAMANHO - 1){
                    lcdWriteString("Modo salvo!");
                    modo = index_frase;
                    __delay_cycles(2000000);
                } else {
                    reset_sec();
                    lcdWriteString("Liberando racao");
                    __delay_cycles(1000000);
                    motor_on();
                    delayCycles(modo);
                    motor_off();
                    reset_sec();
                    lcd_clear2();
                    lcdWriteString("Fim!");
                    __delay_cycles(2000000);
                }

                previous_S2 = ABERTA;
                frase_changed = TRUE;
                debounce(DBC);
            }
        } else {
            previous_S2 = FECHADA;
            debounce(DBC);
        }

        if (frase_changed == TRUE) {
            lcd_clear2();
            lcdWriteString(frases[index_frase]);
            frase_changed = FALSE;
        }


        // Lógica do sensor de proximidade
        if (diff > 0) { // Apenas calcula a distância se diff foi atualizado
            distance = diff / 58.0; // Conversão para cm

            sprintf(buffer, "Distancia: %.2f cm\r\n", distance);
            uart_sendString(buffer);

            if (distance <= 10.0 && minuteFlag == 1) {
                minuteFlag = 0;
                led_green();
                motor_on();   // Liga o motor se a distância for menor ou igual a 10 cm
                delayCycles(modo);
                motor_off();
            }

        }

    }
    return 0;
}
