
#ifndef WIND_VELOCITY
#define WIND_VELOCITY

#include "Arduino.h"
#include <PitotTube.h>
#include <HMC5883L_Simple.h>

#define M_DRY_AIR 29.0 // mollar mass [g/moll]
#define R_DRY_CONST 287.058  // gas constant for dry air[Dg/moll*K]
#define R_STEAM_CONST 461.495   // gas constant for water steam[Dg/moll*K]

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

    /**
     * constructor for using with tachymeter
     * @param a_pin     The pin uses for tachymeter (if uses)
     * @param isBMP280_SPI == true if BMP280 in pit_tube is connected by SPI
     */
    WindVelocity(bool isBMP280_SPI);

    /**
     * return P_full - P_stat
     * @Pstat static air pressure
     * @return Pdyn 
    */
   float readP_dyn();

    /** wind speed module
     * @param t_air air temperature
     * @param p_stat_air static air pressure
     * @param fi  relative humidity
     * @return wind speed module
    */
    float readVabs(float p_stat_air, float fi, float t_air= -100.0);

    /**
     * returns air density
     * @param p_stat_air static air pressure in kPa
     * @param fi  relative humidity
     * @param t_air air temperature 
     * @return air density in kg/m^3
    */
    float getAirDensity(float t_air, float p_stat_air, float fi);

    /**
     * returns air speed heading
     * @return air speed heading measured by compass-magnetometer
    */
    float readVangle();

    /**
     * reads wind speed vector
     * @param p_stat_air static air pressure
     * @param fi  relative humidity
     * @param t_air air temperature
     * @return struct with air speed module and cource
    */
    Wind readVvector(float p_stat_air, float fi, float t_air= -100.0);


private:
    int8_t tch_pin = 255; // tachymeter interrupt pin 

    PitotTube pit_tube; //Pitot-Prandtel tube 
    HMC5883L_Simple compass; // compass-magnetometer for measuring wind direction


};
#endif WIND_VELOCITY