#ifndef MOTOR_H_
#define MOTOR_H_

#include <msp430.h>
#include <utils.h>

#define T20ms  20000    // Período total do PWM (20ms)

#define NEUTRAL_PWM  0     // Pulso neutro
#define MODO_PWM  700   // Pulso para rotação

void ta2_config(void);
void motor_on(void);
void motor_off(void);

#endif /* MOTOR_H_ */
