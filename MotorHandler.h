#ifndef MOTORHANDLER_H_
#define MOTORHANDLER_H_

#include <mbed.h>
#include <stdio.h>
#include <SpeedController.h>
#include <SensorHandler.h>

class MotorHandler {

public:
  MotorHandler(bool &bDecapState, bool &bSolenoidState, bool &bDecapDoneState);
  void MotorTasks();
  bool bStateMotorRoundabout;
  bool bStateMotorBelt;
 

private:
    bool& bDecapState;
    bool& bSolenoidState; 
    bool& bDecapDoneState;
    //SpeedController speedController_MRoundabout;
    //SpeedController speedController_MBelt;
    //MotorEnable


};
#endif