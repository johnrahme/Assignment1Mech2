
#include <xc.h>

volatile bit conversionDone = 0; // Bit flag to signal if the pushbutton is pressed
void initializeADC();
void readData();