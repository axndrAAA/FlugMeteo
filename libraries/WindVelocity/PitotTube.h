#ifndef PITOT_TUBE
#define PITOT_TUBE

#include "Arduino.h"
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

class PitotTube : public Adafruit_BMP280
{
public:
    /**
     * Default  I2C constructor
     */
    PitotTube();

    /**
     * SPI constructor
    */
   PitotTube(bool isI2C);

    /**
     * init settings
    */
    void init(void);

};
#endif PITOT_TUBE