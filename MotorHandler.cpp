#include <MotorHandler.h>



MotorHandler::MotorHandler(bool &bDecapState, bool &bSolenoidState, bool &bDecapDoneState):
 bDecapState(bDecapState), 
 bSolenoidState(bSolenoidState), 
 bDecapDoneState(bDecapDoneState),
 SPEED_ROUNDABOUT(0.6f),
 SPEED_BELT(0.6f),
 SPEED_STOP(0.5f),
 doEnable_motors(PB_15),
 doSolenoid(PB_10), //eif eppis usgang
 pwm_MotorRoundabout(PB_13),
 pwm_MotorBelt(PA_9),
 encoder_MotorRoundabout(PA_6, PC_7),
 encoder_MotorBelt(PB_6, PB_7),
 pwm_period_s(0.00005f),
 max_voltage(12.0f),
 counts_per_turn_MBelt(20.0f * 391.0f),
 counts_per_turn_MRoundabout(20.0f * 195.0f),
 kn_MRoundabout(195.0f / 12.0f),
 kn_MBelt(391.0f / 12.0f),
 k_gear_MRoundabout(195.0f / 100.0f),
 k_gear_MBelt(391.0f / 100.0f),
 kp(0.1f),
 max_speed_rps(1.0f),
 speedController_MRoundabout(counts_per_turn_MRoundabout * k_gear_MRoundabout, kn_MRoundabout / k_gear_MRoundabout, max_voltage, pwm_MotorRoundabout, encoder_MotorRoundabout),
 speedController_MBelt(counts_per_turn_MBelt * k_gear_MBelt, kn_MBelt / k_gear_MBelt, max_voltage, pwm_MotorBelt, encoder_MotorBelt)
{
    
}

MotorHandler::~MotorHandler()
{
    doEnable_motors = 0;
}


void MotorHandler::MotorTasks(){

    //doEnable_motors = 1;
    //speedController_MRoundabout.setDesiredSpeedRPS(SPEED_ROUNDABOUT);

    if(bDecapState)
    {
        //MUSS BELT SEIN ROUNDABOUT FÜR TEST
        speedController_MRoundabout.setDesiredSpeedRPS(SPEED_ROUNDABOUT);
        //speedController_MBelt.setDesiredSpeedRPS(SPEED_BELT);
    }
    else
    {
        //MUSS BELT SEIN ROUNDABOUT FÜR TEST
        speedController_MRoundabout.setDesiredSpeedRPS(SPEED_STOP);
        //speedController_MBelt.setDesiredSpeedRPS(SPEED_STOP);
    }
    if(bDecapDoneState){
        speedController_MBelt.setDesiredSpeedRPS(SPEED_STOP);
    }

    if(bSolenoidState){
        ThisThread::sleep_for(500ms);
        doSolenoid = 1;
        ThisThread::sleep_for(500ms);
        doSolenoid = 0;
    }



printf("motortasks\r\n");

}
