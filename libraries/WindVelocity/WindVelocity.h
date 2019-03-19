
#ifndef WIND_VELOCITY
#define WIND_VELOCITY

#include "Arduino.h"
#include <HMC5883L_Simple.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

#define M_DRY_AIR 29.0 // mollar mass [g/moll]
#define R_DRY_CONST 287.058  // gas constant for dry air[Dg/moll*K]
#define R_STEAM_CONST 461.495   // gas constant for water steam[Dg/moll*K]

#define TO_KELVIN(t_celsium) (t_celsium + 273.0)

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
     * return air pressure in pitot tube
     * @return P_full 
    */
   float readP_full();

   /**
    * return P_full - P_stat
    * @param p_stat static air pressure
    * @return p_dyn
   */
    float readP_dyn(float p_stat);

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

    void init(bool isBMP280_SPI);

private:
    int8_t tch_pin = 255; // tachymeter interrupt pin 

    Adafruit_BMP280 pit_tube; //Pitot tube sensor
    //HMC5883L_Simple compass; // compass-magnetometer for measuring wind direction

    /**
     * initialize pressure sensor in Pitot tube
    */
    void init_BMP280(void);


};
#endif WIND_VELOCITY