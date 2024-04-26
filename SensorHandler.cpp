#include <SensorHandler.h>

SensorHandler::SensorHandler(): 
bDecapState(false), 
bSolenoidState(false), 
bDecapDoneState(false), 
AI(PC_3), 
SensorDecap(AI), 
diTubeDetection(PB_2),  
aiCapAfterDecapping(PC_2),
aiCapAfterSolenoid(PC_5),
senTubeDetection(diTubeDetection),
senCapAfterDecapping(aiCapAfterDecapping),
senCapAfterSolenoid(aiCapAfterSolenoid),
UPPER_THRESHOLD(1000.0f),
LOWER_THRESHOLD(500.0f)
{
    thread.start(callback(this, &SensorHandler::SensorTasks));
    ticker.attach(callback(this, &SensorHandler::sendThreadFlag), PERIOD);
}

const float SensorHandler::PERIOD = 1.0f;                  // period of task, given in [s]

/**
 * Deletes the SensorHandler object.
 */
SensorHandler::~SensorHandler() {
    
    ticker.detach();
}

/**
 * This method is called by the ticker timer interrupt service routine.
 * It sends a flag to the thread to make it run again.
 */
void SensorHandler::sendThreadFlag() {
    
    thread.flags_set(threadFlag);
}

void SensorHandler::SensorTasks() {



  while (true) {

    // wait for the periodic thread flag

    ThisThread::flags_wait_any(threadFlag);
    

    bool bTubeDetection = senTubeDetection.read();
    float fCapAfterDecapping = senCapAfterDecapping.read();
    float fCapAfterSolenoid = senCapAfterSolenoid.read();

    printf("Sensortasks\r\n");

    if (bTubeDetection == true) {
      bDecapState = true;
      printf("decapStateTrue\r\n");
      //bDecapState = false;
    }
    else bDecapState = false;

    if (fCapAfterDecapping <= UPPER_THRESHOLD && fCapAfterDecapping >= LOWER_THRESHOLD) {
      bSolenoidState = true;
    }
    
    if (fCapAfterSolenoid <= UPPER_THRESHOLD && fCapAfterSolenoid >= LOWER_THRESHOLD) {
      bDecapDoneState = true;
    }
    //ThisThread::sleep_for(25ms);
  }
}

void SensorHandler::SensorTest()
{
    //AnalogIn AI1(PC_2);
    //AnalogIn AI2(PC_5);


    //printf("PC2: %f  PC5: %f\r\n", 1000.0f*3.3f*AI1.read(),1000.0f*3.3f*AI2.read());


}