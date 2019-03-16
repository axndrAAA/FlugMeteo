#include"Station.h"

Station::Station()
{
    areometer = WindVelocity(iS_AREOMETER_USE_SPI);
    
    dht = DHT(DHTPIN, DHTTYPE);
    
    barometer = Adafruit_BMP280();
    
    #ifdef iS_BARO_USE_SPI
        barometer = Adafruit_BMP280(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
    #else
        barometer = Adafruit_BMP280();
    #endif

    rain_sensor = RainSensor(RAIN_SENSOR_A_PIN);

    battery = BatteryMonitoring(BMS_V_METER_PIN, BMS_CHARGE_STATUS_PIN);
    
}

Station::MESSAGE Station::getMessage()
{
    Station::MESSAGE ret;

    ret.humidity = dht.readHumidity();
    ret.temperature = dht.readTemperature();
    ret.pressure = barometer.readPressure();
    ret.is_raning = rain_sensor.isRaning(true);
    ret.bat_voltage = battery.getBatVoltage(true);
    ret.bat_status = battery.getBatStatus();
    ret.v_air = areometer.readVabs(ret.pressure,
                                    ret.humidity,
                                    ret.temperature);
    ret.air_v_ang = areometer.readVangle();
    
    return ret;
}

String Station::getMessage_str()
{
    String ret = "";
    float hum = dht.readHumidity();
    ret += hum + "/";
    float tempr = dht.readTemperature();
    ret += tempr + "/";
    float press = barometer.readPressure(); 
    ret += press + "/";
    ret += areometer.readVabs(press,
                              hum,
                              tempr) + "/";
    ret += rain_sensor.isRaning(true) + "/";
    ret += battery.getBatVoltage(true) + "/";
    ret += battery.getBatStatus() + "/";
    
    return ret;
}

void Station::setRainSensorLimits(uint16_t lower, uint16_t upper)
{
    rain_sensor.setLowerLimit(lower);
    rain_sensor.setUpperLimit(upper);
}

