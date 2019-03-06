#include"BatteryMonitoring.h"
#include <Voltmeter.h>
#include"Arduino.h"

float float_map(float x, float in_min, float in_max, float out_min, float out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

BatteryMonitoring::BatteryMonitoring()
{

}

BatteryMonitoring::BatteryMonitoring(uint8_t v_meter_a_pin, uint8_t charge_status_pin)
{
    voltmeter = Voltmeter(v_meter_a_pin);
    charge_sensor_pin = charge_status_pin;
    pinMode(charge_sensor_pin, INPUT);

    update();
}

float BatteryMonitoring::getBatVoltage(bool isUpdate)
{
    if(isUpdate)
         {
            update();
        }

    return voltage;
}

uint8_t BatteryMonitoring::getBatLevel(bool isUpdate)
{
    if(isUpdate)
    {
        update();
    }
    return level;
}

byte BatteryMonitoring::getBatStatus(bool isUpdate)
{
    if(isUpdate)
    {
        update();
    }
    return status;
}

void BatteryMonitoring::update(void)
{
    voltage = voltmeter.readVoltage();
    
    if(voltage > MAX_LION_VOLTAGE)
    {
        status = bat_status::HIGH_VOLTAGE;
        level = 100;
        return;
    }
    else if (voltage < MIN_LION_VOLTAGE)
    {
        status = bat_status::LOW_VOLTAGE;
        level = 0;
    }
    else
    {
        status = bat_status::NORMAL;
        level = float_map(voltage, MIN_LION_VOLTAGE, MAX_LION_VOLTAGE, 0, 100);
    }     

    if (digitalRead(charge_sensor_pin))
        {
            status = bat_status::CHARGING;
            level = float_map(voltage, MIN_LION_VOLTAGE, MAX_LION_VOLTAGE, 0, 100);
        }
        
}