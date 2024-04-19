/*
 * Main.cpp
 * Copyright (c) 2024, ZHAW
 * All rights reserved.
 */

#include <stdio.h>
#include <mbed.h>
//#include <IRSensorDigital.h>
#include <EncoderCounter.h>
#include <SpeedController.h>
#include <FastPWM.h>
#include <PM2_Libary.h>


AnalogIn IRTest(PC_3);
float ir_distance_mV = 0.0f;


int main() {

while(true)
{

ir_distance_mV = 1.0e3f * IRTest.read() * 3.3f;

printf("Distanz: %3.3f \r\n", ir_distance_mV);

ThisThread::sleep_for(250ms);

}

return 1;
}