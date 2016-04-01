
#include <xc.h>

#define STEP0 0b00111100
#define STEP1 0b00101110
#define STEP2 0b00101011
#define STEP3 0b00100111
#define STEP4 0b00110101
#define STEP5 0b00010111
#define STEP6 0b00011011
#define STEP7 0b00011110
#define _XTAL_FREQ 20000000
signed char cstep = 0; //stores current step
int allSteps[] = {STEP0, STEP1, STEP2, STEP3, STEP4, STEP5, STEP6, STEP7};

void move(char steps, char direction);
void moveDeg(double deg);
