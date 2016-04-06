
#include <xc.h>
#include "timer0.h"
#define DEBOUNCE_REQ_COUNT 10 // Ehhh we can make this any reasonable number

void initializeTimer0(){
        
    //Timer initialization
    TMR0 = 100;
    T0CS = 0;
    T0SE = 0;
    PSA = 0;
    PS0 = 0;
    PS1 = 0;
    PS2 = 1;
    
    TMR0IE = 1;
    ei();
}

void flashLed(){
    rtcCounter++;
    if(rtcCounter == 500){
        LED1 = !LED1;
        rtcCounter = 0;
    }
}

void debounceButtons(){

        if(PB0) {
            pbCounter++;
            if(pbCounter >DEBOUNCE_REQ_COUNT &&pb0Released){
                pb0Pressed = 1;
                pb0Released = 0;
            }
        }
        else{
            pbCounter = 0;
            pb0Released = 1;
        }
    
    if(PB1) {
            pbCounter2++;
            if(pbCounter2 >DEBOUNCE_REQ_COUNT &&pb1Released){
                pb1Pressed = 1;
                pb1Released = 0;
            }
        }
        else{
            pbCounter2 = 0;
            pb1Released = 1;
        }
        if(PB2) {
            pbCounter3++;
            if(pbCounter3 >DEBOUNCE_REQ_COUNT &&pb2Released){
                pb2Pressed = 1;
                pb2Released = 0;
            }
        }
        else{
            pbCounter3 = 0;
            pb2Released = 1;
        }
        if(PB3) {
            pbCounter4++;
            if(pbCounter4 >DEBOUNCE_REQ_COUNT &&pb3Released){
                pb3Pressed = 1;
                pb3Released = 0;
            }
        }
        else{
            pbCounter4 = 0;
            pb3Released = 1;
        }        
}
