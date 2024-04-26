/*
 * IRSensor.h
 * Copyright (c) 2024, ZHAW
 * All rights reserved.
 */

#include <cmath>
#include "Solenoid.h"

using namespace std;

/**
 * Creates and initialises the driver to read the distance sensors.
 * @param distanceOk the digital input to read value from.
 */
Solenoid::Solenoid(DigitalOut& output) : output(output) {
    
    
}

/**
 * Deletes this IRSensor object and releases all allocated resources.
 */
Solenoid::~Solenoid() {}

/**
 * This method sets the solenoid true
 * @return a distance value, given in [bool].
 */
bool Solenoid::set() {
    output = true;
    return output;
}

/**
 * This method sets the solenoid true
 * @return a distance value, given in [bool].
 */
bool Solenoid::reset() {
    output = false;
    return output;
}


