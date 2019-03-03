#include "Arduino.h"
#include"Voltmeter.h"

Voltmeter::Voltmeter()
{
    
}

Voltmeter::Voltmeter(int8_t a_pin):Voltmeter()
{
    analog_pin = a_pin;
    pinMode(analog_pin, INPUT);
}

float Voltmeter:: readVoltage(void){
    return analogRead(analog_pin) * coeff;
}


