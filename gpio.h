#ifndef GPIO_H_
#define GPIO_H_

#include <msp430.h>
#include <utils.h>

#define ABERTA 1 // pullup
#define FECHADA 0
#define DBC 1000

void gpio_config(void);
int mon_s1(void);
int mon_s2(void);

void led_green(void);
void led_GREEN(void);
void led_red(void);
void led_RED(void);

#endif /* GPIO_H_ */
