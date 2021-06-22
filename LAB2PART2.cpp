/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "platform/mbed_thread.h"


// Blinking rate in milliseconds
#define BLINKING_RATE_MS                                                    500
#define BUTTON PC_13

//ticker object
Ticker blinky;
// Initialise the digital pin PA_5 as an output
DigitalOut led(PA_5);


//button as InterruptIn
InterruptIn     button(USER_BUTTON);

// Button handler: Toggle a Boolean variable. This variable will reflect if the LED has to be blinking or off.
volatile bool   buttonHandler = false; 
// blink function
void blink(){
 led = !led;
}
void buttonState()
{
    if(!button)
    {
        buttonHandler=true;
        
    }
   else
   {
       buttonHandler=false;
       
    }
}
//Button ISR:If the Boolean variable is true, toggle the LED.Otherwise turn LED off.
void button_isr()
{
    
    buttonState();
    
    if(buttonHandler==true)
    {
    blink(); 
    }
    else
    {
        led=0;
    }
}


int main()
{
    
    //configure button with internal pull up resistor
    button.mode(PullUp);  
    //Attach the button ISR to be called on the falling edge when button is pressed.
    button.fall(&buttonState);
    //Attach the Ticker ISR to be called every 500ms
    blinky.attach(&button_isr, 0.50); //Interrupt sub-routine blink() will be called every 0.500s 
    
    while(1);
    
}
