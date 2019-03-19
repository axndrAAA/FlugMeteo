

#include<WindVelocity.h>
#include<PitotTube.h>
    //WindVelocity vel(false);
    PitotTube pt(true);

void setup()
{
    Serial.begin(9600);
    Serial.println("Started.");
    
}

void loop()
{

    Serial.print("P_FULL = ");
    //Serial.println(vel.readP_full());

    //Serial.print("Air density = ");
   // Serial.println(vel.getAirDensity(25.0, 101325.0, 50.0));



    delay(1000);
}
