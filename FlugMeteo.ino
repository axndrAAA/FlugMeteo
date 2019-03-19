
#include<WindVelocity.h>
    WindVelocity vel;



void setup()
{
    Serial.begin(9600);
    Serial.println("Started.");
    vel.init(true);
}

void loop()
{

    Serial.print("P_FULL = ");
    Serial.print(vel.readP_full());

    Serial.print("    Air density = ");
    Serial.println(vel.getAirDensity(21.3,vel.readP_full() , 50.0));



    delay(1000);
}
