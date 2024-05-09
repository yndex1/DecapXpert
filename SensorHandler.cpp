#include <SensorHandler.h>
#include <EncoderCounter.h>

SensorHandler::SensorHandler(): 
bDecapState(false), 
bSolenoidState(false), 
bDecapDoneState(false),  
senTubeDetection(PC_2),
senTubeAfterBeltDetection(PC_3),
senTubeFluessigkeit(PC_5), 
senTubeBeforeSolenoid(PB_1), 
UPPER_THRESHOLD(1000.0f),
LOWER_THRESHOLD(500.0f),
fTubeDetection(0.0f),
fTubeFluessigkeit(0.0f),
fTubeAfterBelt(0.0f),
fTubeBeforeSolenoid(0.0f)
{
    thread.start(callback(this, &SensorHandler::SensorTasks));
    ticker.attach(callback(this, &SensorHandler::sendThreadFlag), PERIOD);
    
}

const float SensorHandler::PERIOD = 0.002f;                  // period of task, given in [s]
// Sensor Pin
DigitalIn sensorPin(PC_8); // Beispiel-Pin, an dem der Sensor angeschlossen ist
int iEncoderCounter= 0;
// Anzahl der Löcher auf der Scheibe
const int holeCount = 90;

// Zähler für die Umdrehungen

volatile int erwartetCount = 10;

// Vorheriger Zustand des Sensors
bool previousState = false;

/**
 * Deletes the SensorHandler object.
 */
SensorHandler::~SensorHandler() {
    
    ticker.detach();
}

/**
 * This method is called by the ticker timer interrupt service routine.
 * It sends a flag to the thread to make it run again.
 */
void SensorHandler::sendThreadFlag() {
    
    thread.flags_set(threadFlag);
}

void SensorHandler::SensorTasks() {



  while (true) {

    // wait for the periodic thread flag

    ThisThread::flags_wait_any(threadFlag);
    

    fTubeDetection = 1.0e3f * senTubeDetection.read() * 3.3f;
    fTubeAfterBelt = 1.0e3f * senTubeAfterBeltDetection.read() * 3.3f;
    fTubeFluessigkeit = 1.0e3f * senTubeFluessigkeit.read() * 3.3f;
    fTubeBeforeSolenoid = 1.0e3f * senTubeBeforeSolenoid.read() * 3.3f;

    //printf("Sensortasks\r\n");
    if(bDecapState == true){
        SensorStateChanged();
        }
    if (fTubeDetection > 0 && fTubeDetection < 400) {
        bDecapState = true;
        //SensorStateChanged();
    //  printf("decapStateTrue\r\n");
      //bDecapState = false;
    }
    
    if (fTubeBeforeSolenoid > 2200 && fTubeBeforeSolenoid < 2400) {
        bSolenoidState = true;
    }

    if (fTubeFluessigkeit > 0 && fTubeFluessigkeit < 700)
    {
        bFluessigkeit = true;

    }
    //else bDecapState = false;

    

  }
}

void SensorHandler::SensorTest()
{
    //AnalogIn AI1(PC_2);
    //AnalogIn AI2(PC_5);


    //printf("PC2: %f  PC5: %f\r\n", 1000.0f*3.3f*AI1.read(),1000.0f*3.3f*AI2.read());


}


bool SensorHandler::EncoderUeberpruefen() {
return false;
}




// Funktion, die jedes Mal aufgerufen wird, wenn sich der Zustand des Sensors ändert
void SensorHandler::SensorStateChanged() {
    bool currentState = sensorPin.read();
    // Überprüfen Sie, ob sich der Zustand des Sensors geändert hat
    if (currentState != previousState) {
        previousState = currentState;
        
        if (currentState == true) {
            iEncoderCounter++;
        }
    }
}

void SensorHandler::EncoderCounterReset()
{
    iEncoderCounter = 0;
}