#include "Arduino.h"
#include"WindVelocity.h"
#include "Adafruit_BMP280.h"
#include "MedianFilter.h"

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
    
    return pres_filter.in(pit_tube.readPressure() + 183.0);
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

float WindVelocity::getAirDensity( float p_stat_air, float fi,float t_air)
{
    
    float pv = fi*6.1078*pow(10, ((7.5*t_air)-2048.625)/(TO_KELVIN(t_air)-35.85));//saturated vapor partial pressure in mBar
    float pd = p_stat_air - pv; //dry air pressure

    return (pd/R_DRY_CONST + pv/R_STEAM_CONST)/TO_KELVIN(t_air);
}

float WindVelocity::readVangle()
{
    return compass.GetHeadingDegreesHQ();//corrected with calibration matrix and bias
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

    init_HMC5883L();

    pres_filter = MedianFilter(PRES_FILTER_SIZE, PRES_FILTER_SEED);

    while(readP_full() == 0.00){
        /* code */
    }
    
    
}

void WindVelocity::init_BMP280(void)
{
    if(pit_tube.begin(BMP280_ADDRESS_ALT)){
        log_info("BMP280 PitotTube initialized");
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

void WindVelocity::init_HMC5883L(void)
{
    // Magnetic Declination is the correction applied according to your present location
  // in order to get True North from Magnetic North, it varies from place to place.
  // 
  // The declination for your area can be obtained from http://www.magnetic-declination.com/
  // Take the "Magnetic Declination" line that it gives you in the information, 
  //
  // Examples:
  //   Christchurch, 23° 35' EAST
  //   Wellington  , 22° 14' EAST
  //   Dunedin     , 25° 8'  EAST
  //   Auckland    , 19° 30' EAST
  //   Moscow      , 11  16' EAST
  //    
  compass.SetDeclination(11, 16, 'E');  
  
  // The device can operate in SINGLE (default) or CONTINUOUS mode
  //   SINGLE simply means that it takes a reading when you request one
  //   CONTINUOUS means that it is always taking readings
  // for most purposes, SINGLE is what you want.
  compass.SetSamplingMode(COMPASS_SINGLE);
  
  // The scale can be adjusted to one of several levels, you can probably leave it at the default.
  // Essentially this controls how sensitive the device is.
  //   Options are 088, 130 (default), 190, 250, 400, 470, 560, 810
  // Specify the option as COMPASS_SCALE_xxx
  // Lower values are more sensitive, higher values are less sensitive.
  // The default is probably just fine, it works for me.  If it seems very noisy
  // (jumping around), incrase the scale to a higher one.
  compass.SetScale(COMPASS_SCALE_130);
  
  // The compass has 3 axes, but two of them must be close to parallel to the earth's surface to read it, 
  // (we do not compensate for tilt, that's a complicated thing) - just like a real compass has a floating 
  // needle you can imagine the digital compass does too.
  //
  // To allow you to mount the compass in different ways you can specify the orientation:
  //   COMPASS_HORIZONTAL_X_NORTH (default), the compass is oriented horizontally, top-side up. when pointing North the X silkscreen arrow will point North
  //   COMPASS_HORIZONTAL_Y_NORTH, top-side up, Y is the needle,when pointing North the Y silkscreen arrow will point North
  //   COMPASS_VERTICAL_X_EAST,    vertically mounted (tall) looking at the top side, when facing North the X silkscreen arrow will point East
  //   COMPASS_VERTICAL_Y_WEST,    vertically mounted (wide) looking at the top side, when facing North the Y silkscreen arrow will point West  
  compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH);



    log_info("HMC5883 initialized.");
}