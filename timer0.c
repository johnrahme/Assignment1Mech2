
#include <xc.h>
#include "timer0.h"
#define DEBOUNCE_REQ_COUNT 10 // Ehhh we can make this any reasonable number


void debounceButtons(){

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
        if(PB2) {
            rtcCounter3++;
            if(rtcCounter3 >DEBOUNCE_REQ_COUNT &&pb2Released){
                pb2Pressed = 1;
                pb2Released = 0;
            }
        }
        else{
            rtcCounter3 = 0;
            pb2Released = 1;
        }
}
