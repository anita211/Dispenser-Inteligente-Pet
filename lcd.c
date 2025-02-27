#include <lcd.h>

extern volatile int cursor = 0;

// Initialize LCD 4 bit mode
void lcd_init(void){
    // Prepare I2C to operate
    UCB0I2CSA = PCF_ADR;    // Slave address
    UCB0CTL1 |= UCTR    |   // Master TX
                UCTXSTT;    // START
    while ( (UCB0IFG & UCTXIFG) == 0);          // Wait TXIFG=1
    UCB0TXBUF = 0;                              // Output PCF = 0;
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);   // Wait STT=0
    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG) { // NACK?
        led_RED();
        while(TRUE);
    }

    // Start initialization
    lcd_aux(0);     //RS=RW=0, BL=1
    debounce(20000);
    lcd_aux(3);     //3
    debounce(10000);
    lcd_aux(3);     //3
    debounce(10000);
    lcd_aux(3);     //3
    debounce(10000);
    lcd_aux(2);     //2

    // Entered 4 bit mode
    lcd_aux(2);     lcd_aux(8);     //0x28
    lcd_aux(0);     lcd_aux(8);     //0x08
    lcd_aux(0);     lcd_aux(1);     //0x01
    lcd_aux(0);     lcd_aux(6);     //0x06
    lcd_aux(0);     lcd_aux(0xC);   //0x0F

    while ( (UCB0IFG & UCTXIFG) == 0)   ;          // Wait TXIFG=1
    UCB0CTL1 |= UCTXSTP;                           // STOP
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP)   ;   // Wait STOP
    debounce(50);
}

// Help initialize LCD (RS=RW=0)
// *** Only for initialization ***
void lcd_aux(char dado){
    while ( (UCB0IFG & UCTXIFG) == 0);              // Wait TXIFG=1
    UCB0TXBUF = ((dado<<4)&0XF0) | BIT3;            // PCF7:4 = data;
    debounce(50);
    while ( (UCB0IFG & UCTXIFG) == 0);              // Wait TXIFG=1
    UCB0TXBUF = ((dado<<4)&0XF0) | BIT3 | BIT2;     // E=1
    debounce(50);
    while ( (UCB0IFG & UCTXIFG) == 0);              // Wait TXIFG=1
    UCB0TXBUF = ((dado<<4)&0XF0) | BIT3;            // E=0;
}

void lcdWriteString(char * string) {
    int i = 0;
    for (i = 0; string[i] != 0 && cursor < LCD_LINE_LEN * 2; i++) {
        if (string[i] != '\n') {
            lcdWriteCharExtra(string[i], BIT0);
            cursor++;
        }
        else
            lcd_next_line();
    }
}

void lcdWriteChar(char byte) {
    lcdWriteNibble((byte >> 4) & 0x0F, BIT0);
    lcdWriteNibble(byte & 0x0F, BIT0);
}

void lcdWriteCharExtra(char byte, char isChar) {
    lcdWriteNibble((byte >> 4) & 0x0F, isChar);
    lcdWriteNibble(byte & 0x0F, isChar);
}

void lcd_clear() {
    pcf_write((0x01 & 0xF0) | 0x08);  // Envia a parte alta com 0x08
    pcf_write((0x01 & 0xF0) | 0x0C);  // Envia a parte alta com 0x0C
    pcf_write((0x01 & 0xF0) | 0x08);  // Envia a parte alta com 0x08

    pcf_write((0x01 << 4) | 0x08);    // Envia a parte baixa com 0x08
    pcf_write((0x01 << 4) | 0x0C);    // Envia a parte baixa com 0x0C
    pcf_write((0x01 << 4) | 0x08);    // Envia a parte baixa com 0x08
}

void lcdWriteNibble(char nibble, char isChar) {
    char instr_nibble, instr;
    instr_nibble = BIT3 | isChar;  // prepare nibble
    instr = ((nibble << 4) & 0xF0) | instr_nibble;

    pcf_write(PCF_ADR, instr);
    pcf_write(PCF_ADR, instr | BIT2);
    pcf_write(PCF_ADR, instr & ~BIT2);
}

void lcd_next_line() {
    volatile int i;
    for (i=24 + (LCD_LINE_LEN - cursor); i>0; i--)
        lcdWriteCharExtra(' ', TRUE);
    cursor = LCD_LINE_LEN;
}

void lcd_clear2() {
    volatile int i;
    for (i=(160 - cursor); i>0; i--)
        lcdWriteCharExtra(' ', TRUE);
    cursor = 0;
}
