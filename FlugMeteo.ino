

#include"WindVelocity.h"
#include"Adafruit_BMP280.h"
#include"MedianFilter.h"

    WindVelocity vel;
    Adafruit_BMP280 bmp;
    MedianFilter pres_filter(31, 0);


void setup()
{
    Serial.begin(9600);
    Serial.println("Started.");
    vel.init(true);

    if (!bmp.begin(BMP280_ADDRESS_ALT)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    while(pres_filter.in(bmp.readPressure()) == 0.0){
        /* code */
    }
    

}

void loop()
{
    Serial.print("P_FULL = ");
    Serial.print(vel.readP_full());

    Serial.print("   P_STAT = ");
    Serial.print(pres_filter.in(bmp.readPressure()));

    Serial.print("   DIFF = ");
    Serial.print(pres_filter.out() - vel.readP_full());


    
    Serial.print("    Air speed = ");
    Serial.println(vel.readVabs(pres_filter.out(), 50.0, -100.0));
/*
    Serial.print(" Heading = ");
    Serial.println( vel.readVangle() );
    */



    delay(300);
}
