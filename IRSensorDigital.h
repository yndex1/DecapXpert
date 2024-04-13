/*
 * IRSensorDigital.h
 * Copyright (c) 2024, ZHAW
 * All rights reserved.
 */

#ifndef IR_SENSOR_DIGITAL_H_
#define IR_SENSOR_DIGITAL_H_

#include <cstdlib>
#include <mbed.h>

/**
 * This class implements a driver to read the distance sensors
 * of the ROME2 mobile robot.
 */
class IRSensorDigital {

    public:
        
                IRSensorDigital(DigitalIn& distanceOk);
        virtual ~IRSensorDigital();
        float   read();
                operator float();
        
    private:
        
        DigitalIn&   distanceOk;

};

#endif /* IR_SENSOR_DIGITAL_H_ */
