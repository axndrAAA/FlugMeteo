#ifndef STATION_H
#define STATION_H

#include "Arduino.h"
#include <string.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>

#include "WindVelocity.h"
#include "RainSensor.h"
#include "BatteryMonitoring.h"

/**
//Settings and pinouts:
*/

#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

//Uncomment if baro is connected via SPI
//#define iS_BARO_USE_SPI 1
#ifdef iS_BARO_USE_SPI
    //barometer sensor's SPI pinout
    #define BMP_SCK  (13)
    #define BMP_MISO (12)
    #define BMP_MOSI (11)
    #define BMP_CS   (10)
#endif

#define RAIN_SENSOR_A_PIN 3 //Rain sensor analog pin 

#define BMS_V_METER_PIN 2 // analog pin uses for measuring voltage on accumulator
#define BMS_CHARGE_STATUS_PIN 5 // Digital pin uses to indicate charging status 

// Iinterrupt pin for rpm sensor in areometer
#define AREOMETER_RPM_PIN 0

class Station
{

public:
    /** Structure for message data*/
    struct MESSAGE
    {
        float v_air;
        uint16_t air_v_ang;
        uint8_t humidity;
        float temperature;
        float pressure;
        bool is_raning;
        float bat_voltage;
        bool bat_status;
    };
    
    /**
     * Default constructor
    */
    Station();

    /**
     * Return MESSAGE with all data
    */
    MESSAGE getMessage();

    /**
     * Return string with all data
    */
   String getMessage_str();

    /**
     * Calibrate Rain sensor
     * @param lower Lower limit of sensor saturation
     * @param upper Upper limit of sensor saturation
    */
    void setRainSensorLimits(uint16_t lower, uint16_t upper);

    /**
     * initialize all sensors
    */
    void init(void);

private:
    
    WindVelocity areometer; //wind vector sensor
    DHT dht; // humidity and tempereture sensor
    Adafruit_BMP280 barometer;// air pressure sensor
    RainSensor rain_sensor; // rain sensor
    BatteryMonitoring battery; // battery monitoring sensor

    /**
     * initialize barometer sensor (bmp 280)
    */
    void init_baro(void);
};

#endif
