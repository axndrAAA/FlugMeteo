#include "Arduino.h"
#include"Voltmeter.h"

Voltmeter::Voltmeter()
{
    analog_pin = 0 // default voltage divider pin

    coeff = 5.0 * (R1 + R2) / (1024.0 * R2);

}

Voltmeter::Voltmeter(int8_t a_pin):Voltmeter()
{
    analog_pin = a_pin;
}

float Voltmeter:: readVoltage(void){
    return analogRead(analog_pin) * coeff;
}


