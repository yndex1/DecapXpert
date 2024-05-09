#include "mbed.h"
#include <Solenoid.h>
#include "ThreadFlag.h"
#include <SensorHandler.h>

#ifndef ROUNDABOUTHANDLER_H
#define ROUNDABOUTHANDLER_H

/** Library that allows faster and/or higher resolution PWM output
  *
  * Library can directly replace standard mbed PWM library.
  *
  * Contrary to the default mbed library, this library takes doubles instead of floats. The compiler will autocast if needed,
  * but do take into account it is done for a reason, your accuracy will otherwise be limitted by the floating point precision.
  */
class Roundabouthandler {

    public:
        virtual ~Roundabouthandler();
        Roundabouthandler(SensorHandler &sensorHandler);
        DigitalOut doMotorOutput;
        int iIncrementCounter();
        
        int iSensorToBelt = 34;
        void startMotor();
        void stopMotor();
        //Thread variables
        static const float PERIOD; // period of task, given in [s]
        ThreadFlag threadFlag;
        Thread thread;
        Ticker ticker;
        void sendThreadFlag();
        void running();
        int iIncrementValue;
    private:
        SensorHandler &sensorHandler;
        
};

#endif