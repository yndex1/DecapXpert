#include <RoundaboutHandler.h>

Roundabouthandler::Roundabouthandler(SensorHandler &sensorHandler):sensorHandler(sensorHandler), doMotorOutput(PB_12)
{
    thread.start(callback(this, &Roundabouthandler::running));
    ticker.attach(callback(this, &Roundabouthandler::sendThreadFlag), PERIOD);
    int iIncrementValue = sensorHandler.iEncoderCounter;
    

}
const float Roundabouthandler::PERIOD = 0.2f;
int iSensorToBelt = 5;
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
    printf("iIncrementValue: %i\n", iIncrementValue);
    while(true)
    {
        ThisThread::flags_wait_any(threadFlag);
        
        
        if(iIncrementValue == iSensorToBelt)
        {
            stopMotor();
            //ThisThread::sleep_for(2s);
            iIncrementValue = 0;
            sensorHandler.EncoderCounterReset();
            startMotor();
        }

    }

}

