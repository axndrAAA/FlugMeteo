#include"PitotTube.h"
#include <Wire.h>
#include<Adafruit_BMP280.h>

#define DEBUG
#ifdef DEBUG
    #define log_info(M) Serial.println(M)
#else
	#define log_info(M)
#endif

PitotTube::PitotTube():Adafruit_BMP280()
{
    init();
}

PitotTube::PitotTube(bool isI2C):Adafruit_BMP280(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK)
{
    init();
}

void PitotTube::init(void)
{
    if(begin(BMP280_ADDRESS_ALT)){
        log_info("The PitotTube initialized successfull.");
    }else
    {
        log_info("Could not find a valid BMP280 sensor, check wiring!");
        while (1);
    }
    

      /* Default settings from datasheet. */
    setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}