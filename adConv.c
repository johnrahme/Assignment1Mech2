#include <xc.h>
#include "adConv.h"

void initializeADC(){
    TRISA = 0b11111111;
    //Right justified
    ADFM = 1;
    //FOSC 32
    ADCS2 = 0;
    
    PCFG3 = 0;
    PCFG2 = 0;
    PCFG1 = 1;
    PCFG0 = 1;
    
    //ADCON1 = 0b10000000;
    
    ADCON0 = 0b10000001;
    
    //Interrupts
    
    ADIF = 0;
    ADIE = 1;
    PEIE = 1;
    GIE = 1;
}
int readADCData(){
    
       int ADCResult = (ADRESH<<8) + ADRESL ;   //Merging the MSB and LSB
       return ADCResult;
    
}
void startADCConversion(){
       //acquisition time
       __delay_ms(1);
       //Set GO/DONE
       GO = 1;
}