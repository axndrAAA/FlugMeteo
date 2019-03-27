#ifndef TACHYMETER_H
#define TACHYMETER_H
#include "Arduino.h"

static uint32_t RPM;
static unsigned long lastflash;



class Tachymeter
{


private:
    uint8_t sens_pin;
    
public:

    Tachymeter();

    /**
     * constructor
     * @param _sens_pin - pin used for sensor digital output
     *                      (WARNING _sens_pin must support interrupts!!!)
     *                      pin 2 ->  _sens_pin = 0
     *                      pin 1 -> _sens_pin = 1 (for arduino nano)
     * 
    */
    Tachymeter(uint8_t _sens_pin);

    /**
     * attach interrupt and etc
    */
    void init();

    /**
     * reads rpm in [round per minute]
     * @return round per minute
    */
    float readRPM();

    /**
     * calculate linear speed from angle speed
     * @param radius - radius of sensor place in [mm]
     * @return linear speed in [m/s]
    */
    float readLinearV(uint16_t radius);

    /**
     *  interrupts listener. calculate rpm;
    */
    //void sens();

};





#endif