#include <utils.h>

void debounce(long limite){
    volatile long cont=0;
    while (cont++ < limite);
}
void delayCycles(unsigned int modo) {
    switch(modo) {
        case 0:  // Modo P
            __delay_cycles(15000000);  // 15 milhões de ciclos
        case 1:  // Modo M
            __delay_cycles(20000000);  // 20 milhões de ciclos
        case 2:  // Modo G
            __delay_cycles(25000000);  // 25 milhões de ciclos
    }
}
