#include<BatteryMonitoring.h>

BatteryMonitoring bm(1, 2);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.print("BatStatus = ");
    Serial.print(bm.bat_status_name[bm.getBatStatus(true)]);

    Serial.print("  | Vbat =");
    Serial.print(bm.getBatVoltage(false));

    Serial.print("  |  BatLevel = ");
    Serial.print(bm.getBatLevel(false));
    Serial.println("%");

    


    delay(1000);
}
