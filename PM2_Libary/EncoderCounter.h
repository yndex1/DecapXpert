/*
 * EncoderCounter.h
 * Copyright (c) 2018, ZHAW
 * All rights reserved.
 */

#ifndef ENCODER_COUNTER_H_
#define ENCODER_COUNTER_H_

#include <cstdlib>
#include <stdint.h>
#include <mbed.h>

/**
 * This class implements a driver to read the quadrature
 * encoder counter of the STM32 microcontroller.
 */
class EncoderCounter
{

public:

    EncoderCounter(PinName a, PinName b);
    virtual     ~EncoderCounter();
    void        reset();
    void        reset(int16_t offset);
    int16_t     read();
    operator int16_t();

private:

    TIM_TypeDef*    TIM;
};

#endif /* ENCODER_COUNTER_H_ */



