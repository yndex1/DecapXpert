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
  bool EncoderUeberpruefen();
  void SensorStateChanged();
  void EncoderCounterReset();
  bool bDecapState;
  bool bWithCapState;
  bool bSolenoidState;
  bool bFluessigkeit;
  bool bDecapDoneState;
  AnalogIn senTubeDetection;
  AnalogIn senTubeBeforeBelt;
  AnalogIn senTubeFluessigkeit;
  AnalogIn senTubeBeforeSolenoid;
  DigitalOut doLedFault;
  int iEncoderCounter;
  bool currentState;
  float fTubeDetection;
  float fTubeBeforeBelt;
  float fTubeFluessigkeit;
  float fTubeBeforeSolenoid;

private:
  // Ein / Ausgänge definieren
  //float fTubeDetection;
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