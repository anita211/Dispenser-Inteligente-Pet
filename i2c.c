#include <i2c.h>

// P3.0 = SDA e P3.1=SCL
void i2c_config(void){
    UCB0CTL1 |= UCSWRST;    // Reset UCSI B0
    UCB0CTL0 = UCSYNC |     // Sync
               UCMODE_3 |   // I2C mode
               UCMST;       // Master
    UCB0BRW = BR_100K;      // 100 kbps (clock calculated = clock selected / (UCB0BRW + UCB1BRW * 256)
    P3SEL |=  BIT1 | BIT0;  // Use dedicated module
    UCB0CTL1 = UCSSEL_2;    // SMCLK and remove reset
}

// Read PCF's port
int pcf_read(char address){
    int data;
    UCB0I2CSA = address;                // Slave address
    UCB0CTL1 &= ~UCTR;                  // Master RX
    UCB0CTL1 |= UCTXSTT;                // START
    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT);

    UCB0CTL1 |= UCTXSTP;                // STOP + NACK
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP)   ;   // Wait STOP
    while ( (UCB0IFG & UCRXIFG) == 0);  // Wait RX

    data=UCB0RXBUF;

    return data;
}

// Write data in port
void pcf_write(char address, char dado){
    UCB0I2CSA = address;        // Slave address
    UCB0CTL1 |= UCTR    |       // Master TX
                UCTXSTT;        // START

    while ( (UCB0IFG & UCTXIFG) == 0)   ;          // Wait TXIFG=1

    UCB0TXBUF = dado;                              // Write data

    while ( (UCB0CTL1 & UCTXSTT) == UCTXSTT)   ;   // Wait STT=0
    if ( (UCB0IFG & UCNACKIFG) == UCNACKIFG) {     // NACK?
        led_RED();
        while(TRUE);
    }

    UCB0CTL1 |= UCTXSTP;                        // STOP
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP)   ;   // Wait STOP
}

// Test address in I2C
// TRUE if ACK
int pcf_teste(char adr){
    UCB0I2CSA = adr;                            // PCF address
    UCB0CTL1 |= UCTR | UCTXSTT;                 // START, Master transmitting
    while ( (UCB0IFG & UCTXIFG) == 0);          // Wait START
    UCB0CTL1 |= UCTXSTP;                        // STOP
    while ( (UCB0CTL1 & UCTXSTP) == UCTXSTP);   // Wait STOP
    if ((UCB0IFG & UCNACKIFG) == 0)     return TRUE;
    else                                return FALSE;
}
