
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

    Serial.print("    Air speed = ");
    Serial.print(vel.readVabs(99302.02 , 50.0, 21.0));

    Serial.print(" Heading = ");
    Serial.println( vel.readVangle() );



    delay(1000);
}
