#include <SensorHandler.h>

SensorHandler::SensorHandler() {

  // Eingänge definieren
  DigitalIn diTubeDetection(PB_2);
  AnalogIn aiCapAfterDecapping(PC_2);
  AnalogIn aiCapAfterSolenoid(PC_3);

  // Ausgänge definieren
  DigitalOut bit0(PF_0);
  DigitalOut bit1(PF_1);
  DigitalOut bit2(PF_2);

  // Sensor Objekte erstellen
  IRSensorDigital senTubeDetection(diTubeDetection);
  IRSensor senCapAfterDecapping(aiCapAfterDecapping, bit0, bit1, bit2, 0);
  IRSensor senCapAfterSolenoid(aiCapAfterSolenoid, bit0, bit1, bit2, 1);

}

int SensorHandler::SensorTasks() {

  bool  bTubeDetection = senTubeDetection.read();
  float  fCapAfterDecapping = senCapAfterDecapping.read();
  float  fCapAfterSolenoid = senCapAfterSolenoid.read();

    
return 0;
}