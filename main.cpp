/*
 * Main.cpp
 * Copyright (c) 2024, ZHAW
 * All rights reserved.
 */

#include <stdio.h>
#include <mbed.h>

int main() {
    
    // create miscellaneous periphery objects
    
    DigitalIn button(BUTTON1);
    DigitalOut led(LED1);
    
    
    ThisThread::sleep_for(500ms);
    
    
    while (true) {
        
        led = !led;
        

        ThisThread::sleep_for(250ms);
    }
}
