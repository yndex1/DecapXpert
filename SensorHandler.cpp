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
senCapAfterSolenoid(aiCapAfterSolenoid)
{

}


void SensorHandler::SensorTasks() {

  //while (true) {
    bool bTubeDetection = senTubeDetection.read();
    float fCapAfterDecapping = senCapAfterDecapping.read();
    float fCapAfterSolenoid = senCapAfterSolenoid.read();

    if (bTubeDetection == true)
      bDecapState = true;
    if (fCapAfterDecapping <= 0.5 && fCapAfterDecapping >= 0)
      bSolenoidState = true;
    if (fCapAfterSolenoid <= 0.5 && fCapAfterSolenoid >= 0)
      bDecapDoneState = true;
    //ThisThread::sleep_for(25ms);
  //}
}

void SensorHandler::SensorTest()
{

    float Wert = 1.0e3f * 3.3f * SensorDecap.read();
    printf("test: %f", Wert);


}