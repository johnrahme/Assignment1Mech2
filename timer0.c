
#include <xc.h>
#include "timer0.h"

void interrupt isr(void){
    if (T0IF){ // If Timer 0 overflow occurred
    T0IF = 0; // Clear flag
    TMR0 = TMR0_VAL;
    
    // Reset the timer0 start count
    // Increment counter
        if(PB0) {
            rtcCounter++;
            if(rtcCounter >DEBOUNCE_REQ_COUNT &&pb0Released){
                pb0Pressed = 1;
                pb0Released = 0;
            }
        }
        else{
            rtcCounter = 0;
            pb0Released = 1;
        }
    
    if(PB1) {
            rtcCounter2++;
            if(rtcCounter2 >DEBOUNCE_REQ_COUNT &&pb1Released){
                pb1Pressed = 1;
                pb1Released = 0;
            }
        }
        else{
            rtcCounter2 = 0;
            pb1Released = 1;
        }
    }
}
