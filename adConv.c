#include <xc.h>
#include "adConv.h"
#define _XTAL_FREQ 20000000

void initializeADC(){
    TRISA = 0b11111111;
    //Right justified
    ADFM = 1;
    //FOSC 32
    ADCS2 = 0;
    
    PCFG3 = 0;
    PCFG2 = 0;
    PCFG1 = 1;
    PCFG0 = 0;
    
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

        if(ADCResult>1000){
            LED0 = 0;
            LED1 = 1;
        }
        else if (ADCResult<1000&&ADCResult>400){
            LED0 = 1;
            LED1 = 0;
        }

        else{
            LED0 = 1;
            LED1 = 1;
        }
       return ADCResult;
    
}
void startADCConversion(){
       //acquisition time
       __delay_ms(1);
       //Set GO/DONE
       GO = 1;
}