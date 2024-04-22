#include <MotorHandler.h>


MotorHandler::MotorHandler(bool &bDecapState, bool &bSolenoidState, bool &bDecapDoneState):
 bStateMotorRoundabout(true), 
 bStateMotorBelt(false), 
 bDecapState(bDecapState), 
 bSolenoidState(bSolenoidState), 
 bDecapDoneState(bDecapDoneState)
{


}

void MotorHandler::MotorTasks(){

//MotorEnable
DigitalOut enable_motors(PB_15);
//Motor PWM definieren
FastPWM pwm_MotorRoundabout(PB_13);
FastPWM pwm_MotorBelt(PA_9);

//Encoder definieren
EncoderCounter encoder_MotorRoundabout(PA_6, PC_7);
EncoderCounter encoder_MotorBelt(PB_6, PB_7); // create encoder objects to read in the encoder counter values

//pwm Periode definieren
float pwm_period_s = 0.00005f;    // define pwm period time in seconds and create FastPWM objects to command dc motors

// create SpeedController and PositionController objects, default parametrization is for 100:1 gear box
float max_voltage = 12.0f;                  // define maximum voltage of battery packs, adjust this to 6.0f V if you only use one batterypack
float counts_per_turn_MRoundabout = 20.0f * 195.0f;  // define counts per turn at gearbox end: counts/turn * gearratio  -->> von 20 auf 10 geändert, jetzt stimmen 1
float counts_per_turn_MBelt = 20.0f * 391.0f;     
float kn_MRoundabout = 195.0f / 12.0f;               // define motor constant in rpm per V
float kn_MBelt = 391.0f / 12.0f;                  
float k_gear_MRoundabout = 195.0f / 100.0f;          // define additional ratio in case you are using a dc motor with a different gear box, e.g. 100:1
float k_gear_MBelt = 391.0f / 100.0f;          
float kp = 0.1f;                            // define custom kp, this is the default speed controller gain for gear box 78.125:1

float max_speed_rps = 1.0f;                 // define maximum speed that the position controller is changig the speed, has to be smaller or equal to kn * max_voltage$
SpeedController speedController_MRoundabout(counts_per_turn_MRoundabout * k_gear_MRoundabout, kn_MRoundabout / k_gear_MRoundabout, max_voltage, pwm_MotorRoundabout, encoder_MotorRoundabout);
SpeedController speedController_MBelt(counts_per_turn_MBelt * k_gear_MBelt, kn_MBelt / k_gear_MBelt, max_voltage, pwm_MotorBelt, encoder_MotorBelt);


//while(true){
    bStateMotorBelt = bDecapState;


    if(bDecapState)
    {
        enable_motors = 1;
        speedController_MRoundabout.setDesiredSpeedRPS(0.6f);
    }
    if(bStateMotorBelt == 1){
        //Motor Controller Solenoid startet
    }
//}

printf("motortasks\r\n");


}
