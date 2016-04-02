#include <xc.h>
#include "motor.h"
#include "timer0.h"
#include "adConv.h"

#pragma config BOREN = OFF, CPD = OFF, WRT = OFF, FOSC = HS, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF //for XC8 compiler
#define TMR0_VAL 100

bit motorToggle = 0;

void interrupt isr(void){
    if (T0IF){ // If Timer 0 overflow occurred
        T0IF = 0; // Clear flag
        TMR0 = TMR0_VAL;
        debounceButtons();
    }
    if(ADIF){
        conversionDone = 1;
        ADIF = 0;
    }
}
void initialise (void){
// Let?s try using PORTB. Configure PORTB.
// Hint: Read the datasheet, it will be your best friend in this subject
    TRISB = 0b00000111;
    TRISC = 0;
    
    LED0 = 1;
    LED1 = 1;
    
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

void main (void) {
//initialise the program
    initialise();
    initializeADC();
    startADCConversion();

    //ADCON0 = ADCON0 | 0b00000100;
    while(1){
        
        
        if(conversionDone){
            conversionDone = 0;
            int result = readADCData();
            startADCConversion();
            
        }
        if(pb0Pressed){
            move(1,0);
            pb0Pressed = 0;
        }
        if(pb1Pressed){
            move(1,1);
            pb1Pressed = 0;
        }
        if(pb2Pressed){
            if(motorToggle){
                moveDeg(-180);
            }
            else{
                moveDeg(180);
            }
            motorToggle = !motorToggle;
            pb2Pressed = 0;
        }
        __delay_ms(20);
    }
}