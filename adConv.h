
#ifndef ADCONV_H
#define ADCONV_H

#include <xc.h>
#define LED0 RB3 // Lets use PORT B pin 0 and connect it to an LED to show if the button has been pressed or not
#define LED1 RB4
volatile bit conversionDone = 0; // Bit flag to signal if the pushbutton is pressed
void initializeADC();
int readADCData();
void startADCConversion();

#endif ADCONV_H