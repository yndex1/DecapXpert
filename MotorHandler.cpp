#include <MotorHandler.h>

MotorHandler::MotorHandler(bool &bDecapState, bool &bSolenoidState, bool &bDecapDoneState):
 bDecapState(bDecapState), 
 bSolenoidState(bSolenoidState), 
 bDecapDoneState(bDecapDoneState),
 SPEED_ROUNDABOUT(0.5f),
 SPEED_BELT(-1.0f),
 SPEED_STOP(0.0f),
 doEnable_motors(PB_15),
 doSolenoid(PB_10), //eif eppis usgang
 pwm_MotorRoundabout(PB_9),
 pwm_MotorBelt(PB_13),
 encoder_MotorRoundabout(PB_6, PB_7),
 encoder_MotorBelt(PA_6, PC_7),
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
    thread.start(callback(this, &MotorHandler::MotorTasks));
    ticker.attach(callback(this, &MotorHandler::sendThreadFlag), PERIOD);
}

DigitalOut solenoid(PC_6);
Solenoid Solenoid(solenoid);

const float MotorHandler::PERIOD = 0.2f;                  // period of task, given in [s]


MotorHandler::~MotorHandler()
{
    doEnable_motors = 0;
    ticker.detach();
}
void MotorHandler::MotorStop()
{
    doEnable_motors = 0;
}
void MotorHandler::MotorEnable()
{
    doEnable_motors = 1;

}
/**
 * This method is called by the ticker timer interrupt service routine.
 * It sends a flag to the thread to make it run again.
 */
void MotorHandler::sendThreadFlag() {
    
    thread.flags_set(threadFlag);
}

void MotorHandler::MotorTasks()
{


    //speedController_MRoundabout.setDesiredSpeedRPS(SPEED_ROUNDABOUT);
    

  while (true) {

    // wait for the periodic thread flag
    ThisThread::flags_wait_any(threadFlag);
    speedController_MBelt.setDesiredSpeedRPS(SPEED_BELT);

    if(bDecapState)
    {
        speedController_MBelt.setDesiredSpeedRPS(SPEED_BELT);
    }
    else
    {

        speedController_MBelt.setDesiredSpeedRPS(SPEED_STOP);
    }

    if(bSolenoidState){
        ThisThread::sleep_for(500ms);
        solenoid = 1;
        ThisThread::sleep_for(1000ms);
        solenoid = 0;
        bSolenoidState = 0;
    }
    /*
    if(bSolenoidState){
        
        Solenoid.set();
        ThisThread::sleep_for(500ms);
        Solenoid.reset();
    }
    */
//printf("motortasks\r\n");
  }
}
