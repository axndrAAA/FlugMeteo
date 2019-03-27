#include"Tachymeter.h"
#include"Arduino.h"

Tachymeter::Tachymeter(/* args */)
{

}


Tachymeter::Tachymeter(uint8_t _sens_pin)
{
    sens_pin = _sens_pin;
}


void sens() {
	RPM=60/((float)(micros()-lastflash)/1000000);  //расчет
	lastflash=micros();  //запомнить время последнего оборота
}

void Tachymeter::init(){
    attachInterrupt(sens_pin,sens,RISING);
}



float Tachymeter::readRPM(){
    if ((micros()-lastflash)>1000000){ //если сигнала нет больше секунды
		RPM=0;  //считаем что RPM 0
	}
    return RPM;
}

float Tachymeter::readLinearV(uint16_t radius){
    return readRPM() * radius / 1000.0;
}