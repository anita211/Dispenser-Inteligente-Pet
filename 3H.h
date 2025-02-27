#ifndef TRESH_H_
#define TRESH_H_

#include <msp430.h>
#include <utils.h>
#include <gpio.h>

#define SEC_COUNT 32768    // Contagens de ACLK para 1 segundo

extern volatile unsigned char minuteFlag;

void tb0_config(void);
void reset_sec(void);

#endif // TRESH_H_
