#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "SSD1306Wire.h"  

class MyDisplay {
public:
    void begin();
    void printMessage(String msg);

private:
    SSD1306Wire display{0x3C, 21, 22};  // I2C address, SDA, SCL
};

#endif