
#ifndef WIND_VELOCITY
#define WIND_VELOCITY

#include "Arduino.h"
#include "Adafruit_BMP280.h"
#include "MedianFilter.h"
#include <HMC5883L_Simple.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

#define M_DRY_AIR 29.0 // mollar mass [g/moll]
#define R_DRY_CONST 287.058  // gas constant for dry air[Dg/moll*K]
#define R_STEAM_CONST 461.495   // gas constant for water steam[Dg/moll*K]

#define PRES_FILTER_SIZE 21
#define PRES_FILTER_SEED 0

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
    float getAirDensity( float p_stat_air, float fi, float t_air);

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
    HMC5883L_Simple compass; // compass-magnetometer for measuring wind direction

    MedianFilter pres_filter;

    /**
     * initialize pressure sensor in Pitot tube
    */
    void init_BMP280(void);

    /**
     * initialize 3x axis magnetometer
    */
    void init_HMC5883L(void);


};
#endif