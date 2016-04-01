#include <xc.h>

#define PB0 !RB0 // We?ll NOT the pushbutton input to convert it to active high logic
#define PB1 !RB1
#define PB2 !RB2

volatile bit pb0Pressed = 0; // Bit flag to signal if the pushbutton is pressed
volatile bit pb0Released = 0; // Bit to signal if the pushbutton has been released
volatile unsigned char rtcCounter = 0;

volatile bit pb1Pressed = 0; // Bit flag to signal if the pushbutton is pressed
volatile bit pb1Released = 0; // Bit to signal if the pushbutton has been released
volatile unsigned char rtcCounter2 = 0;

volatile bit pb2Pressed = 0; // Bit flag to signal if the pushbutton is pressed
volatile bit pb2Released = 0; // Bit to signal if the pushbutton has been released
volatile unsigned char rtcCounter3 = 0;

void debounceButtons();