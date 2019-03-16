#ifndef BATTERY_MONITORING
#define BATTERY_MONITORING

#include "Arduino.h"
#include "string.h"
#include <Voltmeter.h>

#define MIN_LION_VOLTAGE 3.2
#define MAX_LION_VOLTAGE 4.2

class BatteryMonitoring
{
public:
    enum bat_status {
        NORMAL,
        CHARGING,
        LOW_VOLTAGE,
        HIGH_VOLTAGE
    };

    String bat_status_name[4] = {
        "NORMAL",
        "CHARGING",
        "LOW_VOLTAGE",
        "HIGH_VOLTAGE"
         };

    /**
     * Default constructor
     */
    BatteryMonitoring();

    /**
     * Standart constructor.
     * @param v_meter_a_pin     The pin uses for voltage measuring
     * @param charge_status_pin The pin uses for detecting charging process
     */
    BatteryMonitoring(uint8_t v_meter_a_pin, uint8_t charge_status_pin);


    /**
     * Gets battery voltage 
     * @param isUpdate      if true -> update values, else return old one
     * @return value stored in float voltage in [Volts].
     */    
    float getBatVoltage(bool isUpdate);

    /**
     * gets battery charge level
     * @param isUpdate      if true -> update values, else return old one
     * @return battery  level in [%]
    */
    uint8_t getBatLevel(bool isUpdate);

    /**
     * gets battery status
     * if true -> update values, else return old one
     * @return battery  status - one of the bat_status enum
    */
    bat_status getBatStatus(bool isUpdate);

    /**
     * updates all info about battery
     *
    */
   void update(void);

private:
    Voltmeter voltmeter;
    uint8_t charge_sensor_pin;

    bat_status status;
    float voltage;
    uint8_t level;
};
#endif BATTERY_MONITORING