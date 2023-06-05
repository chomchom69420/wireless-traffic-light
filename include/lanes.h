#ifndef LANES_H_INCLUDED
#define LANES_H_INCLUDED

/*
This method is used to initialize the lanes fsm by setting the first lane as the go and stopping traffic on other lanes 
*/
void lanes_start_signals();  


/*
This method is used to update the lanes fsm to change state from allow traffic on one lane to the other depending on the timer values 
*/
void lanes_update();

#endif