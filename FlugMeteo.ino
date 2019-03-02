#include"libs/Voltmeter/Voltmeter.h"

Voltmeter v_meter(0);


void setup()
{

}

void loop()
{
    Serial.print("Voltage: ");
    Serial.print(v_meter.readVoltage());
    delay(1000);
}
