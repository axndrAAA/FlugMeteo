#include "Arduino.h"
#include"WindVelocity.h"

#include<math.h>

WindVelocity::WindVelocity()
{

}

WindVelocity::WindVelocity(bool isBMP280_SPI): tch_pin(_tch_pin)
{
    if(isBMP280_SPI){
        pit_tube = PitotTube(true);
    }else
    {
        pit_tube = PitotTube();
    }
    
}

float WindVelocity:: readP_dyn()
{
    return pit_tube.readPressure();
}

float WindVelocity::readVabs(float p_stat_air, float fi, float t_air)
{
    if (t_air < -80){
        t_air = pit_tube.readTemperature();
    }
    float p_dyn = readP_dyn();
    float ro_air = getAirDensity(p_stat_air, fi, t_air);
    return sqrt(2.0*(p_dyn)/ro_air);
}

float WindVelocity::getAirDensity(float t_air, float p_stat_air, float fi)
{
    float pv = fi*6.1078*pow(10, ((7.5*t_air)-2048.625)/(t_air-35.85));//saturated vapor partial pressure in mBar
    float pd = p_stat_air - pv; //dry air pressure

    return (pd/R_DRY_CONST + pv/R_STEAM_CONST)/t_air;
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