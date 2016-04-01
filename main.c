#include <xc.h>
#include "motor.h"

#pragma config BOREN = OFF, CPD = OFF, WRT = OFF, FOSC = HS, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = OFF //for XC8 compiler
#define TMR0_VAL 100
#define LED0 RB2 // Lets use PORT B pin 0 and connect it to an LED to show if the button has been pressed or not
#define LED1 RB3
#define PB0 !RB0 // We?ll NOT the pushbutton input to convert it to active high logic
#define PB1 !RB1
#define DEBOUNCE_REQ_COUNT 10 // Ehhh we can make this any reasonable number
//Defining stepping sequence

volatile bit pb0Pressed = 0; // Bit flag to signal if the pushbutton is pressed
volatile bit pb0Released = 0; // Bit to signal if the pushbutton has been released
volatile unsigned char rtcCounter = 0;

volatile bit pb1Pressed = 0; // Bit flag to signal if the pushbutton is pressed
volatile bit pb1Released = 0; // Bit to signal if the pushbutton has been released
volatile unsigned char rtcCounter2 = 0;

//Oscillator (Hz) You need this to call the __delay_my() function
// What do we want the program to do? How would we approach initialising the program?

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
void initialise (void){
// Let?s try using PORTB. Configure PORTB.
// Hint: Read the datasheet, it will be your best friend in this subject
    TRISB = 0b00000011;
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
    
    while(1){
        if(pb0Pressed){
            LED0 = !LED0;
            moveDeg(3.75);
            pb0Pressed = 0;
        }
        if(pb1Pressed){
            LED1 = !LED1;
            moveDeg(180);
            pb1Pressed = 0;
        }
        __delay_ms(20);
    }
}