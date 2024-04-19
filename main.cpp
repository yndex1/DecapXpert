//Workshop1
#include "mbed.h"
#include "PM2_Libary.h"

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

// Sharp GP2Y0A41SK0F, 4-40 cm IR Sensor
float ir_distance_mV = 0.0f;    // define variable to store measurement
// ???    // create AnalogIn object to read in infrared distance sensor, 0...3.3V are mapped to 0...1
AnalogIn ir_analog_in(PC_3);


int main()
{
    // attach button fall and rise functions to user button object
    user_button.fall(&user_button_pressed_fcn);
    user_button.rise(&user_button_released_fcn);

    // start timers
    main_task_timer.start();

    // set pullup mode: add resistor between pin and 3.3 V, so that there is a defined potential
    mechanical_button.mode(PullUp);
    
    while (true) { // this loop will run forever

        main_task_timer.reset();

        if (do_execute_main_task) {
            
            // read analog input
            ir_distance_mV = 1.0e3f * ir_analog_in.read() * 3.3f;

            // if the mechanical button is pressed the extra led is blinking
            if (mechanical_button.read()) {
                // visual feedback that the main task is executed
                extra_led = !extra_led;
            } else {
                extra_led = 1;
            }

        } else {

            ir_distance_mV = 0.0f;

            extra_led = 0;
        }

        user_led = !user_led;

        // do only output via serial what's really necessary (this makes your code slow)
        printf("IR sensor (mV): %3.3f\r\n", ir_distance_mV);

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