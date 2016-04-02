#include <xc.h>
#define _XTAL_FREQ 20000000

void initializeADC(){

    //ADFM = 1;
    ADCON1 = 0b10000000;
    
    ADCON0 = 0b100000001;
    
    //Interrupts
    
    ADIF = 0;
    ADIE = 1;
    PEIE = 1;
    GIE = 1;
}