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
  bool bDecapState;
  bool bSolenoidState;
  bool bDecapDoneState;
 

  


private:
  // Ein / Ausgänge definieren
  bool bTubeDetection;
  float fCapAfterDecapping;
  float fCapAfterSolenoid;

};

#endif