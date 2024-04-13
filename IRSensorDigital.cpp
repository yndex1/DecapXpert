/*
 * IRSensor.h
 * Copyright (c) 2024, ZHAW
 * All rights reserved.
 */

#include <cmath>
#include "IRSensorDigital.h"

using namespace std;

/**
 * Creates and initialises the driver to read the distance sensors.
 * @param distanceOk the analog input to read a distance value from.
 */
IRSensorDigital::IRSensorDigital(DigitalIn& distanceOk) : distanceOk(distanceOk) {
    
    
}

/**
 * Deletes this IRSensor object and releases all allocated resources.
 */
IRSensorDigital::~IRSensorDigital() {}

/**
 * This method reads from the distance sensor.
 * @return a distance value, given in [m].
 */
bool IRSensorDigital::read() {
       
    return distanceOk;
}

/**
 * The empty operator is a shorthand notation of the <code>read()</code> method.
 */
IRSensorDigital::operator float() {
    
    return read();
}
