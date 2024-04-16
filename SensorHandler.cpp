#include <SensorHandler.h>

SensorHandler::SensorHandler(): bDecapState(false), bSolenoidState(false), bDecapDoneState(false)
{}


void SensorHandler::SensorTasks() {

   //Eingänge definieren
   DigitalIn diTubeDetection(PB_2);
   AnalogIn aiCapAfterDecapping(PC_2);
   AnalogIn aiCapAfterSolenoid(PC_3);

   //Ausgänge definieren
   DigitalOut bit0(PA_0);
   DigitalOut bit1(PA_1);
   DigitalOut bit2(PA_2);

   //Sensor Objekte erstellen
   IRSensorDigital senTubeDetection(diTubeDetection);
   IRSensor senCapAfterDecapping(aiCapAfterDecapping, bit0, bit1, bit2, 0);
   IRSensor senCapAfterSolenoid(aiCapAfterSolenoid, bit0, bit1, bit2, 1);

  while (true) {
    bool bTubeDetection = senTubeDetection.read();
    float fCapAfterDecapping = senCapAfterDecapping.read();
    float fCapAfterSolenoid = senCapAfterSolenoid.read();

    if (bTubeDetection == true)
      bDecapState = true;
    if (fCapAfterDecapping <= 0.5 && fCapAfterDecapping >= 0)
      bSolenoidState = true;
    if (fCapAfterSolenoid <= 0.5 && fCapAfterSolenoid >= 0)
      bDecapDoneState = true;
    ThisThread::sleep_for(25ms);
  }
}