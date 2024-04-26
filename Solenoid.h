/*
 * IRSensorDigital.h
 * Copyright (c) 2024, ZHAW
 * All rights reserved.
 */

#ifndef SOLENOID_H_
#define SOLENOID_H_

#include <cstdlib>
#include <mbed.h>

/**
 * This class implements a driver to read the distance sensors
 * of the ROME2 mobile robot.
 */
class Solenoid {

    public:
        
                Solenoid(DigitalOut& output);
        virtual ~Solenoid();
        bool   set();
        bool   reset();
        

        
    private:
        
        DigitalOut&   output;

};

#endif /* IR_SENSOR_DIGITAL_H_ */
