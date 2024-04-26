#ifndef MOTORHANDLER_H_
#define MOTORHANDLER_H_

#include <mbed.h>
#include <stdio.h>
#include <SpeedController.h>
#include <SensorHandler.h>
#include <Solenoid.h>

class MotorHandler {

public:
    virtual ~MotorHandler();
  MotorHandler(bool &bDecapState, bool &bSolenoidState, bool &bDecapDoneState);
  void MotorStop();
  void MotorTasks();
  
 

private:
    bool& bDecapState;
    bool& bSolenoidState; 
    bool& bDecapDoneState;
    
    //Geschwindigkeitskonstanten
    const float SPEED_ROUNDABOUT;
    const float SPEED_BELT;
    const float SPEED_STOP;

    //Motorenkonstanten
    //I/O definieren
//MotorEnable
DigitalOut doEnable_motors;
DigitalOut doSolenoid;
//Motor PWM definieren
FastPWM pwm_MotorRoundabout;
FastPWM pwm_MotorBelt;

//Encoder definieren
EncoderCounter encoder_MotorRoundabout;
EncoderCounter encoder_MotorBelt; // create encoder objects to read in the encoder counter values

//pwm Periode definieren
float pwm_period_s;    // define pwm period time in seconds and create FastPWM objects to command dc motors
// create SpeedController and PositionController objects, default parametrization is for 100:1 gear box
float max_voltage;                  // define maximum voltage of battery packs, adjust this to 6.0f V if you only use one batterypack
float counts_per_turn_MRoundabout;  // define counts per turn at gearbox end: counts/turn * gearratio  -->> von 20 auf 10 geändert, jetzt stimmen 1
float counts_per_turn_MBelt;     
float kn_MRoundabout;               // define motor constant in rpm per V
float kn_MBelt;                  
float k_gear_MRoundabout;          // define additional ratio in case you are using a dc motor with a different gear box, e.g. 100:1
float k_gear_MBelt;          
float kp;                           // define custom kp, this is the default speed controller gain for gear box 78.125:1
float max_speed_rps;                 // define maximum speed that the position controller is changig the speed, has to be smaller or equal to kn * max_voltage$

SpeedController speedController_MRoundabout;
SpeedController speedController_MBelt;

};
#endif