#ifndef RAIN_SENSOR
#define RAIN_SENSOR

#include "Arduino.h"
#include <Voltmeter.h>

#define METRIC_NUMBER 10


/**
 * чем выше сырость, тем ниже значение на аналоговом выходе датчика
*/
class RainSensor
{
public:

    /**
     * Default constructor
     */
    RainSensor();

    /**
     * Standart constructor
     * @param analog_pin the analog pin sensor
     */
    RainSensor(uint8_t analog_pin);

    /**
     * sensor analog output 
     * @return analog value on analog_pin 
    */
    uint16_t getAnalogValue(void);

    /**
     * @return value of isRaning
    */
    bool isRaning(bool isUpdate);

    /**
     * update sensor status
    */
   void update(void);

    /**
     * set the upper limit of deadband
    */
    void setUpperLimit(uint16_t new_upper_limit);

    /**
     * set the lower limit of deadband
    */
    void setLowerLimit(uint16_t new_lower_limit);

private:
    uint8_t analog_sensor_pin;
    bool rainFlag;

    uint16_t lower_limit = 500;// эти параметры задают мертвую зону.
    uint16_t upper_limit = 800; // Т.о. флаг дождя не сбростится пока датчик не подсохнет, и флаг не появитя,
                                // пока датчик не увлажнится достаточно сильно
};
#endif RAIN_SENSOR