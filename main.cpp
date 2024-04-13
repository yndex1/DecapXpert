/*
 * Main.cpp
 * Copyright (c) 2024, ZHAW
 * All rights reserved.
 */

#include <stdio.h>
#include <mbed.h>
#include <IRSensorDigital.h>

int main() {
    
    // create miscellaneous periphery objects
    
    DigitalIn button(BUTTON1);
    DigitalOut led(LED1);

    DigitalIn testIrDigital(PB_2);
    IRSensorDigital TestSignal(testIrDigital);
    
    
    ThisThread::sleep_for(500ms);
    
    
    while (true) {
        
        //led = !led;
        printf("Wert: %d\r\n", TestSignal.read());
        

        ThisThread::sleep_for(250ms);
    }
}
