#include <SensorHandler.h>

SensorHandler::SensorHandler(): bDecapState(false), bSolenoidState(false), bDecapDoneState(false), AI(PC_2), SensorDecap(AI)
{

}


void SensorHandler::SensorTasks() {

   //Eingänge definieren
   DigitalIn diTubeDetection(PB_2);
   AnalogIn aiCapAfterDecapping(PC_2);
   AnalogIn aiCapAfterSolenoid(PC_3);

   //Sensor Objekte erstellen
   IRSensorDigital senTubeDetection(diTubeDetection);
   IRSensor senCapAfterDecapping(aiCapAfterDecapping);
   IRSensor senCapAfterSolenoid(aiCapAfterSolenoid);

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