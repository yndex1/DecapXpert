#ifndef SENSORHANDLER_H_
#define SENSORHANDLER_H_

#include <IRSensor.h>
#include <IRSensorDigital.h>
#include <mbed.h>
#include <stdio.h>

class SensorHandler {

public:

  SensorHandler();
  void SensorTasks();
  void SensorTest();
  bool bDecapState;
  bool bSolenoidState;
  bool bDecapDoneState;
  AnalogIn AI;
  IRSensor SensorDecap;
  DigitalIn diTubeDetection;
  AnalogIn aiCapAfterDecapping;
  AnalogIn aiCapAfterSolenoid;
  IRSensorDigital senTubeDetection;
  IRSensor senCapAfterDecapping; 
  IRSensor senCapAfterSolenoid;
 

  


private:
  // Ein / Ausgänge definieren
  bool bTubeDetection;
  float fCapAfterDecapping;
  float fCapAfterSolenoid;

};

#endif