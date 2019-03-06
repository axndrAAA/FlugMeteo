#include<Voltmeter.h>

Voltmeter voltmeter(1);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.print("V =");
    Serial.println(voltmeter.readVoltage());
    delay(1000);
}
