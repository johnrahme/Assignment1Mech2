
#ifndef ADCONV_H
#define ADCONV_H
#include <xc.h>
#include "common.h"
volatile bit conversionDone = 0; // Bit flag to signal if the pushbutton is pressed
void initializeADC();
int readADCData();
int readADCMeter();
void startADCConversion();


#endif ADCONV_H