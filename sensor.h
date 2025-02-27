#ifndef SENSOR_H_
#define SENSOR_H_

#include <msp430.h>
#include <math.h>
#include <utils.h>

extern volatile float diff;
extern volatile float distance;

void ta1_config(void);
void ta0_config(void);
void io_config(void);

#endif /* SENSOR_H_ */
