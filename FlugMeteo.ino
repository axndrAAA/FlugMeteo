#include<WindVelocity.h>

#define DEBUG

WindVelocity vel(2,true);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.print("Preshure = ");
    Serial.println(vel.readP_dyn());

    delay(1000);
}
