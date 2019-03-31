
#ifndef WIND_VELOCITY
#define WIND_VELOCITY

#include "Arduino.h"
#include "MedianFilter.h"
#include <HMC5883L_Simple.h>
#include "Tachymeter.h"

#define PRES_FILTER_SIZE 21
#define PRES_FILTER_SEED 0

//tachymeter sensor radius in [mm]
#define TACHYMETER_RADIUS 100


class WindVelocity
{
public:
    /*Encapsulates abs wind speed value and it's cource (magnetic) */
    struct Wind
    {
        float v; //velocity [m/s]
        float cource; // magnetic cource [grad]
    };
    
    /**
     * Default constructor
     */
    WindVelocity();

   
    /** wind speed module
     * @return wind speed module [m/s]
    */
    float readVabs();

    /**
     * returns air speed heading
     * @return air speed heading measured by compass-magnetometer
    */
    float readVangle();

    /**
     * reads wind speed vector
     * @return struct with air speed module and cource
    */
    Wind readVvector();

    void init(uint8_t tach_pin);

private:

    HMC5883L_Simple compass; // compass-magnetometer for measuring wind direction

    Tachymeter speed;

    MedianFilter pres_filter;

    /**
     * initialize 3x axis magnetometer
    */
    void init_HMC5883L(void);

    /**
     * initialize tachymeter for air speed measuring
     * @param tach_pin interrupt pin for tachymeter
    */
    void init_tachymeter(uint8_t tach_pin);

};
#endif
