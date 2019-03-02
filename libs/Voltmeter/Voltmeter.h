#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
 #include "TinyWireM.h"
 #define Wire TinyWireM
#else
 #include <Wire.h>
#endif


class Voltmeter
{
private:
    int8_t analog_pin;

    float R1 = 100000.0; //Om
    float R2 = 10000.0;  //Om

    float coeff = 0.0; // coefficient of voltage divider
public:

    /**
     * Default constructor
     */
    Voltmeter();

    /**
     * Standart constructor.
     * @param a_pin     The pin to use for analogRead
     */
    Voltmeter(int8_t a_pin);

    
    /**
     * Reads voltage level from voltage divider
     * @return voltage in [Volts]
     */
    float readVoltage(void);
};


