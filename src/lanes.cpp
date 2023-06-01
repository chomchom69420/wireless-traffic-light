#include "lanes.h"
#include "delay.h"

enum Signal { lane1, lane2 } signal_state;

int comm_done =0; //flag to store if latest value has been communicated or not 

void lanes_start_signals() {
    //Start with allowing traffic on first lane 
    signal_state = lane1;
}

void lane_update() {
    switch (signal_state)
    {
    case lane1:
        if(delay_isdone(0))
        {
            //if the delay is done move to the next lane
            signal_state=lane2;
            comm_done=0;
        }

        if(!comm_done)
        {
            //Send MQTT message to slave 1 to display green
            //Send MQTT message to slave 2 to display red
            comm_done=1;
        }
        
        break;
    case lane2:
        if(delay_isdone(0))
        {
            //move to next lane 
            signal_state=lane1;
        }

        if(!comm_done)
        {
            //Send MQTT message to slave 1 to display red
            //Send MQTT message to slave 2 to display green
            comm_done=1;
        }
        break;
    default:
        break;
    }
}