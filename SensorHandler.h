#ifndef SENSORHANDLER_H_
#define SENSORHANDLER_H_

#include <IRSensor.h>
#include <IRSensorDigital.h>
#include <mbed.h>
#include <stdio.h>

class SensorHandler {

public:
  SensorHandler();
  //Sensor 0 , 1, 2
  int SensorTasks();

private:
  // Ein / Ausgänge definieren
  bool bTubeDetection;
  float fCapAfterDecapping;
  float fCapAfterSolenoid;

  IRSensorDigital senTubeDetection;
  IRSensor senCapAfterDecapping;
  IRSensor senCapAfterSolenoid;

};

#endif