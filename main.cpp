#include "mbed.h"
#include "PM2_Libary.h"
#include <string>
#include <MotorHandler.h>
#include <SensorHandler.h>


// logical variable main task
bool do_execute_main_task = false;  // this variable will be toggled via the user button (blue button) to or not to execute the main task

// user button on nucleo board
Timer user_button_timer;            // create Timer object which we use to check if user button was pressed for a certain time (robust against signal bouncing)
InterruptIn user_button(PC_13);     // create InterruptIn interface object to evaluate user button falling and rising edge (no blocking code in ISR)
void user_button_pressed_fcn();     // custom functions which gets executed when user button gets pressed and released, definition below
void user_button_released_fcn();

// while loop gets executed every main_task_period_ms milliseconds
int main_task_period_ms = 50;   // define main task period time in ms e.g. 50 ms -> main task runns 20 times per second
Timer main_task_timer;          // create Timer object which we use to run the main task every main task period time in ms

// led on nucleo board
DigitalOut user_led(LED1);      // create DigitalOut object to command user led

// additional Led
DigitalOut extra_led(PB_9);     // create DigitalOut object to command extra led (do add an aditional resistor, e.g. 220...500 Ohm)

// mechanical button
DigitalIn mechanical_button(PC_5);  // create DigitalIn object to evaluate extra mechanical button, you need to specify the mode for proper usage, see below

//1 - Start
int iState;
const int START = 1;
const int STOP = 10;


int main()
{
    // attach button fall and rise functions to user button object
    user_button.fall(&user_button_pressed_fcn);
    user_button.rise(&user_button_released_fcn);

    // start timers
    main_task_timer.start();

    SensorHandler SensorHandler;
    
    while (true) { // this loop will run forever

        main_task_timer.reset();

        if (do_execute_main_task) {
        iState = START;    

        } else {
            iState = STOP;
        }

        switch (iState)
        {
            case START:{
 
                        
                        printf("Task START\r\n");
                        MotorHandler MotorHandlerObjekt(SensorHandler.bDecapState, SensorHandler.bSolenoidState, SensorHandler.bDecapDoneState);
                        MotorHandlerObjekt.MotorTasks();
                        //MotorHandlerObjekt.~MotorHandler();


                        
                        break;}
            case STOP:{

                 printf("Task STOP\r\n");
                 break;}

            default: {printf("Kein Case");}
        }
        user_led = !user_led;

        // do only output via serial what's really necessary (this makes your code slow)
        //printf("state: %i \r\n", iState);

        // read timer and make the main thread sleep for the remaining time span (non blocking)
        int main_task_elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(main_task_timer.elapsed_time()).count();
        thread_sleep_for(main_task_period_ms - main_task_elapsed_time_ms);
    }
}

void user_button_pressed_fcn()
{
    user_button_timer.start();
    user_button_timer.reset();
}

void user_button_released_fcn()
{
    // read timer and toggle do_execute_main_task if the button was pressed longer than the below specified time
    int user_button_elapsed_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(user_button_timer.elapsed_time()).count();
    user_button_timer.stop();
    if (user_button_elapsed_time_ms > 200) {
        do_execute_main_task = !do_execute_main_task;
    }
}
