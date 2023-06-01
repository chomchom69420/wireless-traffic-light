#include "delay.h"

static volatile unsigned int delay_count[2] = {0, 0};
static unsigned int limit[2] = {0, 0};
static unsigned char initialized = 0;

void delay_init(){
    if(!initialized)
    {
        //Set prescaler according to timing ranges

        //Set overflow value 

        //Set counter to 0 

        //Enable interrupts 

        //Set initialized to prevent further initialization
        initialized=1;
    }
}

