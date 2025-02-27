#ifndef I2C_H_
#define I2C_H_

#include <msp430.h>
#include <utils.h>

#define BR_100K    11  //SMCLK/100K = 11
#define BR_50K     21  //SMCLK/50K  = 21
#define BR_10K    105  //SMCLK/10K  = 105

void i2c_config(void);

int pcf_read(char address);
void pcf_write(char address, char dado);
int pcf_teste(char adr);


#endif /* I2C_H_ */
