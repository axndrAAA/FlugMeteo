

#include "WindVelocity.h"

    WindVelocity vel;


void setup()
{
    Serial.begin(9600);
    Serial.println("Started.");
    vel.init(0); 

}

void loop()
{
    Serial.print("V = ");
    Serial.print(vel.readVabs());

    Serial.print("   Ang = ");
    Serial.println(vel.readVangle());
    
    delay(300);
}
