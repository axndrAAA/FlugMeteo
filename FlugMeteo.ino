

#include "Tachymeter.h"

    Tachymeter tach(0);


void setup()
{
    Serial.begin(9600);
    Serial.println("Started.");
    tach.init(); 

}

void loop()
{
    Serial.print("RPM = ");
    Serial.print(tach.readRPM());

    Serial.print("   V = ");
    Serial.println(tach.readLinearV(1000));
    
    delay(300);
}
