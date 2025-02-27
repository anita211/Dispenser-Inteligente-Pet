#ifndef LCD_H_
#define LCD_H_

#include <msp430.h>
#include <utils.h>

// Address of PCF_8574 (LCD)
// P3.0 ==> SDA
// P3.1 ==> SCL
#define PCF_ADR1 0x3F
#define PCF_ADR2 0x27
#define PCF_ADR  PCF_ADR2

#define LCD_LINE_LEN 0x10
#define FRASES_TAMANHO 4
#define LCD_LINHA_MAX 16

void lcd_init();
void lcd_aux(char dado);

void lcdWriteNibble(char nibble, char isChar);
void lcdWriteChar(char byte);
void lcdWriteCharExtra(char byte, char isChar);
void lcdWriteString(char * string);
void lcd_next_line();
void lcd_clear();
void lcd_clear2();

extern volatile int cursor;

#endif /* LCD_H_ */
