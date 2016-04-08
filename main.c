#include <xc.h>
#include "motor.h"
#include "timer0.h"
#include "adConv.h"
#include "lcd.h"
#include "common.h"

#pragma config BOREN = OFF, CPD = OFF, WRT = OFF, FOSC = HS, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF //for XC8 compiler
#define TMR0_VAL 100

bit motorToggle = 0;

void interrupt isr(void){
    if (T0IF){ // If Timer 0 overflow occurred
        T0IF = 0; // Clear flag
        TMR0 = TMR0_VAL;
        flashLed();
        debounceButtons();
        lcdRefresh();
    }
    if(ADIF){
        conversionDone = 1;
        ADIF = 0;
    }
}
void initialise (void){
// Let?s try using PORTB. Configure PORTB.
// Hint: Read the datasheet, it will be your best friend in this subject
    TRISB = 0b00001111;
    TRISC = 0;
    
    LED0 = 1;
    LED1 = 1;
    
    initializeTimer0();
    initializeADC();
    setupLCD();
    initializeMotor();

    
    
}

void main (void) {
//initialise the program
    initialise();
    startADCConversion();   

    //ADCON0 = ADCON0 | 0b00000100;
    while(1){
        

        if(conversionDone){
            conversionDone = 0;
            int result = readADCData();
            int resultInMeters = readADCMeter();
            if(updateLcdIRData){
                lcdSetCursor(0x00);
                lcdWriteToDigitBCD(result);
                lcdSetCursor(0x0B);
                lcdWriteToDigitBCD(resultInMeters);
                updateLcdIRData = 0;
            }
            //lcdWriteString("Hello World!");
            startADCConversion();
            
        }
        if(pb0Pressed){
            move(1,1);
            pb0Pressed = 0;
        }
        if(pb1Pressed){
            move(1,0);
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
        if(pb3Pressed){
            LED0 = !LED0;
            pb3Pressed = 0;
        }

        __delay_ms(20);
    }
}