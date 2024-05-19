#include <RoundaboutHandler.h>

Roundabouthandler::Roundabouthandler(SensorHandler &sensorHandler):sensorHandler(sensorHandler), doMotorOutput(PB_12)
{    
    startMotor();
    thread.start(callback(this, &Roundabouthandler::running));
    ticker.attach(callback(this, &Roundabouthandler::sendThreadFlag), PERIOD);

}
const float Roundabouthandler::PERIOD = 0.01f;


Roundabouthandler::~Roundabouthandler() {
        ticker.detach();
}
void Roundabouthandler::sendThreadFlag() {
    
    thread.flags_set(threadFlag);
}

int Roundabouthandler::iIncrementCounter()
{
    return iIncrementValue;
}

void Roundabouthandler::startMotor()
{
    doMotorOutput = 1;
}

void Roundabouthandler::stopMotor()
{
    doMotorOutput = 0;
}

void Roundabouthandler::running()
{
    
    while(true)
    {
        ThisThread::flags_wait_any(threadFlag);
        
        int iIncrementValue = sensorHandler.iEncoderCounter;
        printf("iIncrementValue: %i iSensorToBelt: %i\n", iIncrementValue, iSensorToBelt);

        //Wait for Decapping State and Cap on Tube
        if (sensorHandler.bDecapState == true && sensorHandler.bWithCapState == true) {
          // if Increment Value of Encoder is Position in front of Belt Stop Roundabout
          if (iIncrementValue >= iSensorToBelt) {
            stopMotor();
            ThisThread::sleep_for(2s);
            iIncrementValue = 0;
            sensorHandler.EncoderCounterReset();
            startMotor();
            sensorHandler.bDecapState = false;
            sensorHandler.bWithCapState = false;
          }
        }
    }

}

