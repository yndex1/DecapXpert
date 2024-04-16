#include <MotorHandler.h>

MotorHandler:: MotorHandler(bool &bDecapState, bool &bSolenoidState, bool &bDecapDoneState): bStateMotorRoundabout(true), bStateMotorBelt(false), bDecapState(bDecapState), bSolenoidState(bSolenoidState), bDecapDoneState(bDecapDoneState)
{
//Motor Controller Decap Band starten

}

void MotorHandler::MotorTasks(){



while(true){
    bStateMotorBelt = bDecapState;


    if(bStateMotorBelt == 1){
        //Motor Controller Solenoid startet
    }
}




}
