
#ifndef VOLTMETER
#define VOLTMETER

#include "Arduino.h"

#define R1 100000.0
#define R2 10000.0
#define V_REF 5.0

class Voltmeter
{
private:
    int8_t analog_pin;

    float coeff = V_REF * (R1 + R2) / (1024.0 * R2); // coefficient of voltage divider
public:

    /**
     * Default constructor
     */
    Voltmeter();

    /**
     * Standart constructor.
     * @param a_pin     The pin uses for analogRead
     */
    Voltmeter(int8_t a_pin);

    
    /**
     * Reads voltage level from voltage divider
     * @return voltage in [Volts]
     */
    float readVoltage(void);
};
#endif VOLTMETER