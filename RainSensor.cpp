#include"RainSensor.h"
#include"Arduino.h"

RainSensor::RainSensor()
{
}

RainSensor::RainSensor(uint8_t analog_pin):RainSensor()
{
    analog_sensor_pin = analog_pin;
    pinMode(analog_sensor_pin,INPUT);

    update();
}

uint16_t RainSensor::getAnalogValue(void)
{
    return analogRead(analog_sensor_pin);
}

bool RainSensor::isRaning(bool isUpdate)
{
    if(isUpdate){
        update();
    }
    return rainFlag;
}

void RainSensor::update(void){
    uint16_t val = 0;
    uint8_t count = 0;
    while(count < METRIC_NUMBER){
        count++;
        val += getAnalogValue();
    }

    val /= METRIC_NUMBER;

    if(val < lower_limit)
    {
        rainFlag = true;
    }else if(val > upper_limit)
    {
        rainFlag = false;
    }    
}

void RainSensor::setUpperLimit(uint16_t new_upper_limit)
{
    upper_limit = new_upper_limit;
}

void RainSensor::setLowerLimit(uint16_t new_lower_limit)
{
    lower_limit = new_lower_limit;
}