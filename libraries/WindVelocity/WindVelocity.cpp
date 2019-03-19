#include "Arduino.h"
#include"WindVelocity.h"
#include <Adafruit_BMP280.h>
#include<math.h>

#define DEBUG
#ifdef DEBUG
    #define log_info(M) Serial.println(M)
#else
	#define log_info(M)
#endif

WindVelocity::WindVelocity()
{

}

WindVelocity::WindVelocity(bool isBMP280_SPI)
{
        
}

float WindVelocity:: readP_full()
{
    return pit_tube.readPressure();
}

float WindVelocity::readP_dyn(float p_stat)
{
    return readP_full() - p_stat;
}

float WindVelocity::readVabs(float p_stat_air, float fi, float t_air)
{
    if (t_air < -80){
        t_air = pit_tube.readTemperature();
    }
    float p_dyn = readP_dyn(p_stat_air);
    float ro_air = getAirDensity(p_stat_air, fi, t_air);
    return sqrt(2.0*(p_dyn)/ro_air);
}

float WindVelocity::getAirDensity(float t_air, float p_stat_air, float fi)
{
    
    float pv = fi*6.1078*pow(10, ((7.5*t_air)-2048.625)/(TO_KELVIN(t_air)-35.85));//saturated vapor partial pressure in mBar
    float pd = p_stat_air - pv; //dry air pressure

    return (pd/R_DRY_CONST + pv/R_STEAM_CONST)/TO_KELVIN(t_air);
}

float WindVelocity::readVangle()
{
    return 1;//compass.GetHeadingDegreesHQ();//corrected with calibration matrix and bias
}

WindVelocity::Wind WindVelocity::readVvector(float p_stat_air, float fi, float t_air)
{
    WindVelocity::Wind ret;
    ret.v = readVabs(p_stat_air, fi, t_air);
    ret.cource = readVangle();
    return ret;
}

void WindVelocity::init(bool isBMP280_SPI)
{
    if(isBMP280_SPI){
        log_info("try to create pito spi");
        pit_tube = Adafruit_BMP280(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
    }else
    {
        log_info("try to create pito i2c");

    }
    init_BMP280();
    
}

void WindVelocity::init_BMP280(void)
{
    if(pit_tube.begin(BMP280_ADDRESS_ALT)){
        log_info("The PitotTube initialized successfull.");
    }else
    {
        log_info("Could not find a valid BMP280 sensor, check wiring!");
        while (1);
    }
    

      /* Default settings from datasheet. */
    pit_tube.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}