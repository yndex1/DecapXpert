#include <SensorHandler.h>

SensorHandler::SensorHandler(): 
bDecapState(false), 
bSolenoidState(false), 
bDecapDoneState(false), 
AI(PC_3), 
SensorDecap(AI), 
diTubeDetection(PB_2), 
aiCapAfterDecapping(PC_2),
aiCapAfterSolenoid(PC_3),
senTubeDetection(diTubeDetection),
senCapAfterDecapping(aiCapAfterDecapping),
senCapAfterSolenoid(aiCapAfterSolenoid),
UPPER_THRESHOLD(1000.0f),
LOWER_THRESHOLD(500.0f)
{

}




void SensorHandler::SensorTasks() {

  //while (true) {
    bool bTubeDetection = senTubeDetection.read();
    float fCapAfterDecapping = senCapAfterDecapping.read();
    float fCapAfterSolenoid = senCapAfterSolenoid.read();

    if (bTubeDetection == true) {
      bDecapState = true;
      ThisThread::sleep_for(2000ms);
      bDecapState = false;
    }
    if (fCapAfterDecapping <= UPPER_THRESHOLD && fCapAfterDecapping >= LOWER_THRESHOLD) {
      bSolenoidState = true;
    }
    if (fCapAfterSolenoid <= UPPER_THRESHOLD &&
        fCapAfterSolenoid >= LOWER_THRESHOLD) {
      bDecapDoneState = true;
    }
    //ThisThread::sleep_for(25ms);
  //}
}

void SensorHandler::SensorTest()
{

    float Wert = 1.0e3f * 3.3f * SensorDecap.read();
    printf("test: %f", Wert);


}