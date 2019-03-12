#include"PitotTube.h"
#include <Wire.h>
#include<Adafruit_BMP280.h>

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
        #ifdef DEBUG
            Serial.println("The PitotTube initialized successfull.");
        #endif
    }else
    {
        #ifdef DEBUG
            Serial.println("The PitotTube initialize failed.");
        #endif
    }
    

      /* Default settings from datasheet. */
    setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}