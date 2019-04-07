

#include "Station.h"

    Station station;


void setup()
{
    Serial.begin(9600);
    Serial.println("Started.");
    station.init();
    Serial.println("Initialized.");

}

void loop()
{
    Serial.print("StrMessage:  ");
    Serial.print(station.getMessage_str());

    delay(1000);
}
