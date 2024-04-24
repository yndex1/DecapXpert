#ifndef SENSORHANDLER_H_
#define SENSORHANDLER_H_

#include <IRSensor.h>
#include <IRSensorDigital.h>
#include <mbed.h>
#include <stdio.h>
#include "ThreadFlag.h"

class SensorHandler {

public:
  SensorHandler();
  virtual ~SensorHandler(); //Destructor
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
  const float UPPER_THRESHOLD;
  const float LOWER_THRESHOLD;

  // Thread variables
  static const float PERIOD; // period of task, given in [s]
  ThreadFlag threadFlag;
  Thread thread;
  Ticker ticker;
  void sendThreadFlag();
  void run();
};

#endif