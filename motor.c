/*
 * File:   motor.c
 * Author: JohnMac
 *
 * Created on den 1 april 2016, 16:36
 */


#include <xc.h>
#include <math.h>
#include "motor.h"
#include "lcd.h"
#define CLOCKWISE 1
#define COUNTER_CLOCKWISE 0
#define STEPS_PER_ROTATION 48
#define DEG_PER_STEP 7.5
#define SPEED 20

void initializeMotor(){
    PORTC = halfSteps[0];
    lcdSetCursor(0x40);
    lcdWriteToDigitBCD(nrOfSteps,4,1);
}

void move(char steps, char direction){
    for(char i = 0; i<steps; i++){
         if(cstep == 7 && direction == CLOCKWISE){
            PORTC = halfSteps[0];
            cstep = 0;
         }
         else if(cstep == 0 && direction == COUNTER_CLOCKWISE){
            PORTC = halfSteps[7];
            cstep = 7;
         }
         else if (cstep >= 0 && cstep <= 7){
             if(direction == CLOCKWISE){
                PORTC = halfSteps[cstep+1]; 
                cstep++;
             }
             else if(direction == COUNTER_CLOCKWISE){
                PORTC = halfSteps[cstep-1];
                cstep--;
             }
             
         }
         else{
               PORTC = 0x00;
         }
         
         lcdSetCursor(0x40);
         if(direction==CLOCKWISE){
             nrOfSteps++;
             lcdWriteToDigitBCD(nrOfSteps,4,1);
         }
         else{
             nrOfSteps--;
             lcdWriteToDigitBCD(nrOfSteps,4,1);
         }
        __delay_ms(SPEED);
    }
}

void moveDeg(double deg){
    char stepsToMove;
    if(deg<0){
        stepsToMove = (char) round(-deg/(DEG_PER_STEP/2.0));
        move(stepsToMove,0);
    }
    else{
        stepsToMove = (char) round(deg/(DEG_PER_STEP/2.0)); 
        move(stepsToMove,1);
    }
}
