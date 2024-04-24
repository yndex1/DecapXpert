#include "Servo.h"

Servo::Servo(PinName Pin) : ServoPin(Pin) {}

/**
 * Sets the desired position.
 * @Pos desired position in mus (position/period).
 */
void Servo::SetPosition(int Pos)
{
    Position = Pos;
}

void Servo::StartPulse()
{
    ServoPin = 1;
    PulseStop.attach(callback(this, &Servo::EndPulse), std::chrono::microseconds{static_cast<long int>(Position)});
}

void Servo::EndPulse()
{
    ServoPin = 0;
}

/**
 * Enables the servo with start position and period.
 * @StartPos start position in mus.
 * @Period period in mus.
 */
void Servo::Enable(int StartPos, int Period)
{
    Position = StartPos;
    Pulse.attach(callback(this, &Servo::StartPulse), std::chrono::microseconds{static_cast<long int>(Period)});
}

/**
 * Disables the servo.
 */
void Servo::Disable()
{
    Pulse.detach();
}