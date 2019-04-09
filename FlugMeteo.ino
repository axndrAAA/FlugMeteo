/**
 * @example TCPClientSingle.ino
 * @brief The TCPClientSingle demo of library WeeESP8266. 
 * @author Wu Pengfei<pengfei.wu@itead.cc> 
 * @date 2015.02
 * 
 * @par Copyright:
 * Copyright (c) 2015 ITEAD Intelligent Systems Co., Ltd. \n\n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version. \n\n
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "Station.h"
#include "ESP8266.h"
#include "SoftwareSerial.h"
#include "LowPower.h"

#define SSID        "ITEAD"
#define PASSWORD    "12345678"
#define HOST_NAME   "172.16.5.12"
#define HOST_PORT   (8090)

#define POWER_PIN 6

SoftwareSerial s_serial(10, 11);

ESP8266 wifi(s_serial);
Station station;

void setup(void)
{
    Serial.begin(9600);
    Serial.print("setup begin\r\n");
    station.init();
    
    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());

    //modules power driver
    pinMode(POWER_PIN, OUTPUT);
    powerManage(true);
}
 
void loop(void)
{
    //enable esp
    powerManage(true);

    //wait for starting module
    delay(200);

    Serial.print("setup begin\r\n");

    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }
 
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP:");
        Serial.println( wifi.getLocalIP().c_str());       
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    if (wifi.disableMUX()) {
        Serial.print("single ok\r\n");
    } else {
        Serial.print("single err\r\n");
    }
    
    Serial.print("setup end\r\n");
    
    if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
        Serial.print("create tcp ok\r\n");
    } else {
        Serial.print("create tcp err\r\n");
    }
    
    
    //getting and send data
    char *hello = station.getMessage_str().c_str();
    wifi.send((const uint8_t*)hello, strlen(hello));

    //close TCP connection
    if (wifi.releaseTCP()) {
        Serial.print("release tcp ok\r\n");
    } else {
        Serial.print("release tcp err\r\n");
    }

    //disconect AP
    if (wifi.leaveAP()) {
        Serial.print("disconect AP ok\r\n");
    } else {
        Serial.print("disconect AP err\r\n");
    }

    Serial.print("Shut down power\r\n");
    powerManage(false);
    
    Serial.print("Sleep for 16 sec\r\n");

    //sleep for 16 sec
    LowPower.idle(SLEEP_16S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                SPI_OFF, USART0_OFF, TWI_OFF);
}

void powerManage(bool enable)
{
    if(enable)
    {
        // enable power 
        digitalWrite(POWER_PIN, HIGH);
    }else
    {
        //disable power
        digitalWrite(POWER_PIN, LOW);
    }
    
}
